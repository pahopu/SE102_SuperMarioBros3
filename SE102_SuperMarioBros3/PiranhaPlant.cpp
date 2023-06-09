#include "PiranhaPlant.h"

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
		aniId = ID_ANI_PIRANHA_GREEN_FIRE_LEFT;
		break;
	case PIRANHA_TYPE_RED_FIRE:
		aniId = ID_ANI_PIRANHA_RED_FIRE_LEFT;
		break;
	}
	return aniId;
}

void CPiranhaPlant::SetState(int state) {
	CGameObject::SetState(state);
	switch (state) {
	case PIRANHA_STATE_UP:
		ay = 0;
		break;
	case PIRANHA_STATE_DOWN:
		ay = 0;
		break;
	case PIRANHA_STATE_ATTACK:
		ay = 0;
		break;
	}
}
