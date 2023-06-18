#pragma once

/*****************************
Using this in case: when I should update Koopa Para Troopa and Para Goomba
****************************/

#include "GameObject.h"
#include "debug.h"

#define INVISIBLE_BBOX_WIDTH				10
#define INVISIBLE_BBOX_HEIGHT				500

#define INVISIBLE_OBJECT_TYPE_GOOMBA		1
#define INVISIBLE_OBJECT_TYPE_KOOPA_TROOPA	2

class CInvisibleObject : public CGameObject {
	int type;

	bool isActived;

public:
	CInvisibleObject(float x, float y, int t) : CGameObject(x, y) {
		type = t;
		isActived = false;
	}

	void Render() { 
		RenderBoundingBox(); 
	}

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	int IsBlocking() { 
		return 0;
	}

	void Activating() { 
		isActived = true; 
	}

	int GetType() {
		return type;
	}

	bool IsActived() {
		//DebugOut(L"isActived: %d\n", isActived); 
		return isActived; 
	}
};
