#pragma once

#include <forward_list>
#include <string>
#include <vector>

using namespace std;

namespace KrostganEngine {
	struct CollectionsExts {

		//
		//
		// Delegates
		//
		//

		template<typename TInput>
		struct Predicate {
			virtual bool Condition(TInput input) const = 0;
		};
		template<typename TInput>
		struct CompareFunc {
			/// <summary>
			/// Return true if first less than second
			/// </summary>
			/// <param name="first"></param>
			/// <param name="second"></param>
			/// <returns></returns>
			virtual bool Compare(const TInput& first, const TInput& second) const = 0;
		};

		//
		//
		// Functions
		//
		//

		/// <summary>
		/// Return string::npos if list hasn't value
		/// </summary>
		/// <typeparam name="TCollectionsType"></typeparam>
		/// <typeparam name="TElementsType"></typeparam>
		/// <param name="list"></param>
		/// <param name="value"></param>
		/// <returns></returns>
		template <typename TCollectionType, typename TElementsType>
		static size_t IndexOf(const TCollectionType& collection, TElementsType const& value) {
			size_t i = 0;
			for (TElementsType const& el : collection) {
				if (el == value) {
					return i;
				}
				i += 1;
			}
			return string::npos;
		}
		template <typename TCollectionType, typename TElementsType>
		static size_t IndexOf(
			const TCollectionType& collection,
			const Predicate<TElementsType const&>& predicate) {

			size_t i = 0;
			for (TElementsType const& el : collection) {
				if (predicate.Condition(el))
					return i;
				i += 1;
			}
			return string::npos;
		}

		template<typename TInput>
		struct EqualCompareFunc {
			/// <summary>
			/// Return true if equal
			/// </summary>
			/// <param name="first"></param>
			/// <param name="second"></param>
			/// <returns></returns>
			virtual bool Equal(const TInput& first, const TInput& second) const = 0;
		};
		template <typename TCollectionType, typename TElementsType>
		static bool Contains(const TCollectionType& collection, TElementsType const& element) {
			for (TElementsType const& el : collection) {
				if (el == element) {
					return true;
				}
			}
			return false;
		}
		template <typename TCollectionType, typename TElementsType>
		static bool Contains(const TCollectionType& collection, TElementsType const& element, const EqualCompareFunc<TElementsType>& comparator) {
			for (TElementsType const& el : collection) {
				if (comparator.Equal(el, element)) {
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
		template <typename TElementsType, typename TCollectionType>
		static bool Remove(TCollectionType& collection, TElementsType const& elementToRem) {
			auto it = collection.begin();
			auto end = collection.end();
			for (;it != end;++it) {
				if ((*it) == elementToRem) {
					collection.erase(it);
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
		template <typename TElementsType, typename TCollectionType = forward_list<TElementsType>>
		static bool Remove(forward_list<TElementsType>& collection, TElementsType const& elementToRem) {
			auto it = collection.begin();
			auto preIt = collection.before_begin();
			auto end = collection.end();
			for (;it != end;++it) {
				if ((*it) == elementToRem) {
					collection.erase_after(preIt);
					return true;
				}
				++preIt;
			}
			return false;
		}

		template <typename TColectionType, typename TElementsType>
		static bool RemoveByPred(TColectionType& collection, const Predicate<TElementsType const&>& pred) {
			auto it = collection.begin();
			auto end = collection.end();
			for (;it != end;++it) {
				if (pred.Condition(*it)) {
					collection.erase(it);
					return true;
				}
			}
			return false;
		}

		template <typename TCollectionType>
		static size_t Size(const TCollectionType& collection) {
			return (size_t)distance(collection.begin(), collection.end());
		}

		/// <summary>
		/// Return nullptr if collection doesn't contain element
		/// </summary>
		/// <typeparam name="TCollectionType"></typeparam>
		/// <typeparam name="TElementsType"></typeparam>
		/// <param name="list"></param>
		/// <param name="elementToFind"></param>
		/// <returns></returns>
		template<typename TCollectionType, typename TElementsType>
		static TElementsType* Get(
			TCollectionType&						collection, 
			const Predicate<TElementsType const&>&	cond) {
			
			for (auto& el : collection) {
				if (cond.Condition(el))
					return &el;
			}
			return nullptr;
		}
		template<typename TCollectionType, typename TElementsType>
		static const TElementsType* Get_c(
			const TCollectionType& collection,
			const Predicate<TElementsType const&>& cond) {

			for (auto& el : collection) {
				if (cond.Condition(el))
					return &el;
			}
			return nullptr;
		}

		template<typename TElementsType, typename TCollectionType>
		static void InsertSorted(
			TCollectionType&							collection,
			const TElementsType&						element,
			const CompareFunc<TElementsType>&	comparator) {

			size_t size = Size<TCollectionType>(collection);
			if (size == 0) {
				collection.push_front(element);
			}
			else if (size == 1) {
				auto beg = collection.begin();
				if (comparator.Compare(element, (*beg)))
					collection.push_front(element);
				else
					collection.insert_after(beg, element);
			}
			else {

				auto it = collection.begin();
				if (comparator.Compare(element, (*it))) {
					collection.push_front(element);
					return;
				}
				auto postIt = collection.begin();
				auto end = collection.cend();
				++postIt;
				++postIt;
				++it;
				while (postIt != end) {
					if (comparator.Compare(element, (*postIt))) {
						collection.insert_after(it, element);
						return;
					}
					++postIt;
					++it;
				}
				collection.insert_after(it,element);
			}
		}

		template<typename TElementsType>
		static void InsertSorted(
			vector<TElementsType>&				collection,
			const TElementsType&				element,
			const CompareFunc<TElementsType>&	comparator){

			size_t size = collection.size();
			if (size == 0) {
				collection.push_back(element);
			}
			else if (size == 1) {
				if (comparator.Compare(element, collection[0]))
					collection.insert(collection.cbegin(), element);
				else
					collection.push_back(element);
			}
			else {
				if (comparator.Compare(element, collection[0])) {
					collection.insert(collection.cbegin(), element);
					return;
				}
				auto it = collection.cbegin();
				++it;
				auto end = collection.cend();
				while (it != end) {
					if (comparator.Compare(element, (*it))) {
						collection.insert(it, element);
						return;
					}
					++it;
				}
				collection.push_back(element);
			}
		}

		template<typename TElementsType, typename TCollectionType>
		static void Insert(
			TCollectionType&		collection,
			const TElementsType&	element,
			size_t					insertPos){
			
			size_t size = collection.size();
			if (size > insertPos)
				throw exception("Insert position is out of range");

			auto it = collection.begin();
			for (size_t i = 0;i < insertPos;++i) {
				++it;
			}
			collection.insert(it, element);
		}

		template<typename TCollectionType>
		static char* Join(const TCollectionType& collection) {

			string testStr;
			size_t size = 0;
			for (auto& str : collection) {

				size += str.size();
			}
			char* result = new char[size];
			char* offset = result;
			const char* buffer = nullptr;
			for (auto& str : collection) {

				buffer = str.c_str();
				strcpy_s(offset, str.size()+1, buffer);
				offset += str.size();
			}
			return result;
		}
	};
}