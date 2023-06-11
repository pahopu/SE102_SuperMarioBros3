#pragma once

#ifndef CKOOPAS_H
#define CKOOPAS_H

#include "PhaseChecker.h"
#include "GameObject.h"


#define KOOPA_TROOPA_GRAVITY					0.001f
#define KOOPA_TROOPA_WALKING_SPEED				0.04f
#define KOOPA_TROOPA_SHELL_SPEED				0.2f

#define KOOPA_TROOPA_DIE_DEFLECT				0.2f

#define KOOPA_TROOPA_BBOX_WIDTH					14
#define KOOPA_TROOPA_BBOX_HEIGHT				24
#define KOOPA_TROOPA_BBOX_HEIGHT_DIE			13

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


class CKoopaTroopa : public CGameObject {
protected:
	float ax;
	float ay;

	int level;

	bool isHeld;

	ULONGLONG time_start;

	CGameObject* phaseCheck;

	virtual int IsCollidable() { return state != KOOPA_TROOPA_STATE_DIE && !isHeld; }
	virtual int IsBlocking() { return 0; }
	virtual void Deflected(int direction);

	void OnCollisionWithBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopaTroopa(LPCOLLISIONEVENT e);
	void OnCollisionWithPiranhaPlant(LPCOLLISIONEVENT e);

	int GetAniId();

public:
	CKoopaTroopa(float x, float y): CGameObject(x, y) {
		phaseCheck = new CPhaseChecker(x - KOOPA_TROOPA_BBOX_WIDTH - KOOPA_TROOPA_PHASE_CHECK_WIDTH / 2, y, 
			KOOPA_TROOPA_PHASE_CHECK_WIDTH, KOOPA_TROOPA_PHASE_CHECK_HEIGHT, PHASECHECK_BY_KOOPA_TROOPA);
		phaseCheck->SetSpeed(0, KOOPA_TROOPA_WALKING_SPEED);

		ax = 0;
		ay = KOOPA_TROOPA_GRAVITY;
		time_start = -1;
		level = KOOPA_TROOPA_NORMAL;
		isHeld = 0;

		SetState(KOOPA_TROOPA_STATE_WALKING);
	}

	void SetLevel(int level);
	void SetState(int state);
	void SetNx(int nx) {
		this->nx = nx;
	}

	int GetNx() {
		return nx;
	}

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();

	int GetStateHeld() { return isHeld; }
	void IsHeld() { isHeld = true; }
};

#endif