#pragma once

#include "GameObject.h"

#define PHASE_CHECKER_GRAVITY	0.002f

class CPhaseChecker : public CGameObject
{
protected:
	int width;
	int height;

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
		left = x - width / 2;
		top = y - height / 2;
		right = left + width;
		bottom = top + height;
	}

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
	{
		vx += ax * dt;
		vy += ay * dt;

		CGameObject::Update(dt, coObjects);
		CCollision::GetInstance()->Process(this, dt, coObjects);
	}
	virtual void Render()
	{
		RenderBoundingBox();
	}

public:
	CPhaseChecker(float x, float y, int w, int h) : CGameObject(x, y)
	{
		ax = 0;
		ay = PHASE_CHECKER_GRAVITY;

		width = w;
		height = h;

		vy = 0;
	}
	
	void SetAy(float ay) {
		this->ay = ay;
	}
};