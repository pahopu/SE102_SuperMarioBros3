#include <algorithm>
#include "debug.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "Coin.h"
#include "Portal.h"
#include "Mushroom.h"
#include "Brick.h"
#include "PiranhaPlant.h"
#include "Bullet.h"

#include "Platform.h"
#include "PSwitch.h"

#include "Collision.h"

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (x < 6) x = 6;
	if (x > 2798) x = 2798;
	if (y < 6) y = 6;

	//DebugOutTitle(L"mario x: %f y: %f", x, y);

	vy += ay * dt;
	vx += ax * dt;

	if (_koopa) {
		if (!_koopa->GetStateHeld())
			_koopa = NULL;
		else {
			if (_koopa->GetNx() != nx) {
				_koopa->SetNx(nx);
				float temp = (nx >= 0) ? 1.0f : -1.0f;

				switch (level) {
				case MARIO_LEVEL_SMALL:
					_koopa->SetPosition(x + temp * MARIO_SMALL_BBOX_WIDTH / 2 + temp * KOOPA_TROOPA_BBOX_WIDTH / 2, y - MARIO_SMALL_BBOX_HEIGHT / 2);
					break;

				case MARIO_LEVEL_BIG:
					_koopa->SetPosition(x + temp * MARIO_BIG_BBOX_WIDTH / 2 + temp * KOOPA_TROOPA_BBOX_WIDTH / 2, y);
					break;

				case MARIO_LEVEL_RACOON:
					_koopa->SetPosition(x + temp * MARIO_RACOON_BBOX_WIDTH / 2 + temp * KOOPA_TROOPA_BBOX_WIDTH / 2, y + 1);
					break;
				}
			}
			_koopa->SetSpeed(vx, vy);
		}
	}

	if (abs(vx) > abs(maxVx)) vx = maxVx;

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME) {
		untouchable_start = 0;
		untouchable = 0;
	}

	if (flag == MARIO_ATTACK_TIME) {
		CTail* tail = dynamic_cast<CTail*>(_tail);
		if (GetTickCount64() - time_count > flag) {
			flag = 0;
			time_count = 0;
			tail->SetAttackTime(time_count);
		}
		else {
			float temp = (nx >= 0) ? -1.0f : 1.0f; //to determine direction

			tail->SetPosition(x + temp * MARIO_RACOON_BBOX_WIDTH / 2 + temp * MARIO_TAIL_WIDTH / 2, y + MARIO_TAIL_POSITION_ADJUST);
			tail->SetSpeed(vx, vy);

			if (!tail->IsAttacking()) tail->Attack(nx);
			tail->SetAttackTime(time_count);
			_tail->Update(dt, coObjects);
		}
	}

	if (flag == MARIO_KICK_TIME && (GetTickCount64() - time_count > flag)) {
		flag = 0;
		time_count = 0;
	}

	if (fly_start && (GetTickCount64() - fly_start >= MARIO_FLY_TIME)) {
		fly_start = 0;
		float_start = GetTickCount64();
	}

	if (isOnPlatform) fly_start = float_start = 0;

	isOnPlatform = false;

	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMario::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0) {
		if (dynamic_cast<CPlatform*>(e->obj)) {
			CPlatform* platform = dynamic_cast<CPlatform*>(e->obj);

			switch (platform->GetType()) {
			case PLATFORM_TYPE_BLOCK:
				isOnPlatform = true;
				vy = 0;
				break;

			case PLATFORM_TYPE_NORMAL:
				if (e->ny < 0) {
					vy = 0;
					isOnPlatform = true;
				}
				break;
			}
		}
		else if (e->obj->IsBlocking()) {
			if (e->ny < 0) isOnPlatform = true;
			vy = 0;
		}

		if (_koopa && _koopa->GetStateHeld()) _koopa->SetSpeed(vx, vy);
	}
	else if (e->nx != 0) {
		if (dynamic_cast<CPlatform*>(e->obj)) {
			if (dynamic_cast<CPlatform*>(e->obj)->GetType() == PLATFORM_TYPE_BLOCK) vx = 0;
		}
		else if (e->obj->IsBlocking()) vx = 0;
	}

	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CKoopaTroopa*>(e->obj))
		OnCollisionWithKoopaTroopa(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);
	else if (dynamic_cast<CMushroom*>(e->obj))
		OnCollisionWithMushroom(e);
	else if (dynamic_cast<CBrick*>(e->obj))
		OnCollisionWithBrick(e);
	else if (dynamic_cast<CPiranhaPlant*>(e->obj))
		OnCollisionWithPiranhaPlant(e);
	else if (dynamic_cast<CBullet*>(e->obj)) {
		if (IsUntouchable() || dynamic_cast<CBullet*>(e->obj)->GetType() == BULLET_BY_MARIO)
			return;

		switch (level) {
		case MARIO_LEVEL_SMALL:
			this->SetState(MARIO_STATE_DIE);
			break;
		case MARIO_LEVEL_BIG:
			this->SetLevel(MARIO_LEVEL_SMALL);
			this->StartUntouchable();
			break;
		case MARIO_LEVEL_RACOON:
			this->SetLevel(MARIO_LEVEL_BIG);
			this->StartUntouchable();
			break;
		}
	}
	else if (dynamic_cast<CPSwitch*>(e->obj)) {
		dynamic_cast<CPSwitch*>(e->obj)->IsActived();
	}
}

