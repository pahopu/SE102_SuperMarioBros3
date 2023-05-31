#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#include "debug.h"

#define MARIO_WALKING_SPEED						0.1f
#define MARIO_RUNNING_SPEED						0.2f

#define MARIO_ACCEL_WALK_X						0.0005f
#define MARIO_ACCEL_RUN_X						0.0007f

#define MARIO_JUMP_SPEED_Y						0.5f
#define MARIO_JUMP_RUN_SPEED_Y					0.6f

#define MARIO_GRAVITY							0.002f

#define MARIO_JUMP_DEFLECT_SPEED				0.4f

#define MARIO_STATE_DIE							-10
#define MARIO_STATE_IDLE						0

#define MARIO_STATE_WALKING_RIGHT				100
#define MARIO_STATE_WALKING_LEFT				200

#define MARIO_STATE_JUMP						300
#define MARIO_STATE_RELEASE_JUMP				301

#define MARIO_STATE_RUNNING_RIGHT				400
#define MARIO_STATE_RUNNING_LEFT				500

#define MARIO_STATE_SIT							600
#define MARIO_STATE_SIT_RELEASE					601

#define MARIO_STATE_ATTACK						700


#pragma region ANIMATION_ID

// SMALL MARIO
#define ID_ANI_MARIO_SMALL_IDLE_LEFT			100
#define ID_ANI_MARIO_SMALL_IDLE_RIGHT			101

#define ID_ANI_MARIO_SMALL_WALKING_LEFT			200
#define ID_ANI_MARIO_SMALL_WALKING_RIGHT		201

#define ID_ANI_MARIO_SMALL_RUNNING_LEFT			300
#define ID_ANI_MARIO_SMALL_RUNNING_RIGHT		301

#define ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT		400
#define ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT		401

#define ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT		500
#define ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT		501

#define ID_ANI_MARIO_SMALL_BRACE_LEFT			600
#define ID_ANI_MARIO_SMALL_BRACE_RIGHT			601

// BIG MARIO
#define ID_ANI_MARIO_IDLE_LEFT					700
#define ID_ANI_MARIO_IDLE_RIGHT					701

#define ID_ANI_MARIO_WALKING_LEFT				800
#define ID_ANI_MARIO_WALKING_RIGHT				801

#define ID_ANI_MARIO_RUNNING_LEFT				900
#define ID_ANI_MARIO_RUNNING_RIGHT				901

#define ID_ANI_MARIO_JUMP_WALK_LEFT				1000
#define ID_ANI_MARIO_JUMP_WALK_RIGHT			1001

#define ID_ANI_MARIO_JUMP_RUN_LEFT				1100
#define ID_ANI_MARIO_JUMP_RUN_RIGHT				1101

#define ID_ANI_MARIO_SIT_LEFT					1200
#define ID_ANI_MARIO_SIT_RIGHT					1201

#define ID_ANI_MARIO_BRACE_LEFT					1300
#define ID_ANI_MARIO_BRACE_RIGHT				1301

// RACOON MARIO
#define ID_ANI_MARIO_RACOON_IDLE_LEFT			1400
#define ID_ANI_MARIO_RACOON_IDLE_RIGHT			1401
#define ID_ANI_MARIO_RACOON_IDLE_FRONT			1402

#define ID_ANI_MARIO_RACOON_WALKING_LEFT		1500
#define ID_ANI_MARIO_RACOON_WALKING_RIGHT		1501

#define ID_ANI_MARIO_RACOON_RUNNING_LEFT		1600
#define ID_ANI_MARIO_RACOON_RUNNING_RIGHT		1601

#define ID_ANI_MARIO_RACOON_JUMP_WALK_LEFT		1700
#define ID_ANI_MARIO_RACOON_JUMP_WALK_RIGHT		1701

#define ID_ANI_MARIO_RACOON_JUMP_RUN_LEFT		1800
#define ID_ANI_MARIO_RACOON_JUMP_RUN_RIGHT		1801

#define ID_ANI_MARIO_RACOON_SIT_LEFT			1900
#define ID_ANI_MARIO_RACOON_SIT_RIGHT			1901

#define ID_ANI_MARIO_RACOON_BRACE_LEFT			2000
#define ID_ANI_MARIO_RACOON_BRACE_RIGHT			2001

#define ID_ANI_MARIO_RACOON_ATTACK_LEFT			2100
#define ID_ANI_MARIO_RACOON_ATTACK_RIGHT		2101

// DIE
#define ID_ANI_MARIO_DIE					999

#pragma endregion


#define GROUND_Y							160.0f


#define	MARIO_LEVEL_SMALL					1
#define	MARIO_LEVEL_BIG						2
#define MARIO_LEVEL_RACOON					3

#define MARIO_SMALL_BBOX_WIDTH				11
#define MARIO_SMALL_BBOX_HEIGHT				13

#define MARIO_BIG_BBOX_WIDTH				14
#define MARIO_BIG_BBOX_HEIGHT				24

#define MARIO_BIG_SITTING_BBOX_WIDTH		14
#define MARIO_BIG_SITTING_BBOX_HEIGHT		16

#define MARIO_SIT_HEIGHT_ADJUST				((MARIO_BIG_BBOX_HEIGHT - MARIO_BIG_SITTING_BBOX_HEIGHT) / 2)

#define MARIO_RACOON_BBOX_WIDTH				21
#define MARIO_RACOON_BBOX_HEIGHT			24

#define MARIO_RACOON_SITTING_BBOX_WIDTH		21
#define MARIO_RACOON_SITTING_BBOX_HEIGHT	16


#define MARIO_UNTOUCHABLE_TIME				2500
#define MARIO_ATTACK_TIME					300

class CMario : public CGameObject
{
	BOOLEAN isSitting;
	float maxVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 

	int level; 
	int untouchable;
	int flag;
	ULONGLONG time_count;
	ULONGLONG untouchable_start;
	BOOLEAN isOnPlatform;
	int coin; 

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopaTroopa(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithMushroom(LPCOLLISIONEVENT e);

	int GetAniIdBig();
	int GetAniIdSmall();
	int GetAniIdRacoon();

public:
	CMario(float x, float y) : CGameObject(x, y)
	{
		isSitting = false;
		maxVx = 0.0f;
		ax = 0.0f;
		ay = MARIO_GRAVITY; 

		level = MARIO_LEVEL_SMALL;
		untouchable = 0;
		untouchable_start = -1;
		isOnPlatform = false;
		coin = 0;
		flag = 0;
		time_count = 0;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);

	int IsCollidable()
	{ 
		return (state != MARIO_STATE_DIE); 
	}

	int IsBlocking() { return (state != MARIO_STATE_DIE && untouchable==0); }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void SetLevel(int l);
	int GetLevel() { return level; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};