
#include <UserInterfaceManager.h>
#include <UIMan_WinResizeEvSubs.h>

using namespace KrostganEngine::Core;
using namespace KrostganEngine::UI;

void UserInterfaceManager::Initialize(){
	Vector2f size = (Vector2f)Engine::GetScreenSize();
	Vector2f pos = Vector2f(-size.x * 0.5, -size.y * 0.5);
	UserInterface = new UIEmpty(pos, DEFAULT_SCALE,DEFAULT_ANCHOR ,size);
	Engine::ResizeWindowEvent.Add(new UIMan_WinResizeEvSubs(*UserInterface));
	new UIRootMover(*UserInterface);
}

UserInterfaceManager::UIRootMover::UIRootMover(UIEmpty& Root)
	:Root(Root){

}

void UserInterfaceManager::UIRootMover::Update(CallbackRecArgs_LUpd args) {
	Vector2f size = (Vector2f)Engine::GetScreenSize();
	Vector2f pos = Vector2f(-size.x * 0.5, -size.y * 0.5);
	pos += Engine::GetCameraPos();
	Root.SetGlobalPosition(pos);
}