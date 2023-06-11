#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "AssetIDs.h"
#include "Brick.h"
#include "Goomba.h"

#define ID_ANI_MUSHROOM_SUPER			1511
#define ID_ANI_MUSHROOM_1UP				1512
#define ID_ANI_SUPER_LEAF				1513

#define MUSHROOM_GRAVITY				0.001f
#define MUSHROOM_WALKING_SPEED			0.065f
#define MUSHROOM_CREATE_SPEED			0.01f
#define MUSHROOM_DEFLECTED_SPEED		0.2f

#define MUSHROOM_TYPE_SUPER				1
#define MUSHROOM_TYPE_1UP				2
#define MUSHROOM_TYPE_SUPER_LEAF		3

#define LEAF_DIVERT_TIME				700

#define MUSHROOM_BBOX_WIDTH				16
#define MUSHROOM_BBOX_HEIGHT			16

class CMushroom :public CGameObject {
protected:
	float ax;
	float ay;

	float old_y;

	int type;

	ULONGLONG time_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() {
		return 1;
	}

	virtual int IsBlocking() {
		return 0;
	}

	virtual void OnNoColision(DWORD dt);
	virtual void OnColisionWith(LPCOLLISIONEVENT e);

	void IsDiversion();
	virtual void Deflected(int direction = 0);

public:
	CMushroom(float x, float y, int type);
	int GetType() { return type; }
	void CreatedByBrick();
};