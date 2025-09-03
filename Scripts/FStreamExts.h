#pragma once

#include <string>

using namespace std;

namespace KrostganEngine {
	struct FStreamExts {

		static void		ClearPath	(string& path);
		static char*	ReadToEnd	(const string& path);

	private:
		FStreamExts();
	};
}