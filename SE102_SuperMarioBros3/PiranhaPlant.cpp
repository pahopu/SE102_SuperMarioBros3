#include "PiranhaPlant.h"
#include "Mario.h"
#include "PlayScene.h"
#include "Game.h"
#include "debug.h"

void CPiranhaPlant::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	if (type == PIRANHA_TYPE_RED_FIRE) {
		left = x - PIRANHA_RED_BBOX_WIDTH / 2;
		top = y - PIRANHA_RED_BBOX_HEIGHT / 2;
		right = left + PIRANHA_RED_BBOX_WIDTH;
		bottom = top + PIRANHA_RED_BBOX_HEIGHT;
	}
	else {
		left = x - PIRANHA_GREEN_BBOX_WIDTH / 2;
		top = y - PIRANHA_GREEN_BBOX_HEIGHT / 2;
		right = left + PIRANHA_GREEN_BBOX_WIDTH;
		bottom = top + PIRANHA_GREEN_BBOX_HEIGHT;
	}
}

void CPiranhaPlant::Render() {
	int aniId = GetAniId();

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CPiranhaPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	vy += ay * dt;
	y += vy * dt;

	switch (state) {
	case PIRANHA_STATE_UP:
		switch (type) {
		case PIRANHA_TYPE_GREEN:
		case PIRANHA_TYPE_GREEN_FIRE:
			if (old_y - y > PIRANHA_GREEN_BBOX_HEIGHT) {
				y = old_y - PIRANHA_GREEN_BBOX_HEIGHT;
				SetState(PIRANHA_STATE_ATTACK);
			}
			break;

		case PIRANHA_TYPE_RED_FIRE:
			if (old_y - y > PIRANHA_RED_BBOX_HEIGHT) {
				y = old_y - PIRANHA_RED_BBOX_HEIGHT;
				SetState(PIRANHA_STATE_ATTACK);
			}
			break;
		}
		break;

	case PIRANHA_STATE_DOWN:
		if (y - old_y >= 0) {
			y = old_y;
			SetState(PIRANHA_STATE_IDLE);
		}
		break;

	case PIRANHA_STATE_ATTACK:
	case PIRANHA_STATE_IDLE:
		if ((GetTickCount64() - time_start) > PIRANHA_ATTACK_IDLE_TIME) {
			time_start = 0;
			if (state == PIRANHA_STATE_IDLE) SetState(PIRANHA_STATE_UP);
			else if (state == PIRANHA_STATE_ATTACK) SetState(PIRANHA_STATE_DOWN);
		}
		break;
	}

	//Get position of Mario
	if (dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene()))
		dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene())->GetPlayer()->GetPosition(mario_x, mario_y);

	CGameObject::Update(dt, coObjects);
}

int CPiranhaPlant::GetAniId()
{
	int aniId = -1;
	switch (type) {
	case PIRANHA_TYPE_GREEN:
		aniId = ID_ANI_PIRANHA_GREEN;
		break;
	case PIRANHA_TYPE_GREEN_FIRE:
		if (mario_x < x) {
			aniId = ID_ANI_PIRANHA_GREEN_FIRE_LEFT;
			if (state > PIRANHA_STATE_DOWN) {
				if (mario_y < y) aniId = ID_ANI_PIRANHA_GREEN_TARGET_TOP_LEFT;
				else aniId = ID_ANI_PIRANHA_GREEN_TARGET_BOTTOM_LEFT;
			}
		}
		else {
			aniId = ID_ANI_PIRANHA_GREEN_FIRE_RIGHT;
			if (state > PIRANHA_STATE_DOWN) {
				if (mario_y < y) aniId = ID_ANI_PIRANHA_GREEN_TARGET_TOP_RIGHT;
				else aniId = ID_ANI_PIRANHA_GREEN_TARGET_BOTTOM_RIGHT;
			}
		}
		break;
	case PIRANHA_TYPE_RED_FIRE:
		if (mario_x < x) {
			aniId = ID_ANI_PIRANHA_RED_FIRE_LEFT;
			if (state > PIRANHA_STATE_DOWN) {
				if (mario_y < y) aniId = ID_ANI_PIRANHA_RED_TARGET_TOP_LEFT;
				else aniId = ID_ANI_PIRANHA_RED_TARGET_BOTTOM_LEFT;
			}
		}
		else {
			aniId = ID_ANI_PIRANHA_RED_FIRE_RIGHT;
			if (state > PIRANHA_STATE_DOWN) {
				if (mario_y < y) aniId = ID_ANI_PIRANHA_RED_TARGET_TOP_RIGHT;
				else aniId = ID_ANI_PIRANHA_RED_TARGET_BOTTOM_RIGHT;
			}
		}
		break;
	}
	DebugOut(L"%d", aniId);
	return aniId;
}

void CPiranhaPlant::SetState(int state) {
	CGameObject::SetState(state);
	switch (state) {
	case PIRANHA_STATE_UP:
		vy = -PIRANHA_UP_DOWN_SPEED;
		break;
	case PIRANHA_STATE_DOWN:
		vy = PIRANHA_UP_DOWN_SPEED;
		break;
	case PIRANHA_STATE_ATTACK:
		time_start = GetTickCount64();
		vy = 0;
		break;
	case PIRANHA_STATE_IDLE:
		time_start = GetTickCount64();
		vy = 0;
		break;
	}
}
