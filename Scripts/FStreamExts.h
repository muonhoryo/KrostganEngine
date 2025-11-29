#pragma once

#include <string>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

namespace KrostganEngine {
	struct FStreamExts {

		static void		ClearPath	(string& path);
		static char*	ReadToEnd	(const string& path);
		static bool		ParseBool	(const string& servalue);
		static char		SFKeyToChar	(Keyboard::Key key);

	private:
		FStreamExts();
	};
}