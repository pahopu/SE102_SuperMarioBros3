#pragma once
#include "GameObject.h"

#define PLATFORM_ANIMATE_BBOX_WIDTH				15
#define PLATFORM_ANIMATE_BBOX_HEIGHT			15

class CPlatformAnimate : public CGameObject {
protected:
	int animation;

	virtual int IsBlocking() {
		return 0;
	}

public:
	CPlatformAnimate(float x, float y, int ani) : CGameObject(x, y) {
		animation = ani;
	}

	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};