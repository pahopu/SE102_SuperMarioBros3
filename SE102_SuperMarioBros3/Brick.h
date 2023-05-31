#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define BRICK_GRAVITY				0.002f
#define BRICK_TRANSFORM_DEFLECT		0.2f

#define BRICK_BREAK_DEFLECT_X		0.1f
#define BRICK_BREAK_DEFLECT_Y		0.4f

#define BRICK_BREAK_TIMEOUT			500

#define BRICK_BBOX_WIDTH			15
#define BRICK_BBOX_HEIGHT			15

#define BRICK_BREAK_BBOX_WIDTH		13
#define BRICK_BREAK_BBOX_HEIGHT		8

#define BRICK_TYPE_GOLD				1
#define BRICK_TYPE_QUESTION			2
#define BRICK_TYPE_EMPTY			3
#define BRICK_TYPE_BREAK			4

#define BRICK_STATE_DEFLECT			1

#define ID_ANI_GOLD_BRICK			10000
#define ID_ANI_QUESTION_BRICK		10001
#define ID_ANI_EMPTY_BRICK			10002
#define ID_ANI_BREAK_BRICK			10003


class CBrick : public CGameObject {
protected:
	float old_y;

	float ax;
	float ay;

	int type;
	ULONGLONG time_start;

	vector<CBrick*> bricks;

	virtual int IsBlocking() { return type != BRICK_TYPE_BREAK; }
	virtual void Deflected(int direction);

	virtual void OnNoCollision(DWORD dt) {}
	virtual void OnCollisionWith(LPCOLLISIONEVENT e) {};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

	void Update(DWORD dt);

public:
	CBrick(float x, float y, int type) : CGameObject(x, y) {
		this->type = -1;
		SetType(type);

		time_start = -1;
		state = -1;

		old_y = ax = ay = vx = vy = 0;
	}

	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	int GetType() { return type; }
	void SetType(int type);
	void SetState(int State);
	bool IsAttacking();
};