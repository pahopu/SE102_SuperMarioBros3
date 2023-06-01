#include "Goomba.h"
#include "Brick.h"

CGoomba::CGoomba(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = GOOMBA_GRAVITY;
	time_start = -1;
	SetState(GOOMBA_STATE_WALKING);
}

void CGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == GOOMBA_STATE_DIE_BY_JUMP)
	{
		left = x - GOOMBA_BBOX_WIDTH / 2;
		top = y - GOOMBA_BBOX_HEIGHT_DIE / 2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT_DIE;
	}
	else
	{
		left = x - GOOMBA_BBOX_WIDTH / 2;
		top = y - GOOMBA_BBOX_HEIGHT / 2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT;
	}
}

void CGoomba::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	//if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CGoomba*>(e->obj)) return;

	if (e->ny != 0)
		vy = 0;
	else if (e->nx != 0)
		vx = -vx;

	if (dynamic_cast<CBrick*>(e->obj))
		OnCollisionWithBrick(e);
}

int CGoomba::getAniId()
{
	int aniId = ID_ANI_GOOMBA_WALKING;
	if (state == GOOMBA_STATE_DIE_BY_JUMP)
		aniId = ID_ANI_GOOMBA_DIE_BY_JUMP;
	return aniId;
}

void CGoomba::OnCollisionWithBrick(LPCOLLISIONEVENT e)
{
	CBrick* brick = dynamic_cast<CBrick*>(e->obj);

	if (brick->IsAttacking() && e->ny != 0) {
		SetState(GOOMBA_STATE_DIE_BY_ATTACK);

		float bx, by;
		brick->GetPosition(bx, by);

		if (bx < x)
			this->Deflected(DEFLECT_DIRECTION_RIGHT);
		else this->Deflected(DEFLECT_DIRECTION_LEFT);
	}
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ((state == GOOMBA_STATE_DIE_BY_JUMP || state == GOOMBA_STATE_DIE_BY_ATTACK) && 
		(GetTickCount64() - time_start > GOOMBA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CGoomba::Render()
{
	int aniId = getAniId();

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CGoomba::Deflected(int direction)
{
	vy = -GOOMBA_DIE_DEFLECT;
	ay = GOOMBA_GRAVITY;

	vx = direction * GOOMBA_WALKING_SPEED;
	ax = 0;
}

void CGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case GOOMBA_STATE_DIE_BY_JUMP:
		time_start = GetTickCount64();
		y += (GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;

	case GOOMBA_STATE_DIE_BY_ATTACK:
		time_start = GetTickCount64();
		vx = GOOMBA_WALKING_SPEED;
		vy = -GOOMBA_DIE_DEFLECT;
		ax = 0;
		break;

	case GOOMBA_STATE_WALKING:
		vx = -GOOMBA_WALKING_SPEED;
		break;
	}
}
