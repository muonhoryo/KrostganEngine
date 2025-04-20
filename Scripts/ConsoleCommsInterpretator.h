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
		private:
			static vector<string>* SplitCommandSyntax(string input);

			static inline const string ZOOM_COMMAND = "zoom";
			static inline const char& SPLIT_COMM_DELIMS = {' '};
		};
	}
}


