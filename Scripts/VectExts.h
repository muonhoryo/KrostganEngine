#pragma once

#include <SFML/System.hpp>
#include <string>

using namespace sf;
using namespace std;

namespace KrostganEngine {

	//Consts

	static const char VECTOR_VALUES_SEP_SYM = ';';

	//Templates methods

	template <typename T>
	static Vector2<T> ParseVec2(const string& serVect,T (*func)(const string& )) {
		size_t index = serVect.find(VECTOR_VALUES_SEP_SYM);
		if (index == string::npos)
			throw exception("Cant parse vector2");

		T x;
		T y;
		string seValue = serVect.substr(0, index);
		x = func(seValue.c_str());
		seValue.clear();
		seValue.append(serVect.substr(index + 1, serVect.length() - index - 1));
		y = func(seValue.c_str());
		return Vector2<T>(x, y);
	}

	template<typename T>
	static string ToString(const Vector2<T>& vect) {
		return "{ " + to_string(vect.x) + " ; " + to_string(vect.y) + " }";
	}

	template<typename T>
	static float Dot(Vector2<T> vect1, Vector2<T> vect2) {
		return vect1.x * vect2.x + vect1.y * vect2.y;
	}

	template<typename T>
	static float SquareLength(Vector2<T> vect) {
		return Dot(vect, vect);
	}

	template <typename T>
	static float Length(Vector2<T> vect) {
		return sqrt((float)SquareLength<T>(vect));
	}

	template <typename T>
	static Vector2f Normalize(Vector2<T> vect) {
		float len = Length(vect);
		return Vector2f(vect.x / len, vect.y / len);
	}

	//Global methods

	static Vector2f ParseVec2f(const string& serVect) {
		float(*func)(const string&) = [](const string& buff) {return stof(buff);};
		return ParseVec2<float>(serVect,func);
	}
	static Vector2u ParseVec2u(const string& serVect) {
		unsigned int (*func)(const string&) = [](const string& buff) {return (unsigned int)abs(stoi(buff));};
		return ParseVec2<unsigned int>(serVect, func);
	}
}