void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
	if (goomba->GetState() == GOOMBA_STATE_DIE_BY_JUMP || goomba->GetState() == GOOMBA_STATE_DIE_BY_ATTACK)
		return;

	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0) {
		if (goomba->GetLevel() == GOOMBA_LEVEL_NORMAL)
			goomba->SetState(GOOMBA_STATE_DIE_BY_JUMP);
		else {
			goomba->SetLevel(GOOMBA_LEVEL_NORMAL);
			goomba->SetState(GOOMBA_STATE_WALKING);
		}
		vy = -MARIO_JUMP_DEFLECT_SPEED;
	}
	else {// hit by Goomba
		if (untouchable == 0) {
			isAttacked = 1;
			if (level != MARIO_LEVEL_SMALL) SetTransformStart();

			if (goomba->GetState() != GOOMBA_STATE_DIE_BY_JUMP)
				if (level == MARIO_LEVEL_RACOON) {
					level = MARIO_LEVEL_BIG;
					StartUntouchable();
				}
				else if (level == MARIO_LEVEL_BIG) {
					level = MARIO_LEVEL_SMALL;
					StartUntouchable();
				}
				else {
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
		}
	}
}

void CMario::OnCollisionWithKoopaTroopa(LPCOLLISIONEVENT e)
{
	CKoopaTroopa* koopa = dynamic_cast<CKoopaTroopa*>(e->obj);

	if (koopa->GetState() == KOOPA_TROOPA_STATE_DIE)
		return;

	// Mario kick koopa troopa shell
	if (koopa->GetState() == KOOPA_TROOPA_STATE_SHELL) {

		if (e->ny != 0 || (holdable == 0 && e->nx != 0)) {
			SetState(MARIO_STATE_KICK);
			koopa->SetNx(-nx);
			koopa->SetState(KOOPA_TROOPA_STATE_ATTACKING);
		}
		else if (holdable && !_koopa) {
			koopa->IsHeld();
			_koopa = koopa;

			float temp = (nx >= 0) ? 1.0f : -1.0f;
			switch (level)
			{
			case MARIO_LEVEL_SMALL:
				_koopa->SetPosition(x + temp * MARIO_SMALL_BBOX_WIDTH / 2 + temp * KOOPA_TROOPA_BBOX_WIDTH / 2,
					y - MARIO_SMALL_BBOX_HEIGHT / 2);
				break;

			case MARIO_LEVEL_BIG:
				_koopa->SetPosition(x + temp * MARIO_BIG_BBOX_WIDTH / 2 + temp * KOOPA_TROOPA_BBOX_WIDTH / 2, y);
				break;

			case MARIO_LEVEL_RACOON:
				_koopa->SetPosition(x + temp * MARIO_RACOON_BBOX_WIDTH / 2 + temp * KOOPA_TROOPA_BBOX_WIDTH / 2, y + 1);
				break;
			}
		}
	}
	else if (e->ny < 0) {
		if (koopa->GetState() == KOOPA_TROOPA_STATE_WALKING)
			koopa->SetState(KOOPA_TROOPA_STATE_SHELL);
		else if (koopa->GetState() == KOOPA_TROOPA_STATE_ATTACKING) {
			koopa->SetState(KOOPA_TROOPA_STATE_SHELL);
		}
		else if (koopa->GetLevel() == KOOPA_TROOPA_LEVEL_PARA) {
			koopa->SetLevel(KOOPA_TROOPA_LEVEL_NORMAL);
			koopa->SetState(KOOPA_TROOPA_STATE_WALKING);
		}
		vy = -MARIO_JUMP_DEFLECT_SPEED;
	}
	else {
		if (untouchable == 0) {
			isAttacked = 1;
			if (level != MARIO_LEVEL_SMALL) SetTransformStart();

			if (koopa->GetState() == KOOPA_TROOPA_STATE_WALKING || koopa->GetState() == KOOPA_TROOPA_STATE_ATTACKING)
				if (level == MARIO_LEVEL_RACOON) {
					level = MARIO_LEVEL_BIG;
					StartUntouchable();
				}
				else if (level == MARIO_LEVEL_BIG) {
					level = MARIO_LEVEL_SMALL;
					StartUntouchable();
				}
				else {
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
		}
	}
}

void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	coin++;
}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* p = (CPortal*)e->obj;
	CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
}

