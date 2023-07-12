#include "Game.h"
#include "debug.h"
#include "Portal.h"
#include "Control.h"
#include "IntroScene.h"
#include "IntroKeyEventHandler.h"

void CIntroKeyEventHandler::OnKeyDown(int KeyCode) {
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	CControl* control = CControl::GetInstance();

	switch (KeyCode) {
	case DIK_S:
		if (control->IsActivatingMode()) { // switch to WorldMap
			control->DeactiveControl(CONTROL_TYPE_MODE);

			DebugOut(L"Switch scene\n");
			((LPINTROSCENE)CGame::GetInstance()->GetCurrentScene())->GetPortal()->SwitchScene();
		}
		else control->ActiveControl(CONTROL_TYPE_MODE);

		break;

	case DIK_ESCAPE:
		if (control->IsPausing()) control->DeactiveControl(CONTROL_TYPE_PAUSE);
		else control->ActiveControl(CONTROL_TYPE_PAUSE);

		break;
	}
}

void CIntroKeyEventHandler::OnKeyUp(int KeyCode) {
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
}

void CIntroKeyEventHandler::KeyState(BYTE* states) {
	LPGAME game = CGame::GetInstance();

	float cx, cy;
	game->GetCamPos(cx, cy);
	if (game->IsKeyDown(DIK_RIGHT))
		game->SetCamPos(cx + 1, cy);
	else if (game->IsKeyDown(DIK_LEFT))
		game->SetCamPos(cx - 1, cy);
}