#include "Goomba.h"
#include "KoopaTroopa.h"

void CKoopaTroopa::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
	if (state == KOOPA_TROOPA_STATE_ATTACKING)
		if (goomba->GetState() != GOOMBA_STATE_DIE_BY_JUMP)
			goomba->SetState(GOOMBA_STATE_DIE_BY_ATTACK);
}

void CKoopaTroopa::OnCollisionWithKoopaTroopa(LPCOLLISIONEVENT e)
{
	CKoopaTroopa* koopa = dynamic_cast<CKoopaTroopa*>(e->obj);
	if (state == KOOPA_TROOPA_STATE_ATTACKING)
		if (koopa->GetState() != KOOPA_TROOPA_STATE_DIE) {
			this->SetState(KOOPA_TROOPA_STATE_DIE);
			if (koopa->GetState() == KOOPA_TROOPA_STATE_ATTACKING)
				koopa->SetState(KOOPA_TROOPA_STATE_DIE);
		}
}

int CKoopaTroopa::GetAniId()
{
	int aniId = ID_ANI_KOOPA_TROOPA_WALKING_LEFT;
	if (state == KOOPA_TROOPA_STATE_DIE)
		aniId = ID_ANI_KOOPA_TROOPA_SHELL;
	else if (state == KOOPA_TROOPA_STATE_SHELL) {
		aniId = ID_ANI_KOOPA_TROOPA_SHELL;
		if (GetTickCount64() - shell_start >= 4000) {
			aniId = ID_ANI_KOOPA_TROOPA_REFORM;
		}
	}
	else if (state == KOOPA_TROOPA_STATE_ATTACKING)
		aniId = ID_ANI_KOOPA_TROOPA_ATTACKING;

	return aniId;
}

void CKoopaTroopa::SetLevel(int level)
{
	this->level = level;
	if (level == KOOPA_TROOPA_SHELL)
		y -= (KOOPA_TROOPA_BBOX_HEIGHT - KOOPA_TROOPA_BBOX_HEIGHT_DIE) / 2;
}

void CKoopaTroopa::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state) {
	case KOOPA_TROOPA_STATE_WALKING:
		vx = -KOOPA_TROOPA_WALKING_SPEED;
		break;

	case KOOPA_TROOPA_STATE_SHELL:
		SetLevel(KOOPA_TROOPA_STATE_SHELL);
		shell_start = GetTickCount64();
		y += (KOOPA_TROOPA_BBOX_HEIGHT - KOOPA_TROOPA_BBOX_HEIGHT_DIE) / 2;
		vx = vy = 0;
		break;

	case KOOPA_TROOPA_STATE_ATTACKING:
		if (nx >= 0)
			vx = KOOPA_TROOPA_SHELL_SPEED;
		else vx = KOOPA_TROOPA_SHELL_SPEED;
		break;

	case KOOPA_TROOPA_STATE_DIE:
		die_start = GetTickCount64();
		vy = -KOOPA_TROOPA_DIE_DEFLECT;
		vx = ax = 0;
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
	if (e->ny != 0)
		vy = 0;

	if (e->obj->IsBlocking() && e->nx != 0)
		vx = -vx;

	if (state != KOOPA_TROOPA_STATE_ATTACKING)
		return;

	float px, py;
	phaseCheck->GetPosition(px, py);

	if (state == KOOPA_TROOPA_STATE_WALKING && py - this->y > 10) {
		vx = -vx;

		float pvx, pvy;
		phaseCheck->GetSpeed(pvx, pvy);

		if (pvx <= this->x)
			phaseCheck->SetPosition(x + KOOPA_TROOPA_BBOX_WIDTH, y);
		else phaseCheck->SetPosition(x - KOOPA_TROOPA_BBOX_WIDTH, y);
	}

	phaseCheck->SetSpeed(vx, 1);

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
	if (state != KOOPA_TROOPA_STATE_ATTACKING)
		phaseCheck->Update(dt, coObjects);

	vx += ax * dt;
	vy += ay * dt;

	if (state == KOOPA_TROOPA_STATE_ATTACKING && GetTickCount64() - shell_start > KOOPA_TROOPA_SHELL_TIMEOUT) {
		SetState(KOOPA_TROOPA_STATE_WALKING);
		SetLevel(KOOPA_TROOPA_NORMAL);
		shell_start = -1;
		return;
	}

	if (state == KOOPA_TROOPA_STATE_DIE && GetTickCount64() - die_start > KOOPA_TROOPA_DIE_TIMEOUT) {
		isDeleted = true;
		phaseCheck->Delete();
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CKoopaTroopa::Render()
{
	if (state != KOOPA_TROOPA_STATE_ATTACKING)
		phaseCheck->RenderBoundingBox();

	int aniId = GetAniId();
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();

	float px, py;
	phaseCheck->GetPosition(px, py);
}