void CMario::OnCollisionWithMushroom(LPCOLLISIONEVENT e)
{
	CMushroom* mushroom = (CMushroom*)e->obj;

	if (mushroom->GetType() == MUSHROOM_TYPE_1UP) {
		// Process 1up
	}
	else {
		if (level != MARIO_LEVEL_RACOON) SetTransformStart();

		switch (level) {
		case MARIO_LEVEL_SMALL:
			SetLevel(MARIO_LEVEL_BIG);
			break;
		case MARIO_LEVEL_BIG:
			SetLevel(MARIO_LEVEL_RACOON);
			break;
		}
	}

	e->obj->Delete();
}

void CMario::OnCollisionWithBrick(LPCOLLISIONEVENT e)
{
	CBrick* brick = dynamic_cast<CBrick*>(e->obj);
	switch (brick->GetType()) {
	case BRICK_TYPE_GOLD:
		if (e->ny > 0) {
			if (level == MARIO_LEVEL_SMALL && brick->GetState() != BRICK_STATE_DEFLECT)
				brick->SetState(BRICK_STATE_DEFLECT);
			else if (level != MARIO_LEVEL_SMALL)
				brick->SetType(BRICK_TYPE_BREAK);
			brick->BrokenByJump();
		}

		break;

	case BRICK_TYPE_QUESTION:
		if (e->ny > 0) {
			brick->SetType(BRICK_TYPE_EMPTY);
			brick->BrokenByJump();
		}

		break;
	}
}

void CMario::OnCollisionWithPiranhaPlant(LPCOLLISIONEVENT e) {
	CPiranhaPlant* plant = dynamic_cast<CPiranhaPlant*>(e->obj);

	if (!untouchable && plant->GetState() != PIRANHA_STATE_IDLE) {
		isAttacked = 1;
		if (level != MARIO_LEVEL_SMALL) SetTransformStart();

		switch (level) {
		case MARIO_LEVEL_RACOON:
			this->level = MARIO_LEVEL_BIG;
			StartUntouchable();
			break;

		case MARIO_LEVEL_BIG:
			this->level = MARIO_LEVEL_SMALL;
			StartUntouchable();
			break;

		case MARIO_LEVEL_SMALL:
			DebugOut(L">>> Mario DIE >>> \n");
			this->SetState(MARIO_STATE_DIE);
			break;
		}
	}
}

