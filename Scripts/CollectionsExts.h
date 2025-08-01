#pragma once

#include <forward_list>
#include <string>

using namespace std;

namespace KrostganEngine {
	struct CollectionsExts {
		/// <summary>
		/// Return string::npos if list hasn't value
		/// </summary>
		/// <typeparam name="TCollectionsType"></typeparam>
		/// <typeparam name="TElementsType"></typeparam>
		/// <param name="list"></param>
		/// <param name="value"></param>
		/// <returns></returns>
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

		template <typename TCollectionsType,typename TElementsType>
		static bool Contains(const TCollectionsType& list, TElementsType const& element) {
			for (TElementsType el: list) {
				if (el == element) {
					return true;
				}
			}
			return false;
		}

		/// <summary>
		/// Return true if element was removed
		/// </summary>
		/// <typeparam name="TCollectionsType"></typeparam>
		/// <typeparam name="TElementsType"></typeparam>
		/// <param name="list"></param>
		/// <param name="elementToRem"></param>
		/// <returns></returns>
		template <typename TCollectionsType, typename TElementsType>
		static bool Remove(TCollectionsType& list, TElementsType const& elementToRem) {
			auto it = list.begin();
			auto end = list.end();
			for (;it != end;++it) {
				if ((*it) == elementToRem) {
					list.erase(it);
					return true;
				}
			}
			return false;
		}
	};
}