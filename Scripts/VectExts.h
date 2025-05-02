#pragma once

#include <SFML/System.hpp>
#include <string>

using namespace sf;
using namespace std;

namespace KrostganEngine {
	struct VectExts {

		static Vector2f ParseVec2f(const string& serVect);

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
			return sqrt(SquareLength<T>(vect));
		}
		template <typename T>
		static Vector2f Normalize(Vector2<T> vect) {
			float len = Length(vect);
			return Vector2f(vect.x / len, vect.y / len);
		}

	private:
		VectExts();

		static inline const char VECTOR_VALUES_SEP_SYM = ';';
	};
}