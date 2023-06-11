#include "Mushroom.h"
#include "Mario.h"
#include "PlayScene.h"

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

	if (ay == 0 && (old_y - y) >= MUSHROOM_BBOX_HEIGHT) {
		ay = MUSHROOM_GRAVITY;
		vx = MUSHROOM_WALKING_SPEED;
		if (type = MUSHROOM_TYPE_SUPER_LEAF)
			time_start = GetTickCount64();
	}
	else if (type == MUSHROOM_TYPE_SUPER_LEAF && vy > 0) {
		IsDiversion();
		vy = ay * dt;
		if ((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene()) {
			CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
			vector<LPGAMEOBJECT> object;
			object.push_back(mario);
			CCollision::GetInstance()->Process(this, dt, &object);
		}
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMushroom::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (type == MUSHROOM_TYPE_SUPER)
		animations->Get(ID_ANI_MUSHROOM_SUPER)->Render(x, y);
	else if(type == MUSHROOM_TYPE_1UP)
		animations->Get(ID_ANI_MUSHROOM_1UP)->Render(x, y);
	else animations->Get(ID_ANI_SUPER_LEAF)->Render(x, y);
	//RenderBoundingBox();
}

void CMushroom::OnNoColision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CMushroom::OnColisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CMario*>(e->obj)) {
		CMario* mario = dynamic_cast<CMario*>(e->obj);

		if (type == MUSHROOM_TYPE_1UP) {
			// + 1 up
		}
		else {
			switch (mario->GetLevel()) {
			case MARIO_LEVEL_SMALL:
				mario->SetLevel(MARIO_LEVEL_BIG);
				break;

			case MARIO_LEVEL_BIG:
				mario->SetLevel(MARIO_LEVEL_RACOON);
				break;
			}
		}
		Delete();
	}
	else if (dynamic_cast<CBrick*>(e->obj)) {
		CBrick* brick = dynamic_cast<CBrick*>(e->obj);
		if (brick->IsAttacking()) {
			Deflected();
			vx = -vx;
		}
	}

	if (!e->obj->IsBlocking() || (dynamic_cast<CGoomba*>(e->obj)) || (dynamic_cast<CMushroom*>(e->obj)))
		return;

	if (e->ny != 0)
		vy = 0;
	else if (e->nx != 0)
		vx = -vx;
}

void CMushroom::IsDiversion()
{
	if (GetTickCount64() - time_start >= LEAF_DIVERT_TIME) {
		vx = -vx;
		time_start = GetTickCount64();
	}
}

void CMushroom::Deflected(int direction) {
	vy = -MUSHROOM_DEFLECTED_SPEED;
}

CMushroom::CMushroom(float x, float y, int type) :CGameObject(x, y) {
	old_y = time_start = ax = 0;
	this->type = type;

	if (type == MUSHROOM_TYPE_SUPER_LEAF)
		time_start = GetTickCount64();

	ay = MUSHROOM_GRAVITY;
	vx = MUSHROOM_WALKING_SPEED;
}

void CMushroom::CreatedByBrick() {
	if (type == MUSHROOM_TYPE_SUPER_LEAF) {
		Deflected();
		return;
	}

	old_y = y;
	ay = vx = 0;
	vy = -MUSHROOM_CREATE_SPEED;
}
