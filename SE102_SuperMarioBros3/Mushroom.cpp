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

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMushroom::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_MUSHROOM)->Render(x, y);
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

	if (dynamic_cast<CBrick*>(e->obj)) return;

	if (e->ny != 0)
		vy = 0;
	else if (e->nx != 0)
		vx = -vx;
}

CMushroom::CMushroom(float x, float y):CGameObject(x, y) {
	ax = 0;
	ay = MUSHROOM_GRAVITY;

	vx = MUSHROOM_WALKING_SPEED;
}

