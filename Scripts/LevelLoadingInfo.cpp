
#include <LevelLoadingInfo.h>
#include <forward_list>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

using namespace sf;
using namespace std;
using namespace KrostganEngine::Core;


LevelLoadingInfo::LevelLoadingInfo(forward_list<UnitLoadInfo>& Units):Units(Units) {
}

KrostganEngine::Core::UnitLoadInfo::UnitLoadInfo(string Name,string TexturePath, Vector2f SpriteOffset, Vector2f Position,
	float Size,EntityBattleStats& BattleStats)
	:BattleStats(BattleStats)
{
	this->Name = Name;
		this->TexturePath = TexturePath;
		this->SpriteOffset = SpriteOffset;
		this->Position = Position;
		this->Size = Size;
}
