#include "Mushroom.h"

void CMushroom::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	// Because coordinate is in center of an object, we calculate like bellow to have bbox
	left = x - MUSHROOM_BBOX_WIDTH / 2;
	top = y - MUSHROOM_BBOX_HEIGHT / 2;
	right = left + MUSHROOM_BBOX_WIDTH;
	bottom = top + MUSHROOM_BBOX_HEIGHT;
}

void CMushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vx += ax * dt;
	vy += ay * dt;

	if (type == SUPER_LEAF) {
		OnNoColision(dt);
		IsDiversion();
		vy = ay * dt;

		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMushroom::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (type == MUSHROOM_SUPER)
		animations->Get(ID_ANI_MUSHROOM_SUPER)->Render(x, y);
	else if(type == MUSHROOM_1UP)
		animations->Get(ID_ANI_MUSHROOM_1UP)->Render(x, y);
	else 
		animations->Get(ID_ANI_SUPER_LEAF)->Render(x, y);
	//RenderBoundingBox();
}

void CMushroom::OnNoColision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CMushroom::OnColisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;

	if (dynamic_cast<CMushroom*>(e->obj)) return;
	if (dynamic_cast<CGoomba*>(e->obj)) return;

	if (e->ny != 0)
		vy = 0;
	else if (e->nx != 0)
		vx = -vx;
}

void CMushroom::IsDiversion()
{
	if (GetTickCount64() - start >= LEAF_DIVERT_TIME) {
		vx = -vx;
		start = GetTickCount64();
	}
}

CMushroom::CMushroom(float x, float y, int type) :CGameObject(x, y) {
	ax = 0;
	ay = MUSHROOM_GRAVITY;
	vx = MUSHROOM_WALKING_SPEED;

	this->type = type;
	if (type == SUPER_LEAF) {
		ax = MUSHROOM_WALKING_SPEED / 1000;
		ay = MUSHROOM_GRAVITY / 6;
		vx = MUSHROOM_WALKING_SPEED / 3;

		start = GetTickCount64();
	}
}