#pragma once

#include <forward_list>
#include <string>

using namespace std;

namespace KrostganEngine {
	struct CollectionsExts {
		template <typename TCollectionsType,typename TElementsType>
		static size_t IndexOf(const TCollectionsType& list,TElementsType const& value) {
			size_t i = 0;
			for (TElementsType el : list) {
				if (el == value) {
					return i;
				}
				i += 1;
			}
			return string::npos;
		}
	};
}