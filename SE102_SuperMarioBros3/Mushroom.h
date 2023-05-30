#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "AssetIDs.h"
#include "Brick.h"

#define ID_ANI_MUSHROOM			1511

#define MUSHROOM_GRAVITY		0.001f
#define MUSHROOM_WALKING_SPEED	0.065f

#define MUSHROOM_BBOX_WIDTH		16
#define MUSHROOM_BBOX_HEIGHT	16

class CMushroom:public CGameObject
{
protected:
	float ax;
	float ay;

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

public:
	CMushroom(float x, float y);
};

