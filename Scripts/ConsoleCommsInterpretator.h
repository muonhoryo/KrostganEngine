#pragma once

#include <string>
#include <vector>

using namespace std;

namespace KrostganEngine {
	namespace Debug {
		class ConsoleCommsInterpretator
		{
		public:
			static void ExecuteCommand(string input);

			/// <summary>
			/// Return true if is Zoom command
			/// </summary>
			/// <param name="input"></param>
			/// <returns></returns>
			static bool InterpretateComm_Zoom(string& input);
			/// <summary>
			/// Return true if is Divine commander command
			/// </summary>
			/// <param name="input"></param>
			/// <returns></returns>
			static bool InterpretateComm_DivComm(string& input);
		private:
			static vector<string>* SplitCommandSyntax(string input);

			static inline const string ZOOM_COMMAND = "zoom";
			static inline const string DIVIVE_COMMANDER_COMMAND = "divcomm";

			static inline const char& SPLIT_COMM_DELIMS = {' '};
		};
	}
}


