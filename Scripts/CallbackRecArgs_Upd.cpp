
#include <ICallbackRec_Upd.h>
#include <vector>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

using namespace KrostganEngine::GameObjects;
using namespace std;
using namespace sf;

CallbackRecArgs_Upd::CallbackRecArgs_Upd(const vector<Event>& PlayerInput):
PlayerInput(PlayerInput){

}