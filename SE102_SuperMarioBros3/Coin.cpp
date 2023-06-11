#include "Coin.h"

void CCoin::Render()
{
	int aniId = ID_ANI_COIN;
	if (ay) aniId = ID_ANI_COIN_DEFLECT;

	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniId)->Render(x, y);

	//RenderBoundingBox();
}

void CCoin::Update(DWORD dt) {
	if (vy == 0 && ay == 0)
		return;

	if (ay != 0 && vy > 0)
		Delete();

	if (ay != 0) {
		vy += ay * dt;
		y += vy * dt;
	}
}

void CCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - COIN_BBOX_WIDTH / 2;
	t = y - COIN_BBOX_HEIGHT / 2;
	r = l + COIN_BBOX_WIDTH;
	b = t + COIN_BBOX_HEIGHT;
}

void CCoin::Deflected(int direction) {
	ay = COIN_GRAVITY;
	vy = -COIN_DEFLECT;
}
