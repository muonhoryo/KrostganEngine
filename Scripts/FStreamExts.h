#pragma once

#include <string>

using namespace std;

namespace KrostganEngine {
	struct FStreamExts {

		static void		ClearPath	(string& path);
		static char*	ReadToEnd	(const string& path);
		static bool		ParseBool	(const string& servalue);

	private:
		FStreamExts();
	};
}