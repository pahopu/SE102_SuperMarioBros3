#include "Bullet.h"
#include "debug.h"
#include "Game.h"
#include "Mario.h"

void CBullet::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x - BULLET_BBOX_WIDTH / 2;
	top = y - BULLET_BBOX_HEIGHT / 2;
	right = left + BULLET_BBOX_WIDTH;
	bottom = top + BULLET_BBOX_HEIGHT;
}

void CBullet::Render() {
	int aniId = ID_ANI_BULLET_FIRE;

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CBullet::OnCollisionWith(LPCOLLISIONEVENT e) {
	if (!dynamic_cast<CMario*>(e->obj)->IsUntouchable()) {
		CMario* mario = dynamic_cast<CMario*>(e->obj);

		switch (mario->GetLevel()) {
		case MARIO_LEVEL_SMALL:
			mario->SetState(MARIO_STATE_DIE);
			break;

		case MARIO_LEVEL_BIG:
			mario->SetLevel(MARIO_LEVEL_SMALL);
			mario->StartUntouchable();
			break;

		case MARIO_LEVEL_RACOON:
			mario->SetLevel(MARIO_LEVEL_BIG);
			mario->StartUntouchable();
			break;
		}
	}
}

void CBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	x += vx * dt;
	y += vy * dt;

	// If bullet out of camera screen, it will disappear
	float cx, cy, cw, ch;
	CGame::GetInstance()->GetCamPos(cx, cy);
	if (x < cx || (x > cx + 320) || y < cy || (y > cy + 240))
		this->Delete();

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