//
// Get animation ID for small Mario
//
int CMario::GetAniIdSmall()
{
	int checkHold = (_koopa) ? _koopa->GetStateHeld() : 0;
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (checkHold) {
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_HOLD_JUMP_RIGHT;
			else aniId = ID_ANI_MARIO_SMALL_HOLD_JUMP_LEFT;
		}
		else {
			if (abs(ax) == MARIO_ACCEL_RUN_X) {
				if (nx >= 0)
					aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT;
				else aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
			}
			else {
				if (nx >= 0)
					aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT;
				else aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
			}
		}
	}
	else {
		if (isSitting) {
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else {
			if (checkHold) {
				if (vx == 0) {
					if (nx > 0) aniId = ID_ANI_MARIO_SMALL_HOLD_IDLE_RIGHT;
					else aniId = ID_ANI_MARIO_SMALL_HOLD_IDLE_LEFT;
				}
				else {
					if (ax > 0) aniId = ID_ANI_MARIO_SMALL_HOLD_RUN_RIGHT;
					else aniId = ID_ANI_MARIO_SMALL_HOLD_RUN_LEFT;
				}
			}
			else {
				if (vx == 0)
				{
					if (nx > 0) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
					else aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
				}
				else if (vx > 0)
				{
					if (ax < 0)
						aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
					else if (vx == MARIO_RUNNING_SPEED)
						aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
					else if (abs(vx) < MARIO_SPEED_UP_SPEED)
						aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
					else if (abs(vx) >= MARIO_SPEED_UP_SPEED)
						aniId = ID_ANI_MARIO_SMALL_SPEED_UP_RIGHT;
				}
				else // vx < 0
				{
					if (ax > 0)
						aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
					else if (vx == -MARIO_RUNNING_SPEED)
						aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
					else if (abs(vx) < MARIO_SPEED_UP_SPEED)
						aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
					else if (abs(vx) >= MARIO_SPEED_UP_SPEED)
						aniId = ID_ANI_MARIO_SMALL_SPEED_UP_LEFT;
				}
			}
		}
	}

	if (flag == MARIO_KICK_TIME)
		if (nx > 0) aniId = ID_ANI_MARIO_SMALL_KICK_RIGHT;
		else aniId = ID_ANI_MARIO_SMALL_KICK_LEFT;

	if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;

	return aniId;
}

