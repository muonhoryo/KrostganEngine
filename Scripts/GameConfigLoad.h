#pragma once

#include <vector>
#include <string>

using namespace std;

namespace KrostganEngine {
	namespace Core {
		class GameConfigLoad {

		private:
			struct ConfigPosition {
				ConfigPosition(string Name,string Value) {
					this->Name = Name;
					this->Value = Value;
				}
				ConfigPosition() :ConfigPosition("", ""){}
				string Name;
				string Value;
			};

			vector<ConfigPosition> ConfigArr = vector<ConfigPosition>();
			static const string CONFIG_PATH;
			static const char CONFIG_DEF_END_SYM;
		
		public:
			GameConfigLoad();
			~GameConfigLoad();
			bool GetConfigValue(const string& configName,string* value);
		};
	}
}