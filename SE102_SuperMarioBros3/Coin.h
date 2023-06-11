#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_COIN					11000
#define ID_ANI_COIN_DEFLECT			11001

#define COIN_DEFLECT				0.4f
#define COIN_GRAVITY				0.001f

//#define	COIN_WIDTH					10
#define COIN_BBOX_WIDTH				15
#define COIN_BBOX_HEIGHT			16

class CCoin : public CGameObject {
	float ay;

public:
	CCoin(float x, float y) : CGameObject(x, y) { ay = 0; vy = 0; }
	void Render();
	void Update(DWORD dt);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	void Deflected(int direction);
};