int CMario::GetAniIdRacoon()
{
	int checkHold = (_koopa) ? _koopa->GetStateHeld() : 0;
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (checkHold) {
			if (nx >= 0)
				aniId = ID_ANI_MARIO_RACOON_HOLD_JUMP_RIGHT;
			else aniId = ID_ANI_MARIO_RACOON_HOLD_JUMP_LEFT;
		}
		else {
			if (abs(vx) == MARIO_RUNNING_SPEED) {
				if (nx >= 0) {
					if (vy < 0) aniId = ID_ANI_MARIO_RACOON_JUMP_RUN_UP_RIGHT;
					else aniId = ID_ANI_MARIO_RACOON_JUMP_RUN_DOWN_RIGHT;
				}
				else {
					if (vy < 0) aniId = ID_ANI_MARIO_RACOON_JUMP_RUN_UP_LEFT;
					else aniId = ID_ANI_MARIO_RACOON_JUMP_RUN_DOWN_LEFT;
				}
			}
			else {
				if (nx >= 0) {
					if (vy < 0) aniId = ID_ANI_MARIO_RACOON_JUMP_WALK_UP_RIGHT;
					else aniId = ID_ANI_MARIO_RACOON_JUMP_WALK_DOWN_RIGHT;
				}
				else {
					if (vy < 0) aniId = ID_ANI_MARIO_RACOON_JUMP_WALK_UP_LEFT;
					else aniId = ID_ANI_MARIO_RACOON_JUMP_WALK_DOWN_LEFT;
				}
			}
		}
	}
	else {
		if (isSitting) {
			if (nx > 0)
				aniId = ID_ANI_MARIO_RACOON_SIT_RIGHT;
			else aniId = ID_ANI_MARIO_RACOON_SIT_LEFT;
		}
		else {
			if (checkHold) {
				if (vx == 0) {
					if (nx > 0) aniId = ID_ANI_MARIO_RACOON_HOLD_IDLE_RIGHT;
					else aniId = ID_ANI_MARIO_RACOON_HOLD_IDLE_LEFT;
				}
				else {
					if (ax > 0) aniId = ID_ANI_MARIO_RACOON_HOLD_RUN_RIGHT;
					else aniId = ID_ANI_MARIO_RACOON_HOLD_RUN_LEFT;
				}
			}
			else {
				if (vx == 0)
				{
					if (nx > 0) aniId = ID_ANI_MARIO_RACOON_IDLE_RIGHT;
					else aniId = ID_ANI_MARIO_RACOON_IDLE_LEFT;
				}
				else if (vx > 0)
				{
					if (ax < 0)
						aniId = ID_ANI_MARIO_RACOON_BRACE_RIGHT;
					else if (vx == MARIO_RUNNING_SPEED)
						aniId = ID_ANI_MARIO_RACOON_RUNNING_RIGHT;
					else if (abs(vx) < MARIO_SPEED_UP_SPEED)
						aniId = ID_ANI_MARIO_RACOON_WALKING_RIGHT;
					else if (abs(vx) >= MARIO_SPEED_UP_SPEED)
						aniId = ID_ANI_MARIO_RACOON_SPEED_UP_RIGHT;
				}
				else // vx < 0
				{
					if (ax > 0)
						aniId = ID_ANI_MARIO_RACOON_BRACE_LEFT;
					else if (vx == -MARIO_RUNNING_SPEED)
						aniId = ID_ANI_MARIO_RACOON_RUNNING_LEFT;
					else if (abs(vx) < MARIO_SPEED_UP_SPEED)
						aniId = ID_ANI_MARIO_RACOON_WALKING_LEFT;
					else if (abs(vx) >= MARIO_SPEED_UP_SPEED)
						aniId = ID_ANI_MARIO_RACOON_SPEED_UP_LEFT;
				}
			}
		}
	}

	if (!_koopa) {
		if (float_start) {
			if (float_start < MARIO_REFLOAT_TIME) {
				if (nx >= 0) aniId = ID_ANI_MARIO_RACOON_JUMP_WALK_DOWN_RIGHT;
				else aniId = ID_ANI_MARIO_RACOON_JUMP_WALK_DOWN_LEFT;
			}
			else {
				if (nx >= 0) aniId = ID_ANI_MARIO_RACOON_FLOAT_RIGHT;
				else aniId = ID_ANI_MARIO_RACOON_FLOAT_LEFT;
			}
		}
		else if (fly_start) {
			if (vy >= 0) {
				if (nx >= 0) aniId = ID_ANI_MARIO_RACOON_JUMP_RUN_DOWN_RIGHT;
				else aniId = ID_ANI_MARIO_RACOON_JUMP_RUN_DOWN_LEFT;
			}
			else {
				if (nx >= 0) aniId = ID_ANI_MARIO_RACOON_FLY_RIGHT;
				else aniId = ID_ANI_MARIO_RACOON_FLY_LEFT;
			}
		}
	}

	if (flag == MARIO_KICK_TIME)
		if (nx > 0) aniId = ID_ANI_MARIO_RACOON_KICK_RIGHT;
		else aniId = ID_ANI_MARIO_RACOON_KICK_LEFT;
	else if (flag == MARIO_ATTACK_TIME)
		if (nx >= 0) aniId = ID_ANI_MARIO_RACOON_ATTACK_RIGHT;
		else aniId = ID_ANI_MARIO_RACOON_ATTACK_LEFT;

	if (aniId == -1) aniId = ID_ANI_MARIO_RACOON_IDLE_RIGHT;

	return aniId;
}


