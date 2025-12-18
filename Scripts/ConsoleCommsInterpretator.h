#pragma once

#include <string>
#include <vector>

using namespace std;

namespace KrostganEngine {
	namespace Debug {
		class ConsoleCommsInterpretator
		{
		public:
			static void ExecuteCommand(const string& input);

			//Commands below return true if input match the command syntax

			static bool InterpretateComm_Zoom(const string& input);
			
			static bool InterpretateComm_DivComm(const string& input);
			
			static bool InterpretateComm_CamMov(const string& input);

			static bool InterpretateComm_ImmArmy(const string& input);

			static bool InterpretateComm_Disarm(const string& input);

			static bool InterpretateComm_Rearm(const string& input);

			static bool InterpretateComm_WarFog(const string& input);

			static bool InterpretateComm_FracSet(const string& input);
		private:
			static vector<string>& SplitCommandSyntax(const string& input);
			static void PrintInterpetatorMessage(const string& message);

			static inline const string ZOOM_COMMAND					= "zoom";
			static inline const string DIVIVE_COMMANDER_COMMAND		= "divcomm";
			static inline const string CAMERA_MOVING_COMMAND		= "cammov";
			static inline const string IMMORTAL_ARMY_COMMAND		= "immarmy";
			static inline const string DISARM_COMMAND				= "disarm";
			static inline const string REARM_COMMAND				= "rearm";
			static inline const string WARFOG_COMMAND				= "warfog";
			static inline const string FRACSET_COMMAND				= "fracset";

			static inline const char& SPLIT_COMM_DELIMS = {' '};
		};
	}
}


