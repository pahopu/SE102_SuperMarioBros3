#pragma once

#include "GameObject.h"

#define PIRANHA_UP_DOWN_ACCEL				0.001f

#define PIRANHA_TYPE_GREEN					1
#define PIRANHA_TYPE_GREEN_FIRE				2
#define PIRANHA_TYPE_RED_FIRE				3

#define PIRANHA_STATE_UP					111
#define PIRANHA_STATE_DOWN					222
#define PIRANHA_STATE_ATTACK				333

#define PIRANHA_GREEN_BBOX_WIDTH			15
#define PIRANHA_GREEN_BBOX_HEIGHT			23

#define PIRANHA_RED_BBOX_WIDTH				15
#define PIRANHA_RED_BBOX_HEIGHT				31

#define ID_ANI_PIRANHA_GREEN				7000

#define ID_ANI_PIRANHA_GREEN_FIRE_LEFT		7001
#define ID_ANI_PIRANHA_GREEN_FIRE_RIGHT		7011

#define ID_ANI_PIRANHA_RED_FIRE_LEFT		7002
#define ID_ANI_PIRANHA_RED_FIRE_RIGHT		7012

class CPiranhaPlant : public CGameObject {
protected:
	int ay;
	int type;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Render();

	virtual int IsCollidable() { return 0; }
	virtual int IsBlocking() { return 0; }

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

	virtual void OnNoCollision(DWORD dt) {}
	virtual void OnCollisionWith(LPCOLLISIONEVENT e) {}

	int GetAniId();
public:
	CPiranhaPlant(float x, float y, int type) :CGameObject(x, y) {
		this->type = type;
		vy = 0;
		vx = 0;
		ay = 0;
		SetState(PIRANHA_STATE_UP);
	}

	virtual void SetState(int state);
};

