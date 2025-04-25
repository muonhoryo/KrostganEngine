#pragma once

#include <SFML/System.hpp>
#include <string>
#include  <forward_list>

using namespace std;
using namespace sf;

namespace KrostganEngine {
	struct Extensions
	{
		static Vector2f ParseVec2f(const string& serVect);
		static string ToString(const Vector2f& vect);
		static void ClearPath(string* path);

		template <typename T>
		static size_t IndexOf(const forward_list<T>& list,T const& value) {
			size_t i = 0;
			for (T el : list) {
				if (el == value) {
					return i;
				}
				i += 1;
			}
			return string::npos;
		}

	private:
		Extensions() {};

		static inline const char VECTOR_VALUES_SEP_SYM = ';';
	};
}


