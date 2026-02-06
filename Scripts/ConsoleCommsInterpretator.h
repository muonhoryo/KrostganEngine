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

			static bool InterpretateComm_Zoom(const vector<string>& input);
			
			static bool InterpretateComm_DivComm(const vector<string>& input);
			
			static bool InterpretateComm_CamMov(const vector<string>& input);

			static bool InterpretateComm_ImmArmy(const vector<string>& input);

			static bool InterpretateComm_Disarm(const vector<string>& input);

			static bool InterpretateComm_Rearm(const vector<string>& input);

			static bool InterpretateComm_WarFog(const vector<string>& input);

			static bool InterpretateComm_FracSet(const vector<string>& input);

			static bool InterpretateComm_Print(const vector<string>& input);
		private:
			static vector<string>& SplitCommandSyntax(const string& input);
			static void PrintInterpetatorMessage(const string& message);

			/// <summary>
			/// Return nullptr if parameter is not key word
			/// </summary>
			/// <param name="splitInput"></param>
			/// <returns></returns>
			static string* PrintComm_TryInterpetateParameter(const vector<string>& splitInput);

			static inline const string ZOOM_COMMAND					= "zoom";
			static inline const string DIVIVE_COMMANDER_COMMAND		= "divcomm";
			static inline const string CAMERA_MOVING_COMMAND		= "cammov";
			static inline const string IMMORTAL_ARMY_COMMAND		= "immarmy";
			static inline const string DISARM_COMMAND				= "disarm";
			static inline const string REARM_COMMAND				= "rearm";
			static inline const string WARFOG_COMMAND				= "warfog";
			static inline const string FRACSET_COMMAND				= "fracset";
			static inline const string PRINT_COMMAND				= "print";

			static inline const string PRINT_PARAM_CAMERAPOS		= "campos";

			static inline const char& SPLIT_COMM_DELIMS = {' '};
		};
	}
}