//
// Get animdation ID for big Mario
//
int CMario::GetAniIdBig()
{
	int checkHold = (_koopa) ? _koopa->GetStateHeld() : 0;
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (checkHold) {
			if (nx >= 0)
				aniId = ID_ANI_MARIO_HOLD_JUMP_RIGHT;
			else aniId = ID_ANI_MARIO_HOLD_JUMP_LEFT;
		}
		else {
			if (abs(ax) == MARIO_ACCEL_RUN_X) {
				if (nx >= 0)
					aniId = ID_ANI_MARIO_JUMP_RUN_RIGHT;
				else aniId = ID_ANI_MARIO_JUMP_RUN_LEFT;
			}
			else {
				if (nx >= 0)
					aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT;
				else aniId = ID_ANI_MARIO_JUMP_WALK_LEFT;
			}
		}
	}
	else {
		if (isSitting) {
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else {
			if (checkHold) {
				if (vx == 0) {
					if (nx > 0) aniId = ID_ANI_MARIO_HOLD_IDLE_RIGHT;
					else aniId = ID_ANI_MARIO_HOLD_IDLE_LEFT;
				}
				else {
					if (ax > 0) aniId = ID_ANI_MARIO_HOLD_RUN_RIGHT;
					else aniId = ID_ANI_MARIO_HOLD_RUN_LEFT;
				}
			}
			else {
				if (vx == 0)
				{
					if (nx > 0) aniId = ID_ANI_MARIO_IDLE_RIGHT;
					else aniId = ID_ANI_MARIO_IDLE_LEFT;
				}
				else if (vx > 0)
				{
					if (ax < 0)
						aniId = ID_ANI_MARIO_BRACE_RIGHT;
					else if (vx == MARIO_RUNNING_SPEED)
						aniId = ID_ANI_MARIO_RUNNING_RIGHT;
					else if (abs(vx) < MARIO_SPEED_UP_SPEED)
						aniId = ID_ANI_MARIO_WALKING_RIGHT;
					else if (abs(vx) >= MARIO_SPEED_UP_SPEED)
						aniId = ID_ANI_MARIO_SPEED_UP_RIGHT;
				}
				else // vx < 0
				{
					if (ax > 0)
						aniId = ID_ANI_MARIO_BRACE_LEFT;
					else if (vx == -MARIO_RUNNING_SPEED)
						aniId = ID_ANI_MARIO_RUNNING_LEFT;
					else if (abs(vx) < MARIO_SPEED_UP_SPEED)
						aniId = ID_ANI_MARIO_WALKING_LEFT;
					else if (abs(vx) >= MARIO_SPEED_UP_SPEED)
						aniId = ID_ANI_MARIO_SPEED_UP_LEFT;
				}
			}
		}
	}

	if (flag == MARIO_KICK_TIME)
		if (nx > 0) aniId = ID_ANI_MARIO_KICK_RIGHT;
		else aniId = ID_ANI_MARIO_KICK_LEFT;

	if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_RIGHT;

	return aniId;
}

void CMario::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	if (transform_start != 0 && (GetTickCount64() - transform_start) < MARIO_TRANSFORMATION_TIME) {
		if (isAttacked) {
			if (level == MARIO_LEVEL_BIG)
				animations->Get(ID_ANI_BIG_MARIO_EATING_SUPERLEAF)->Render(x, y);
			else
				if (nx >= 0) animations->Get(ID_ANI_MARIO_SMALL_TRANSFORM_BIG_RIGHT)->Render(x, y);
				else animations->Get(ID_ANI_MARIO_SMALL_TRANSFORM_BIG_LEFT)->Render(x, y);
		}
		else {
			if (level == MARIO_LEVEL_RACOON)
				animations->Get(ID_ANI_BIG_MARIO_EATING_SUPERLEAF)->Render(x, y);
			else
				if (nx >= 0) animations->Get(ID_ANI_MARIO_SMALL_TRANSFORM_BIG_RIGHT)->Render(x, y);
				else animations->Get(ID_ANI_MARIO_SMALL_TRANSFORM_BIG_LEFT)->Render(x, y);
		}
	}
	else {
		int aniId = -1;
		isAttacked = 0;
		transform_start = 0;

		if (state == MARIO_STATE_DIE)
			aniId = ID_ANI_MARIO_DIE;
		else if (level == MARIO_LEVEL_BIG)
			aniId = GetAniIdBig();
		else if (level == MARIO_LEVEL_SMALL)
			aniId = GetAniIdSmall();
		else aniId = GetAniIdRacoon();

		animations->Get(aniId)->Render(x, y);
		//RenderBoundingBox();
	}

	//DebugOutTitle(L"Coins: %d", coin);
}

