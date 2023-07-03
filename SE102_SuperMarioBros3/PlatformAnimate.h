#pragma once
#include "GameObject.h"

#define PLATFORM_ANIMATE_BBOX_WIDTH				15
#define PLATFORM_ANIMATE_BBOX_HEIGHT			15

#define PLATFORM_ANIMATE_TYPE_BLOCK				0
#define PLATFORM_ANIMATE_TYPE_GATE				1

class CPlatformAnimate : public CGameObject {
protected:
	int type;
	int isAni; // 1: animation, 0: sprite
	int aniOrsprite;

	virtual int IsBlocking() {
		return 1;
	}

public:
	CPlatformAnimate(float x, float y, int AniOrSprite, int Type = 1, int IsAni = 1) : CGameObject(x, y) {
		type = Type;
		isAni = IsAni;
		aniOrsprite = AniOrSprite;
	}

	int GetType() {
		return type;
	}

	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};