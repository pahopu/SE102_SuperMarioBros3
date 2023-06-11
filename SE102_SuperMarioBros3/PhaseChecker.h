#pragma once

#include "GameObject.h"
#include "Goomba.h"
#include "Brick.h"
#include "PiranhaPlant.h"

#define PHASE_CHECKER_GRAVITY				0.001f

#define PHASECHECK_ATTACK_SPEED				1.4f
#define PHASECHECK_ATTACK_RANGE				3.0f

#define PHASECHECK_BY_KOOPA_TROOPA			10
#define PHASECHECK_BY_MARIO					20

class CKoopaTroopa;

class CPhaseChecker : public CGameObject {
protected:
	int width;
	int height;

	int type;

	float ax;
	float ay;

	float old_x;

	virtual int IsCollidable() { return 1; }
	virtual int IsBlocking() { return 0; }

	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

	void OnCollisionWithBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopaTroopa(LPCOLLISIONEVENT e);
	void OnCollisionWithPiranhaPlant(LPCOLLISIONEVENT e);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

	virtual void Render() {
		RenderBoundingBox();
	}

public:
	CPhaseChecker(float x, float y, int w, int h, int t) : CGameObject(x, y) {
		ax = vy = 0;
		ay = PHASE_CHECKER_GRAVITY;

		width = w;
		height = h;
		type = t;

		old_x = x;
	}

	void Attack(int direction) {
		vx += PHASECHECK_ATTACK_SPEED * direction;
		old_x = x;
	}

	bool isAttacking() {
		return abs(vx) >= PHASECHECK_ATTACK_SPEED;
	}

	int GetType() {
		return type;
	}
};