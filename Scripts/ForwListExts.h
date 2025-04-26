#pragma once

#include <forward_list>
#include <string>

using namespace std;

namespace KrostganEngine {
	struct ForwListExts {
		template <typename T>
		static size_t IndexOf(const forward_list<T>& list, T const& value) {
			size_t i = 0;
			for (T el : list) {
				if (el == value) {
					return i;
				}
				i += 1;
			}
			return string::npos;
		}
	};
}