void CMario::SetState(int state) {
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE) return;

	switch (state) {
	case MARIO_STATE_RUNNING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_RUNNING_SPEED;
		ax = MARIO_ACCEL_RUN_X;
		if (vx <= MARIO_WALKING_SPEED && vx >= 0) vx = MARIO_WALKING_SPEED;
		else if (vx < 0) ax = MARIO_ACCEL_CHANGE_DIRECTION;
		nx = 1;
		break;

	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_RUNNING_SPEED;
		ax = -MARIO_ACCEL_RUN_X;
		if (vx >= -MARIO_WALKING_SPEED && vx <= 0) vx = -MARIO_WALKING_SPEED;
		else if (vx > 0) ax = -MARIO_ACCEL_CHANGE_DIRECTION;
		nx = -1;
		break;

	case MARIO_STATE_WALKING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		break;

	case MARIO_STATE_WALKING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		break;

	case MARIO_STATE_JUMP:
		if (isSitting) break;
		if (isOnPlatform) {
			if (abs(this->vx) == MARIO_RUNNING_SPEED) vy = -MARIO_JUMP_RUN_SPEED_Y;
			else vy = -MARIO_JUMP_SPEED_Y;
		}
		break;

	case MARIO_STATE_RELEASE_JUMP:
		if (vy < 0) vy += MARIO_JUMP_SPEED_Y / 2;
		break;

	case MARIO_STATE_SIT:
		if (isOnPlatform && level != MARIO_LEVEL_SMALL) {
			state = MARIO_STATE_IDLE;
			isSitting = true;
			vx = 0; vy = 0.0f; ax = 0;
			y += MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_SIT_RELEASE:
		if (isSitting)
		{
			isSitting = false;
			state = MARIO_STATE_IDLE;
			if (level == MARIO_LEVEL_BIG)
				y -= MARIO_SIT_HEIGHT_ADJUST;
			else y -= (MARIO_SIT_HEIGHT_ADJUST + 2);
		}
		break;

	case MARIO_STATE_IDLE:
		ax = 0.0f;
		vx = 0.0f;
		break;

	case MARIO_STATE_ATTACK:
		if (time_count == 0)
			time_count = GetTickCount64();
		flag = MARIO_ATTACK_TIME;
		break;

	case MARIO_STATE_KICK:
		if (time_count == 0)
			time_count = GetTickCount64();
		flag = MARIO_KICK_TIME;
		break;

	case MARIO_STATE_HOLD:
		holdable = 1;
		break;

	case MARIO_STATE_HOLD_RELEASE:
		holdable = 0;

		if (_koopa) {
			SetState(MARIO_STATE_KICK);
			_koopa->SetNx(-nx);
			_koopa->SetState(KOOPA_TROOPA_STATE_ATTACKING);
			_koopa = NULL;
		}
		break;

	case MARIO_STATE_FLY:
		if (isSitting || level != MARIO_LEVEL_RACOON) break;

		if (!fly_start && !float_start && abs(vx) == MARIO_RUNNING_SPEED) {
			float_start = 0;
			fly_start = GetTickCount64();
		}

		if (!fly_start) float_start = GetTickCount64();

		if (fly_start) vy -= MARIO_FLY_SPEED_Y;
		else if (float_start) vy -= MARIO_FLOAT_SPEED_Y;

		break;

	case MARIO_STATE_RELEASE_FLY:
		if (vy > 0) vy = 0;

		break;

	case MARIO_STATE_DIE:
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		break;
	}

	CGameObject::SetState(state);
}

void CMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (level == MARIO_LEVEL_BIG) {
		if (isSitting) {
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else {
			left = x - MARIO_BIG_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_BBOX_WIDTH;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else if (level == MARIO_LEVEL_SMALL) {
		left = x - MARIO_SMALL_BBOX_WIDTH / 2;
		top = y - MARIO_SMALL_BBOX_HEIGHT / 2;
		right = left + MARIO_SMALL_BBOX_WIDTH;
		bottom = top + MARIO_SMALL_BBOX_HEIGHT;
	}
	else {
		if (isSitting) {
			left = x - MARIO_RACOON_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_RACOON_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_RACOON_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_RACOON_SITTING_BBOX_HEIGHT;
		}
		else {
			left = x - MARIO_RACOON_BBOX_WIDTH / 2;
			top = y - MARIO_RACOON_BBOX_HEIGHT / 2;
			right = left + MARIO_RACOON_BBOX_WIDTH;
			bottom = top + MARIO_RACOON_BBOX_HEIGHT;
		}
	}
}

void CMario::SetLevel(int l)
{
	// Adjust position to avoid falling off platform
	if (this->level == MARIO_LEVEL_SMALL)
	{
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}
	else y -= (MARIO_RACOON_BBOX_HEIGHT - MARIO_BIG_BBOX_HEIGHT);
	level = l;
}