#pragma once

#include "Game.h"
#include "Mario.h"
#include "Scene.h"
#include "Goomba.h"
#include "Portal.h"
#include "Control.h"
#include "Mushroom.h"
#include "Platform.h"
#include "Textures.h"
#include "GameObject.h"
#include "KoopaTroopa.h"
#include "PlatformAnimate.h"

#define WAITING_KOOPA_TROOPA_ATTACK_TIME		2000
#define CURTAIN_FLYING_TIME						3000

#define CURTAIN_FLYING							100
#define GAMENAME_DOWNING						200

#define MARIO_WALKING_TIME						1350
#define MARIO_JUMPING_TIME						(MARIO_WALKING_TIME + 1100)

#define LUIGI_HOLDING_KOOPA_TROOPA				1

#define MARIO_JUMP_ON_GOOMBA					11

#define LUIGI_KICKING_KOOPA_TROOPA				111

#define MARIO_JUMP_ON_KOOPA_TROOPA				1111
#define MARIO_HOLDING_KOOPA_TROOPA				2222

#define KOOPA_TROOPA_ATTACKING					4444

#define KOOPA_TROOPA_WALKING					555

class CIntroScene : public CScene {
protected:
	ULONGLONG timeStart;

	int flag; // determine curtain flying or game name downing
	int stateOfMario;

	float Number3Original_y = 0;

	LPGAMEOBJECT player[2];
	ULONGLONG MarioWalkingStart;

	CPortal* portal;
	CPlatformAnimate* Number3;

