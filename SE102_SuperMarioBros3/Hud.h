#pragma once
#include "GameObject.h"

#define ID_ANI_P_CHANGING_COLOR					8888

#define EFFECT_SPEED							0.02f

#define HUD_BBOX_WIDTH							153
#define HUD_BBOX_HEIGHT							29

#define GIFTBOX_BBOX_WIDTH						24
#define GIFTBOX_BBOX_HEIGHT						29

#define NUMBER_WIDTH							7
#define NUMBER_HEIGHT							6

#define MARIO_SYMBOL_WIDTH						15
#define MARIO_SYMBOL_HEIGHT						7

#define ROW_ABOVE_Y								8	// contain worldmap name, P status and money
#define ROW_BELOW_Y								16	// contain character, life, score and time

#define COLUMN_ML_X								5	// M or L (Mario or Lugi) 
#define COLUMN_SPEED_X							53	

#define COLUMN_WL_X								45	// current world, life
#define COLUMN_SCORE_X							108 // Score
#define COLUMN_MT_X								148	// money and time

#define LENGTH_SCORE							8
#define LENGTH_TIME								3

#define ADJUST									3

class CHud : public CGameObject {
protected:
	int coin;
	int life;
	int score;

	vector<int> gifts;

	// Parameter length use in case option = 1
	// Option 0: Normal draw (example: 100 -> draw 100)
	// Option 1: Special draw (example: 100 -> draw 0000100)
	void RenderNumber(float x, float y, int number, int length = 0, int option = 0);

public:
	CHud(float x, float y) : CGameObject(x, y) {
		gifts.clear();
		coin = 0;
		life = 3;
		score = 0;
	}

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
		this->Update();
	}

	void Update();
	void Render();

	virtual int IsBlocking() {
		return 0; 
	}

	void CollectCoin() { 
		coin++;
	}

	void Collect1UpMushroom() {
		life++;
	}

	void MarioDeath() { 
		life--; 
	}

	int AddScore(int Score) { 
		score = Score; 
	}

	int CanRevive() {
		return life > 0; 
	}
};

