#pragma once

#include <vector>
#include <string>
#include <EngineConfig.h>
#include <ValuesListDeserializer.h>

using namespace std;

namespace KrostganEngine {
	namespace Core {
		class EngineConfigLoad:public ValuesListDeserializer {
		public:
			EngineConfigLoad();
			~EngineConfigLoad() {}

			EngineConfig& LoadEngineConfig();
			EngineConfig& GetLoadedConfig();
		private:
			EngineConfig& LoadedConfig;

			const string GetFilePath() override;
			const char GetValuesDefEndSym() override;

			static const string CONFIG_PATH;
			static const char CONFIG_DEF_END_SYM;
		};
	}
}