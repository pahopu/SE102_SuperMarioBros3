#include "Brick.h"
#include "Goomba.h"
#include "KoopaTroopa.h"
#include "debug.h"

void CKoopaTroopa::Deflected(int direction)
{
	vy = -KOOPA_TROOPA_DIE_DEFLECT;
	ay = KOOPA_TROOPA_GRAVITY;

	vx = direction * KOOPA_TROOPA_WALKING_SPEED;
	ax = 0;
}

void CKoopaTroopa::OnCollisionWithBrick(LPCOLLISIONEVENT e)
{
	CBrick* brick = dynamic_cast<CBrick*>(e->obj);

	if (brick->IsAttacking() && brick->IsBrokenByJump() && e->ny != 0) {
		this->SetState(KOOPA_TROOPA_STATE_SHELL);

		float bx, by;
		brick->GetPosition(bx, by);

		if (bx < x)
			this->Deflected(DEFLECT_DIRECTION_RIGHT);
		else
			this->Deflected(DEFLECT_DIRECTION_LEFT);
	}
	if (state == KOOPA_TROOPA_STATE_ATTACKING && e->nx != 0)
	{
		if (brick->GetType() == BRICK_TYPE_GOLD)
			brick->SetType(BRICK_TYPE_BREAK);
		else if (brick->GetType() == BRICK_TYPE_QUESTION)
			brick->SetType(BRICK_TYPE_EMPTY);
	}
}

void CKoopaTroopa::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	if (goomba->GetState() == GOOMBA_STATE_DIE_BY_JUMP || goomba->GetState() == GOOMBA_STATE_DIE_BY_ATTACK)
		return;

	switch (state) {
	case KOOPA_TROOPA_STATE_WALKING:
		float gvx, gvy;
		goomba->GetSpeed(gvx, gvy);
		goomba->SetSpeed(-gvx, gvy);

		this->vx = -this->vx;

		break;

	case KOOPA_TROOPA_STATE_SHELL:
		if (isHeld) {
			SetState(KOOPA_TROOPA_STATE_DIE);
			Deflected(0);

			goomba->SetState(GOOMBA_STATE_DIE_BY_ATTACK);
			goomba->Deflected(0);
		}

		break;

	case KOOPA_TROOPA_STATE_ATTACKING:
		goomba->SetState(GOOMBA_STATE_DIE_BY_ATTACK);

		float gx, gy;
		goomba->GetPosition(gx, gy);

		if (gx >= x)
			goomba->Deflected(DEFLECT_DIRECTION_RIGHT);
		else goomba->Deflected(DEFLECT_DIRECTION_LEFT);

		break;
	}
}

void CKoopaTroopa::OnCollisionWithKoopaTroopa(LPCOLLISIONEVENT e)
{
	CKoopaTroopa* koopa = dynamic_cast<CKoopaTroopa*>(e->obj);

	if (state == KOOPA_TROOPA_STATE_DIE)
		return;

	switch (state) {
	case KOOPA_TROOPA_STATE_ATTACKING:
		float kx, ky;
		koopa->GetPosition(kx, ky);

		if (koopa->GetState() == KOOPA_TROOPA_STATE_ATTACKING || (koopa->GetState() == KOOPA_TROOPA_STATE_SHELL && koopa->isHeld)) {
			SetState(KOOPA_TROOPA_STATE_DIE);
			if (kx >= x)
				Deflected(DEFLECT_DIRECTION_LEFT);
			else Deflected(DEFLECT_DIRECTION_RIGHT);
		}

		koopa->SetState(KOOPA_TROOPA_STATE_DIE);
		koopa->Deflected(vx);

		break;

	default:
		if (koopa->GetState() == KOOPA_TROOPA_STATE_SHELL && koopa->isHeld) {
			SetState(KOOPA_TROOPA_STATE_DIE);
			koopa->SetState(KOOPA_TROOPA_STATE_DIE);
		}

		break;
	}

	if (state == KOOPA_TROOPA_STATE_ATTACKING) {

		float kx, ky;
		koopa->GetPosition(kx, ky);

		if (koopa->GetState() == KOOPA_TROOPA_STATE_ATTACKING) {
			this->SetState(KOOPA_TROOPA_STATE_DIE);

			if (kx >= x) this->Deflected(DEFLECT_DIRECTION_LEFT);
			else this->Deflected(DEFLECT_DIRECTION_RIGHT);
		}
		koopa->SetState(KOOPA_TROOPA_STATE_DIE);
		koopa->Deflected(this->vx);

	}
}

int CKoopaTroopa::GetAniId()
{
	int aniId = -1;
	if (state == KOOPA_TROOPA_STATE_WALKING) {
		if (vx <= 0)
			aniId = ID_ANI_KOOPA_TROOPA_WALKING_LEFT;
		else aniId = ID_ANI_KOOPA_TROOPA_WALKING_RIGHT;
	}
	else if (state == KOOPA_TROOPA_STATE_DIE)
		aniId = ID_ANI_KOOPA_TROOPA_SHELL;
	else if (state == KOOPA_TROOPA_STATE_SHELL) {
		aniId = ID_ANI_KOOPA_TROOPA_SHELL;
		if (GetTickCount64() - time_start >= KOOPA_TROOPA_SHELL_TIMEOUT - 200)
			aniId = ID_ANI_KOOPA_TROOPA_REFORM;
	}
	else if (state == KOOPA_TROOPA_STATE_ATTACKING)
		aniId = ID_ANI_KOOPA_TROOPA_ATTACKING;
	return aniId;
}

