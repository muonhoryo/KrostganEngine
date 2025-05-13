#pragma once

#include <LevelLoading.h>
#include <string>
#include <EntityBattleStats.h>

using namespace std;
using namespace KrostganEngine::GameObjects;

namespace KrostganEngine {
	namespace Core {
		class LevelSerialization {
		public:
			static LevelLoadingInfo& DeserializeLevel(string serPath);
			static void SerializeLevel(string serPath, LevelLoadingInfo levelInfo);

			static inline const string PAR_DEF_NAME_END_SYM = ":";
			static inline const string OBJECTS_SEP_LINE = "endl;";
		private:
			LevelSerialization() {};

			static UnitLoadInfo* ParseUnitInfo(vector<string>* params);
			static bool GetSerValueOfParam(vector<string>& params, const string& paramName, string* output);
			static EntityBattleStats& GetBattleStats(vector<string>& params, string* buffer);
		};

		struct LevelSerializationParDefNames {
			static inline const string OBJECT_NAME = "Name";
			static inline const string OBJECT_SPRITE_PATH = "SpritePath";
			static inline const string OBJECT_SPRITE_OFFSET = "SpriteOffset";
			static inline const string OBJECT_POSITION = "Position";
			static inline const string OBJECT_SIZE = "Size";

			static inline const string ENTITY_MAX_HP = "MaxHP";
			static inline const string ENTITY_CURR_HP = "CurrentHP";
			static inline const string ENTITY_AA_DAMAGE = "AADamage";
			static inline const string ENTITY_AA_SPEED = "AASpeed";
			static inline const string ENTITY_AA_RADIUS = "AARadius";
			static inline const string ENTITY_FRACTION = "Fraction";

			static inline const string UNIT_MOVINGSPEED = "MovingSpeed";
		};
	}
}