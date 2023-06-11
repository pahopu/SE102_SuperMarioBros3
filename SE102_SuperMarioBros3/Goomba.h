#pragma once
#include "GameObject.h"

#define GOOMBA_GRAVITY					0.001f
#define GOOMBA_WALKING_SPEED			0.04f
#define GOOMBA_DIE_DEFLECT				0.2f

#define GOOMBA_BBOX_WIDTH				16
#define GOOMBA_BBOX_HEIGHT				11
#define GOOMBA_BBOX_HEIGHT_DIE			7

#define GOOMBA_DIE_TIMEOUT				500

#define GOOMBA_STATE_WALKING			100
#define GOOMBA_STATE_DIE_BY_JUMP		200
#define GOOMBA_STATE_DIE_BY_ATTACK		300

#define ID_ANI_GOOMBA_WALKING			5000
#define ID_ANI_GOOMBA_DIE_BY_JUMP		5001

#define GOOMBA_TYPE_NORMAL				1
#define GOOMBA_TYPE_RED_FLY				2

class CGoomba : public CGameObject
{
protected:
	float ax;				
	float ay;

	int type;

	ULONGLONG time_start;

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Render();

	virtual int IsCollidable() { return state != GOOMBA_STATE_DIE_BY_JUMP && state != GOOMBA_STATE_DIE_BY_ATTACK; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

	void OnCollisionWithBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopaTroopa(LPCOLLISIONEVENT e);
	
	int getAniId();

public: 	
	CGoomba(float x, float y, int type);

	virtual void SetState(int state);
	virtual void Deflected(int direction);

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
};