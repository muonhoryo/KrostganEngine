#pragma once

#include <vector>
#include <string>
#include <EngineConfig.h>

using namespace std;

namespace KrostganEngine {
	namespace Core {
		class EngineConfigLoad {

		private:
			struct ConfigPosition {
				ConfigPosition(string Name, string Value) {
					this->Name = Name;
					this->Value = Value;
				}
				ConfigPosition() :ConfigPosition("", "") {}
				string Name;
				string Value;
			};


		public:
			EngineConfigLoad();
			~EngineConfigLoad();

			const EngineConfig& LoadEngineConfig();
			const EngineConfig& GetLoadedConfig();
		private:
			bool TryGetConfigValue(const string& configName, string* value);
			void InitializeConfig();

			vector<ConfigPosition> ConfigArr;
			EngineConfig LoadedConfig;

			static const string CONFIG_PATH;
			static const char CONFIG_DEF_END_SYM;
		};
	}
}