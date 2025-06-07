
#include <LevelLoadingInfo.h>

using namespace sf;
using namespace std;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::EntitiesControl;

LevelLoadingInfo::~LevelLoadingInfo() {
	for (auto& unit :Units) {
		delete &unit;
	}
	for (auto& wall : Walls){
		delete& wall;
	}
	delete &Units;
	delete &Walls;
}
