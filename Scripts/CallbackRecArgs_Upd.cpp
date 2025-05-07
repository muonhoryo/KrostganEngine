
#include <ICallbackRec_Upd.h>
#include <vector>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

using namespace KrostganEngine::Core;
using namespace std;
using namespace sf;

CallbackRecArgs_Upd::CallbackRecArgs_Upd(const vector<Event>& PlayerInput,float LastFrameDeltaTime):
PlayerInput(PlayerInput){
	this->LastFrameDeltaTime = LastFrameDeltaTime;
}