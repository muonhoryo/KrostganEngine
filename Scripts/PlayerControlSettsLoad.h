#pragma once

#include <PlayerControlSettings.h>
#include <ValuesListDeserializer.h>

using namespace KrostganEngine::PlayerControl;

namespace KrostganEngine::Core {

	class PlayerControlSettsLoad : public ValuesListDeserializer {
	public:
		PlayerControlSettsLoad();
		virtual ~PlayerControlSettsLoad();

		PlayerControlSettings& LoadPlayerCtrlSettings();
		PlayerControlSettings& GetLoadedPlayerCtrlSettings() {
			return LoadedPlayerCtrlSetts; 
		}

	private:
		PlayerControlSettings& LoadedPlayerCtrlSetts;

		const string GetFilePath() override { 
			return CONSTS_PATH; 
		}
		const char GetValuesDefEndSym() override {
			return CONFIG_DEF_END_SYM;
		}

		static inline const string CONSTS_PATH = "ControlSettings.txt";
		static inline const char CONFIG_DEF_END_SYM = ':';

	};
}