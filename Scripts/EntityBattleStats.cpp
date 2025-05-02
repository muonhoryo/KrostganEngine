
#include <EntityBattleStats.h>
#include <iostream>

using namespace std;
using namespace KrostganEngine::GameObjects;

EntityBattleStats::EntityBattleStats() 
{
	MovingSpeed = 0;
}

float EntityBattleStats::GetMovingSpeed() const {
	return MovingSpeed;
}

void EntityBattleStats::SetMovingSpeed(float speed){
	if (speed < 0)
		throw exception("Moving spedd cannot be less than zero.");
	
	MovingSpeed = speed;
}