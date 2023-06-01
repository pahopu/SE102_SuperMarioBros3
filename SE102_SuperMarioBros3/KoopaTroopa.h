#pragma once

#include "GameObject.h"

#define KOOPA_TROOPA_GRAVITY					0.002f
#define KOOPA_TROOPA_WALKING_SPEED				0.05f
#define KOOPA_TROOPA_SHELL_SPEED				0.2f

#define KOOPA_TROOPA_DIE_DEFLECT				0.2f

#define KOOPA_TROOPA_BBOX_WIDTH					14
#define KOOPA_TROOPA_BBOX_HEIGHT				24
#define KOOPA_TROOPA_BBOX_HEIGHT_DIE			15

#define KOOPA_TROOPA_PHASE_CHECK_WIDTH			14
#define KOOPA_TROOPA_PHASE_CHECK_HEIGHT			24

#define KOOPA_TROOPA_SHELL_TIMEOUT				5000
#define KOOPA_TROOPA_DIE_TIMEOUT				500

#define KOOPA_TROOPA_STATE_WALKING				100
#define KOOPA_TROOPA_STATE_SHELL				200
#define KOOPA_TROOPA_STATE_ATTACKING			300
#define KOOPA_TROOPA_STATE_DIE					400

#define KOOPA_TROOPA_NORMAL						1
#define KOOPA_TROOPA_SHELL						2

#define ID_ANI_KOOPA_TROOPA_WALKING_LEFT		6000
#define ID_ANI_KOOPA_TROOPA_WALKING_RIGHT		6010
#define ID_ANI_KOOPA_TROOPA_SHELL				6001
#define ID_ANI_KOOPA_TROOPA_ATTACKING			6002
#define ID_ANI_KOOPA_TROOPA_REFORM				6003


class CPhaseCheck : public CGameObject
{
protected:
	float ax;
	float ay;

	virtual int IsCollidable() { return 1; }
	virtual int IsBlocking() { return 0; }

	virtual void OnNoCollision(DWORD dt)
	{
		x += vx * dt;
		y += vy * dt;
	}
	virtual void OnCollisionWith(LPCOLLISIONEVENT e)
	{
		if (e->ny != 0)
		{
			vy = 0;
		}
	}

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom)
	{
		left = x - KOOPA_TROOPA_PHASE_CHECK_WIDTH / 2;
		top = y - KOOPA_TROOPA_PHASE_CHECK_HEIGHT / 2;
		right = left + KOOPA_TROOPA_PHASE_CHECK_WIDTH;
		bottom = top + KOOPA_TROOPA_PHASE_CHECK_HEIGHT;
	}

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
	{
		vy += ay * dt;
		vx += ax * dt;

		CGameObject::Update(dt, coObjects);
		CCollision::GetInstance()->Process(this, dt, coObjects);
	}
	virtual void Render()
	{
		RenderBoundingBox();
	}

public:
	//CPhaseCheck() : CGameObject() {}
	CPhaseCheck(float x, float y) : CGameObject(x, y)
	{
		this->ax = 0;
		this->ay = KOOPA_TROOPA_GRAVITY;
		vx = -KOOPA_TROOPA_WALKING_SPEED;
		vy = 0;
	}
};

class CKoopaTroopa : public CGameObject {
protected:
	float ax;
	float ay;

	int level;

	ULONGLONG time_start;

	CGameObject* phaseCheck;

	virtual int IsCollidable() { return state != KOOPA_TROOPA_STATE_DIE; }
	virtual int IsBlocking() { return 0; }
	virtual void Deflected(int direction);

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopaTroopa(LPCOLLISIONEVENT e);

	int GetAniId();

public:
	CKoopaTroopa(float x, float y): CGameObject(x, y) {
		ax = 0;
		ay = KOOPA_TROOPA_GRAVITY;
		level = KOOPA_TROOPA_NORMAL;
		time_start = -1;
		phaseCheck = new CPhaseCheck(x - KOOPA_TROOPA_BBOX_WIDTH - KOOPA_TROOPA_PHASE_CHECK_WIDTH / 2, y);
		
		SetState(KOOPA_TROOPA_STATE_WALKING);
	}

	void SetLevel(int level);
	void SetState(int state);
	void SetNx(int nx) {
		this->nx = nx;
	}

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
};

