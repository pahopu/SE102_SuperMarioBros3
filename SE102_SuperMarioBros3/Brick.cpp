#include "Brick.h"


void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (time_start == -1)
		return;

	if (type == BRICK_TYPE_EMPTY) {
		vy += ay * dt;
		y += vy * dt;

		if (y > old_y) {
			y = old_y;
			time_start = -1;
			vy = ay = 0;
		}
	}
}

void CBrick::Render()
{
	int aniId = ID_ANI_GOLD_BRICK;
	if (type == BRICK_TYPE_QUESTION)
		aniId = ID_ANI_QUESTION_BRICK;
	else if (type == BRICK_TYPE_EMPTY)
		aniId = ID_ANI_EMPTY_BRICK;

	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
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
	this->type = type;
	switch (type) {
	case BRICK_TYPE_GOLD:
		break;
	case BRICK_TYPE_QUESTION:
		break;
	case BRICK_TYPE_EMPTY:
		time_start = GetTickCount64();
		old_y = y;
		ay = BRICK_GRAVITY;
		vy = -BRICK_TRANSFORM_DEFLECT;
		break;
	}
}