void CKoopaTroopa::SetLevel(int level)
{
	if (this->level == KOOPA_TROOPA_SHELL)
		y -= (KOOPA_TROOPA_BBOX_HEIGHT - KOOPA_TROOPA_BBOX_HEIGHT_DIE) / 2;
	this->level = level;
}

void CKoopaTroopa::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state) {
	case KOOPA_TROOPA_STATE_WALKING:
		vx = -KOOPA_TROOPA_WALKING_SPEED;
		phaseCheck->SetPosition(x - KOOPA_TROOPA_BBOX_WIDTH - KOOPA_TROOPA_PHASE_CHECK_WIDTH / 2, y);
		break;

	case KOOPA_TROOPA_STATE_SHELL:
		SetLevel(KOOPA_TROOPA_SHELL);
		time_start = GetTickCount64();
		y += (KOOPA_TROOPA_BBOX_HEIGHT - KOOPA_TROOPA_BBOX_HEIGHT_DIE) / 2;
		vx = vy = 0;
		break;

	case KOOPA_TROOPA_STATE_ATTACKING:
		time_start = -1;
		if (nx >= 0)
			vx = -KOOPA_TROOPA_SHELL_SPEED;
		else vx = KOOPA_TROOPA_SHELL_SPEED;
		break;

	case KOOPA_TROOPA_STATE_DIE:
		time_start = GetTickCount64();
		break;
	}

}

void CKoopaTroopa::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CKoopaTroopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0) {
		vy = 0;
		if (time_start != -1)
			vx = 0;
	}

	if (e->obj->IsBlocking() && e->nx != 0) {
		vx = -vx;

		float p_vx, p_vy;
		phaseCheck->GetSpeed(p_vx, p_vy);

		if (p_vx >= this->vx)
			phaseCheck->SetPosition(x - KOOPA_TROOPA_BBOX_WIDTH, y);
		else
			phaseCheck->SetPosition(x + KOOPA_TROOPA_BBOX_WIDTH, y);
	}

	float px, py;
	phaseCheck->GetPosition(px, py);

	if (state == KOOPA_TROOPA_STATE_WALKING && py - this->y > 10) {
		vx = -vx;

		if (px <= this->x)
			phaseCheck->SetPosition(x + KOOPA_TROOPA_BBOX_WIDTH, y);
		else phaseCheck->SetPosition(x - KOOPA_TROOPA_BBOX_WIDTH, y);
	}

	phaseCheck->SetSpeed(vx, 1);

	if (dynamic_cast<CBrick*>(e->obj))
		OnCollisionWithBrick(e);
	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CKoopaTroopa*>(e->obj))
		OnCollisionWithKoopaTroopa(e);
}

void CKoopaTroopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == KOOPA_TROOPA_STATE_WALKING) {
		left = x - KOOPA_TROOPA_BBOX_WIDTH / 2;
		top = y - KOOPA_TROOPA_BBOX_HEIGHT / 2;
		right = left + KOOPA_TROOPA_BBOX_WIDTH;
		bottom = top + KOOPA_TROOPA_BBOX_HEIGHT;
	}
	else {
		left = x - KOOPA_TROOPA_BBOX_WIDTH / 2;
		top = y - KOOPA_TROOPA_BBOX_HEIGHT_DIE / 2;
		right = left + KOOPA_TROOPA_BBOX_WIDTH;
		bottom = top + KOOPA_TROOPA_BBOX_HEIGHT_DIE;
	}
}

void CKoopaTroopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == KOOPA_TROOPA_STATE_WALKING)
		phaseCheck->Update(dt, coObjects);

	//if (isHeld == true) ay = 0;
	//else ay = KOOPA_TROOPA_GRAVITY;

	vx += ax * dt;
	vy += ay * dt;

	if ((state == KOOPA_TROOPA_STATE_SHELL) && (GetTickCount64() - time_start > KOOPA_TROOPA_SHELL_TIMEOUT)) {
		SetState(KOOPA_TROOPA_STATE_WALKING);
		SetLevel(KOOPA_TROOPA_NORMAL);
		time_start = -1;
		return;
	}

	if ((state == KOOPA_TROOPA_STATE_DIE) && (GetTickCount64() - time_start > KOOPA_TROOPA_DIE_TIMEOUT)) {
		isDeleted = true;
		phaseCheck->Delete();
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CKoopaTroopa::Render()
{
	//if (state == KOOPA_TROOPA_STATE_WALKING)
		//phaseCheck->RenderBoundingBox();

	int aniId = GetAniId();
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();

	float px, py;
	phaseCheck->GetPosition(px, py);
}
