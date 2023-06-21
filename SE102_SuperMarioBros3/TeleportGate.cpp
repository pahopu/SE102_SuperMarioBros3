#include "Game.h"
#include "Mario.h"
#include "PlayScene.h"
#include "TeleportGate.h"

void CTeleportGate::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	if (dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene())) {
		CMario* mario = dynamic_cast<CMario*>(((CPlayScene*)(CGame::GetInstance()->GetCurrentScene()))->GetPlayer());

		vector<LPGAMEOBJECT> objects;
		objects.clear();
		objects.push_back(mario);

		CCollision::GetInstance()->Process(this, &objects);
	}
}

void CTeleportGate::OnCollisionWith(LPGAMEOBJECT obj) {
	CMario* mario = dynamic_cast<CMario*>(obj);

	switch (direction) {
	case TELEPORT_DIRECTION_DOWN:
		if (mario->IsCanGetIntoPipe() == MARIO_GETINTO_PIPE_DOWN) { // Mario get down into pipe(sewer)
			this->TeleObject(obj);
			//DebugOut(L"[Teleport] teleport Mario\n");
		}
		break;

	case TELEPORT_DIRECTION_UP:
		if (mario->IsCanGetIntoPipe() == MARIO_GETINTO_PIPE_UP) { // Mario get up into pipe(sewer)
			this->TeleObject(obj);
			//DebugOut(L"[Teleport] teleport Mario\n");
		}
		break;
	}
}

void CTeleportGate::TeleObject(LPGAMEOBJECT obj) {
	obj->SetPosition(des_x, des_y);
}

void CTeleportGate::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x - TELEPORT_BBOX_WIDTH / 2;
	top = y - TELEPORT_BBOX_HEIGHT / 2;
	right = left + TELEPORT_BBOX_WIDTH;
	bottom = top + TELEPORT_BBOX_HEIGHT;
}

void CTeleportGate::Render() {
	RenderBoundingBox();
}