
#include <CursorManager.h>

using namespace KrostganEngine::UI;

CursorManager::CursorManager(RenderWindow& RendWin, Cursor& Curs_Default, Cursor& Curs_AttackOrder)
	:RendWin(RendWin),
	Curs_Default(Curs_Default),
	Curs_AttackOrder(Curs_AttackOrder){
}

void CursorManager::SetDefaultSprite() {
	SetCursor(Curs_Default);
}
void CursorManager::SetAttackOrderSprite() {
	SetCursor(Curs_AttackOrder);
}

void CursorManager::SetCursor(Cursor& curs) {
	RendWin.setMouseCursor(curs);
}