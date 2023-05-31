#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define BRICK_GRAVITY				0.002f
#define BRICK_TRANSFORM_DEFLECT		0.2f

#define BRICK_BREAK_TIMEOUT			500

#define BRICK_BBOX_WIDTH			15
#define BRICK_BBOX_HEIGHT			15

#define BRICK_TYPE_GOLD				1
#define BRICK_TYPE_QUESTION			2
#define BRICK_TYPE_EMPTY			3

#define ID_ANI_GOLD_BRICK			10000
#define ID_ANI_QUESTION_BRICK		10001
#define ID_ANI_EMPTY_BRICK			10002


class CBrick : public CGameObject {
protected:
	float old_y;

	float ax;
	float ay;

	int type;
	ULONGLONG time_start;

	virtual void OnNoCollision(DWORD dt) {}
	virtual void OnCollisionWith(LPCOLLISIONEVENT e) {};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

public:
	CBrick(float x, float y, int type) : CGameObject(x, y) {
		SetType(type);
		time_start = -1;
		old_y = ax = ay = vx = vy = 0;
	}

	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	int GetType() { return type; }
	void SetType(int type);
};