	vector<LPGAMEOBJECT> objects;
	vector<CPlatform*> platformObjects;
	vector<LPGAMEOBJECT> ItemsAndEnemies;

	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);

	void LoadAssets(LPCWSTR assetFile);

	void Action(DWORD dt) {
		int Screen_Width = CGame::GetInstance()->GetBackBufferWidth();
		int Screen_Height = CGame::GetInstance()->GetBackBufferHeight();

		CMario* Luigi = (CMario*)player[0];
		CMario* Mario = (CMario*)player[1];

		if (flag == CURTAIN_FLYING) {
			float number3_x, number3_y;
			Number3->GetPosition(number3_x, number3_y);
			Number3->SetPosition(number3_x, number3_y - 0.1f * dt);

			for (int i = 3; i < platformObjects.size(); i++) {
				int id = platformObjects[i]->GetSpriteIDBegin();

				float x, y;
				platformObjects[i]->GetPosition(x, y);
				if (GetTickCount64() - timeStart > CURTAIN_FLYING_TIME) {
					flag = 0;
					timeStart = 0;
					MarioWalkingStart = GetTickCount64();
				}
				else platformObjects[i]->SetPosition(x, y - 0.1f * dt);
			}
		}
		else if (flag == GAMENAME_DOWNING) {
			float number3_x, number3_y;
			Number3->GetPosition(number3_x, number3_y);
			Number3->SetPosition(number3_x, number3_y + 0.1f * dt);

			float adjust = (Number3Original_y - number3_y);
			if (adjust <= 0) { // Number3Original_y <= number3_y
				flag = 0;
				Number3->SetPosition(number3_x, Number3Original_y);

				CGameObject* obj;

				obj = new CGoomba(number3_x - 50, 0, GOOMBA_TYPE_NORMAL, 1);
				float vx, vy;
				obj->GetSpeed(vx, vy);
				obj->SetSpeed(0, vy);

				ItemsAndEnemies.push_back(obj);

				obj = new CKoopaTroopa(number3_x - 25, number3_y, KOOPA_TROOPA_TYPE_GREEN, 1);
				obj->SetState(KOOPA_TROOPA_STATE_SHELL);
				ItemsAndEnemies.push_back(obj);

				obj = new CKoopaTroopa(number3_x + 35, number3_y, KOOPA_TROOPA_TYPE_GREEN, 1);
				obj->SetState(KOOPA_TROOPA_STATE_SHELL);
				ItemsAndEnemies.push_back(obj);

				obj = new CMushroom(number3_x + 50, 0, MUSHROOM_TYPE_SUPER);
				ItemsAndEnemies.push_back(obj);

				obj = new CMushroom(number3_x - 7.5f, number3_y, MUSHROOM_TYPE_SUPER_LEAF);
				ItemsAndEnemies.push_back(obj);

				stateOfMario = MARIO_STATE_JUMP;
				Mario->SetState(stateOfMario);
				DebugOut(L"Mario jump");

				for (auto obj : ItemsAndEnemies)
					if (dynamic_cast<CKoopaTroopa*>(obj))
						obj->SetState(KOOPA_TROOPA_STATE_SHELL);
			}

			for (int i = 3; i < platformObjects.size(); i++) {
				int id = platformObjects[i]->GetSpriteIDBegin();

				float x, y;
				platformObjects[i]->GetPosition(x, y);
				if (!(id == ID_SPRITE_CURTAIN_1 || id == ID_SPRITE_CURTAIN_2)) {
					if (adjust <= 0) platformObjects[i]->SetPosition(x, y - adjust);
					else platformObjects[i]->SetPosition(x, y + 0.1f * dt);
				}
			}

			float x, y;
			platformObjects[0]->GetPosition(x, y); // get position of stage
			platformObjects[2]->SetPosition(x, y + 77); // set position of black screen
		}

		if (MarioWalkingStart != 0) {
			// Luigi touch top of the screen
			float x, y;
			Luigi->GetPosition(x, y);

			if (y - 20 <= 0) {
				Luigi->GetSpeed(x, y);
				Luigi->SetSpeed(x, 0);
				flag = GAMENAME_DOWNING;
			}

			ULONGLONG delta = GetTickCount64() - MarioWalkingStart;
			if (delta < MARIO_WALKING_TIME && player[0]->GetState() != MARIO_STATE_WALKING_RIGHT) {
				Luigi->SetState(MARIO_STATE_WALKING_RIGHT);
				Mario->SetState(MARIO_STATE_WALKING_LEFT);
				Luigi->SetMaxVx(0.0758f);
			}
			else if (delta > MARIO_WALKING_TIME && stateOfMario != MARIO_STATE_JUMP) {
				Mario->SetState(MARIO_STATE_IDLE);
				stateOfMario = MARIO_STATE_JUMP;
			}
			else if (delta > MARIO_WALKING_TIME && delta < MARIO_JUMPING_TIME 
				&& stateOfMario == MARIO_STATE_JUMP && player[0]->GetState() != MARIO_STATE_JUMP)
				Luigi->SetState(MARIO_STATE_JUMP);
			else if (delta > MARIO_JUMPING_TIME) {
				Mario->SetState(MARIO_STATE_SIT_RELEASE);
				MarioWalkingStart = 0;
				DebugOut(L"\nMario sit release");
			}
		}

		// Excepting Mario falling 
		float x, y;
		player[0]->GetPosition(x, y);

		if (x > CGame::GetInstance()->GetBackBufferWidth() + 50)
			player[0]->SetState(MARIO_STATE_IDLE);

		// Luigi
		if (((CMario*)player[0])->GetLevel() != MARIO_LEVEL_BIG)
			((CMario*)player[0])->SetLevel(MARIO_LEVEL_BIG);

		if (Mario->GetLevel() == MARIO_LEVEL_RACOON) {
			if (stateOfMario == MARIO_STATE_JUMP) {
				switch (Mario->GetState()) {
				case MARIO_STATE_FLY:
					Mario->SetState(MARIO_STATE_RELEASE_FLY);
					Mario->SetState(MARIO_STATE_RELEASE_JUMP);

					break;

				case MARIO_STATE_JUMP:
				case MARIO_STATE_RELEASE_FLY:
				case MARIO_STATE_RELEASE_JUMP:
					Mario->SetState(MARIO_STATE_WALKING_LEFT);
					Mario->SetState(MARIO_STATE_FLY);
				}
				flag = MARIO_JUMP_ON_GOOMBA;
			}

			if (Mario->IsOnPlatform() && flag == MARIO_JUMP_ON_GOOMBA)
				stateOfMario = MARIO_STATE_WALKING_RIGHT;

			if (stateOfMario == MARIO_STATE_WALKING_RIGHT) {
				Mario->SetState(stateOfMario);
				Mario->GetPosition(x, y);

				if (x >= Screen_Width * 6 / 8) {
					Mario->SetState(MARIO_STATE_IDLE);
					stateOfMario = MARIO_STATE_IDLE;

					if (ItemsAndEnemies.size() == 0) {
						Luigi->GetPosition(x, y);
						Luigi->SetState(MARIO_STATE_HOLD);

						LPGAMEOBJECT obj = new CKoopaTroopa(x - 20, y, KOOPA_TROOPA_TYPE_GREEN, 1);
						obj->SetState(KOOPA_TROOPA_STATE_SHELL);
						ItemsAndEnemies.push_back(obj);

						flag = LUIGI_HOLDING_KOOPA_TROOPA;
						timeStart = GetTickCount64();
						stateOfMario = 0;
					}
				}
			}
		}

		if (flag == LUIGI_HOLDING_KOOPA_TROOPA) {
			Luigi->SetState(MARIO_STATE_WALKING_LEFT);
			Luigi->SetState(MARIO_STATE_HOLD);
			if (GetTickCount64() - timeStart > MARIO_WALKING_TIME) {
				Luigi->SetState(MARIO_STATE_HOLD_RELEASE);
				Luigi->SetState(MARIO_STATE_IDLE);

				timeStart = 0;
				Mario->SetState(MARIO_STATE_JUMP);

				flag = MARIO_JUMP_ON_KOOPA_TROOPA;
			}

			Luigi->GetPosition(x, y);
			if (x <= Screen_Width + 10)
				Mario->SetState(MARIO_STATE_WALKING_LEFT);
		}

		if (flag == MARIO_JUMP_ON_KOOPA_TROOPA) {
			Mario->GetSpeed(x, y);
			if (y >= 0 && Mario->IsOnPlatform()) {
				Mario->SetState(MARIO_STATE_WALKING_RIGHT);
				Mario->SetState(MARIO_STATE_HOLD);
			}

			if (Mario->IsHolding()) {
				Mario->GetPosition(x, y);
				if (x > Screen_Width / 2 - 20) {
					Mario->SetState(MARIO_STATE_HOLD_RELEASE);
					Mario->SetState(MARIO_STATE_IDLE);

					Luigi->SetState(MARIO_STATE_WALKING_RIGHT);

					flag = KOOPA_TROOPA_ATTACKING;
					timeStart = GetTickCount64();
				}
			}
		}

		if (flag == KOOPA_TROOPA_ATTACKING) {
			if (timeStart != 0 && (GetTickCount64() - timeStart) > WAITING_KOOPA_TROOPA_ATTACK_TIME) {
				Mario->GetPosition(x, y);
				LPGAMEOBJECT obj = new CKoopaTroopa(0, y, KOOPA_TROOPA_TYPE_GREEN, 1);
				obj->SetNx(-1);
				obj->SetState(KOOPA_TROOPA_STATE_ATTACKING);
				ItemsAndEnemies.push_back(obj);
				timeStart = 0;
			}

			if (Mario->GetLevel() == MARIO_LEVEL_BIG)
				Mario->SetLevel(MARIO_LEVEL_SMALL);
			else if (Mario->GetLevel() == MARIO_LEVEL_SMALL) {
				if (ItemsAndEnemies.size() == 0) {
					timeStart = GetTickCount64();
					flag = MARIO_WALKING_TIME;
					Mario->SetState(MARIO_STATE_WALKING_RIGHT);
				}
			}
		}

		if (flag == MARIO_WALKING_TIME) {
			float vx, vy;
			Mario->GetSpeed(vx, vy);
			Mario->GetPosition(x, y);

			DebugOut(L"x: %f, y: %f, vx: %f, vy: %f \n", x, y, vx, vy);
			if (vx > 0 && x >= Screen_Width * 4 / 5)
				Mario->SetState(MARIO_STATE_WALKING_LEFT);
			if (vx < 0 && x <= Screen_Width * 3 / 5) {
				Mario->SetState(MARIO_STATE_WALKING_RIGHT);
				flag = KOOPA_TROOPA_WALKING;
			}

		}

		if (flag == KOOPA_TROOPA_WALKING) {
			Mario->GetPosition(x, y);
			if (x > Screen_Width + 30 && ItemsAndEnemies.size() == 0) {
				LPGAMEOBJECT obj = new CKoopaTroopa(0, y - 5, KOOPA_TROOPA_TYPE_GREEN, 1);
				obj->SetSpeed(0.05f, 0);
				ItemsAndEnemies.push_back(obj);

				obj = new CKoopaTroopa(-20, y - 5, KOOPA_TROOPA_TYPE_GREEN, 1);
				obj->SetSpeed(0.05f, 0);
				ItemsAndEnemies.push_back(obj);

				obj = new CKoopaTroopa(-40, y - 5, KOOPA_TROOPA_TYPE_GREEN, 1);
				obj->SetSpeed(0.05f, 0);
				ItemsAndEnemies.push_back(obj);
			}

			if (ItemsAndEnemies.size() != 0) {
				ItemsAndEnemies[0]->GetPosition(x, y);
				if (x >= Screen_Width / 2 + 15) {
					LPGAMEOBJECT obj = new CKoopaTroopa(-40, y - 5, KOOPA_TROOPA_TYPE_GREEN, 1);
					obj->SetSpeed(0.08f, 0);
					ItemsAndEnemies.push_back(obj);

					Mario->SetState(MARIO_STATE_IDLE);
					flag = 0;

					CControl::GetInstance()->ActiveControl(CONTROL_TYPE_MODE);;
				}
			}
		}
	}

public:

	CIntroScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	LPGAMEOBJECT GetPlayer(int i = 0) { if (i < 2 && i >= 0) return player[i];  return NULL; }

	CPortal* GetPortal() { return portal; }

	vector<CPlatform*>& GetPlatformObjects() { return platformObjects; }
	CPlatformAnimate* GetNumber3() { return Number3; }
	float GetNumber3original_y() { return Number3Original_y; }

	void MainScreen() { flag = 0; timeStart = 0; MarioWalkingStart = 0; }

	void Clear();
	void PurgeDeletedObjects();

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
};

typedef CIntroScene* LPINTROSCENE;