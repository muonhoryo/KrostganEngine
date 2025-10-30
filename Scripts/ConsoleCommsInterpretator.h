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

			/// <summary>
			/// Return true if is Zoom command
			/// </summary>
			/// <param name="input"></param>
			/// <returns></returns>
			static bool InterpretateComm_Zoom(const string& input);
			
			/// <summary>
			/// Return true if is Divine commander command
			/// </summary>
			/// <param name="input"></param>
			/// <returns></returns>
			static bool InterpretateComm_DivComm(const string& input);
			
			/// <summary>
			/// Return true if is Camera moving command
			/// </summary>
			/// <param name="input"></param>
			/// <returns></returns>
			static bool InterpretateComm_CamMov(const string& input);

			/// <summary>
			/// Return true if is Immortality army command
			/// </summary>
			/// <param name="input"></param>
			/// <returns></returns>
			static bool InterpretateComm_ImmArmy(const string& input);
		private:
			static vector<string>& SplitCommandSyntax(const string& input);
			static void PrintInterpetatorMessage(const string& message);

			static inline const string ZOOM_COMMAND = "zoom";
			static inline const string DIVIVE_COMMANDER_COMMAND = "divcomm";
			static inline const string CAMERA_MOVING_COMMAND = "cammov";
			static inline const string IMMORTAL_ARMY_COMMAND = "immarmy";

			static inline const char& SPLIT_COMM_DELIMS = {' '};
		};
	}
}


