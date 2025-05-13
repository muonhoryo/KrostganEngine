
#include <LevelLoadingInfo.h>

using namespace sf;
using namespace std;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::EntitiesControl;


LevelLoadingInfo::LevelLoadingInfo(forward_list<UnitLoadInfo>& Units):Units(Units) {
}

KrostganEngine::Core::UnitLoadInfo::UnitLoadInfo(string Name,string TexturePath, Vector2f SpriteOffset, Vector2f Position,
	float Size,EntityBattleStats& BattleStats,Fraction EntityFraction)
	:BattleStats(BattleStats)
{
	this->Name = Name;
		this->TexturePath = TexturePath;
		this->SpriteOffset = SpriteOffset;
		this->Position = Position;
		this->Size = Size;
		this->EntityFraction = EntityFraction;
}
