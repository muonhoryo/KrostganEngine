
#include <VectExts.h>
#include <string>
#include <SFML/System.hpp>

using namespace sf;
using namespace std;
using namespace KrostganEngine;


Vector2f VectExts::ParseVec2f(const string& serVect) {
	size_t index = serVect.find(VECTOR_VALUES_SEP_SYM);
	if (index == string::npos)
		throw exception("Cant parse vector2");

	float x;
	float y;
	string seValue = serVect.substr(0, index);
	x = stof(seValue.c_str());
	seValue.clear();
	seValue.append(serVect.substr(index + 1, serVect.length() - index - 1));
	y = stof(seValue.c_str());
	return Vector2f(x, y);
}