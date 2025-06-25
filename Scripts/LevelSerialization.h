#pragma once

#include <LevelLoading.h>
#include <string>
#include <EntityBattleStats.h>
#include <forward_list>
#include <vector>

using namespace std;
using namespace KrostganEngine::GameObjects;

namespace KrostganEngine::Core {
	class LevelSerialization {
	public:
		static LevelLoadingInfo& DeserializeLevel(string serPath);
		static void SerializeLevel(string serPath, LevelLoadingInfo levelInfo);

	private:
		LevelSerialization() {}
	};
}