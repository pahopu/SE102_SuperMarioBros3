#include "Brick.h"
#include "Goomba.h"
#include "KoopaTroopa.h"


void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (time_start == -1)
		return;

	this->Update(dt);

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CBrick::Update(DWORD dt) {
	if (type == BRICK_TYPE_EMPTY || state == BRICK_STATE_DEFLECT) {
		vy += ay * dt;
		y += vy * dt;

		if (y > old_y) {
			y = old_y;
			time_start = -1;
			vy = ay = 0;
			state = -1;
		}
	}
	else if (type == BRICK_TYPE_BREAK) {
		vx += ax * dt;
		vy += ay * dt;

		x += vx * dt;
		y += vy * dt;

		if (GetTickCount64() - time_start > BRICK_BREAK_TIMEOUT) {
			if (bricks.size() > 0) {
				vector<CBrick*>::iterator it;
				for (it = bricks.begin(); it != bricks.end(); it++) {
					CBrick* o = *it;
					if (o->IsDeleted()) {
						delete o;
						*it = NULL;
					}
				}
			}
			this->Delete();
		}
	}

	if (bricks.size() > 0)
		for (int i = 0; i < 3; i++)
			bricks[i]->Update(dt);
}

void CBrick::Render()
{
	int aniId = ID_ANI_GOLD_BRICK;
	if (type == BRICK_TYPE_QUESTION)
		aniId = ID_ANI_QUESTION_BRICK;
	else if (type == BRICK_TYPE_EMPTY)
		aniId = ID_ANI_EMPTY_BRICK;
	else if (type == BRICK_TYPE_BREAK)
		aniId = ID_ANI_BREAK_BRICK;

	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniId)->Render(x, y);

	if (bricks.size() > 0)
		for (int i = 0; i < 3; i++)
			bricks[i]->Render();
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x - BRICK_BBOX_WIDTH/2;
	t = y - BRICK_BBOX_HEIGHT/2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}

void CBrick::SetType(int type)
{
	switch (type) {
	case BRICK_TYPE_GOLD:
		break;
	case BRICK_TYPE_QUESTION:
		break;
	case BRICK_TYPE_EMPTY:
		time_start = GetTickCount64();
		old_y = y;
		Deflected(0);
		break;
	case BRICK_TYPE_BREAK:
		time_start = GetTickCount64();
		ay = BRICK_GRAVITY;
		vx = -BRICK_BREAK_DEFLECT_X;
		vy = -BRICK_BREAK_DEFLECT_Y;

		if (type == BRICK_TYPE_GOLD) {
			bricks.push_back(new CBrick(x + BRICK_BBOX_WIDTH, y, BRICK_TYPE_BREAK));
			bricks[0]->SetSpeed(BRICK_BREAK_DEFLECT_X, -BRICK_BREAK_DEFLECT_Y);
			bricks[0]->time_start = GetTickCount64();
			bricks[0]->ay = BRICK_GRAVITY;

			//bricks.push_back(new CBrick(x, y + BRICK_BBOX_HEIGHT, BRICK_TYPE_BREAK));
			//bricks[1]->SetSpeed(-BRICK_BREAK_DEFLECT_X, -BRICK_BREAK_DEFLECT_X);
			//bricks[1]->time_start = GetTickCount64();
			//bricks[1]->ay = BRICK_GRAVITY;

			//bricks.push_back(new CBrick(x + BRICK_BBOX_WIDTH, y + BRICK_BBOX_HEIGHT, BRICK_TYPE_BREAK));
			//bricks[2]->SetSpeed(BRICK_BREAK_DEFLECT_X, -BRICK_BREAK_DEFLECT_X);
			//bricks[2]->time_start = GetTickCount64();
			//bricks[2]->ay = BRICK_GRAVITY;
		}
		break;
	}
	this->type = type;
}

void CBrick::SetState(int State) {
	CGameObject::SetState(State);
	switch (state)
	{
	case BRICK_STATE_DEFLECT:
		time_start = GetTickCount64();
		old_y = y;
		ay = BRICK_GRAVITY;
		vy = -BRICK_TRANSFORM_DEFLECT;
		break;
	}
}

bool CBrick::IsAttacking() {
	if (this == NULL || time_start == -1) return false;
	return type == BRICK_TYPE_BREAK || type == BRICK_TYPE_EMPTY || state == BRICK_STATE_DEFLECT;
}

void CBrick::Deflected(int Direction) {
	ay = BRICK_GRAVITY;
	vy = -BRICK_TRANSFORM_DEFLECT;
}
