
#include <Extensions.h>
#include <string>
#include <SFML/System.hpp>

using namespace sf;
using namespace std;
using namespace KrostganEngine;

Vector2f Extensions::ParseVec2f(const string& serVect) {
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
string Extensions::ToString(const Vector2f& vect) {
	return "{ " + to_string(vect.x) + " ; " + to_string(vect.y) + " }";
}
void Extensions::ClearPath(string* path) {
	long long index = -1;
	long long nextIndex = -1;
	long long count = path->size();
	char sym;
	while (nextIndex<count) {
		++nextIndex;
		sym = (*path)[nextIndex];
		if (sym == ' ')
			++index;
		else
			break;
	}
	if (index >= 0) {
		path->erase(0, index + 1);
	}
}