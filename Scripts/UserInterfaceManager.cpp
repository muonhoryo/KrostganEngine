
#include <UserInterfaceManager.h>
#include <UIMan_WinResizeEvSubs.h>
#include <UIMan_ZoomChangedEvSubs.h>

using namespace KrostganEngine::Core;
using namespace KrostganEngine::UI;

void UserInterfaceManager::Initialize(){
	Vector2f size = (Vector2f)Engine::GetScreenSize();
	Vector2f pos = Vector2f(-size.x * 0.5, -size.y * 0.5);
	UserInterface = new UIRoot(size);
	UserInterface->SetGlobalPosition(pos);
	Engine::ResizeWindowEvent.Add(*new UIMan_WinResizeEvSubs(*UserInterface));
	Engine::ViewZoomChangedEvent.Add(*new UIMan_ZoomChangedEvSubs(*UserInterface));
	new UIRootMover(*UserInterface);
}
void UserInterfaceManager::Unload() {
	for (auto depend : UIDependencies) {
		delete depend;
	}
	UIDependencies.clear();
	FirstSelEntityDepend = new FirstChoosenEntityDependsManager();
	UIDependencies.push_back(FirstSelEntityDepend);
	UserInterface->DestroyChildren();
}

UserInterfaceManager::UIRootMover::UIRootMover(UIRoot& Root)
	:Root(Root){

	DestroyOnUnload = false;
}

void UserInterfaceManager::UIRootMover::Update(CallbackRecArgs_LUpd args) {
	Vector2f size = (Vector2f)Engine::GetScreenSize();
	size *= Engine::GetZoom();
	Vector2f pos = Vector2f(-size.x * 0.5, -size.y * 0.5);
	pos += Engine::GetCameraPos();
	Root.SetGlobalPosition(pos);
}