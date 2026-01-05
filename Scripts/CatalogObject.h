#pragma once

#include <map>
#include <CollectionsExts.h>

using namespace std;

namespace KrostganEngine::Core {
	class CatalogObject {

	private:
		size_t		CatalogID;
		std::byte	SubcatalogID;		//SubcatalogID's contating currently doesn't work cause level loading system doesn't indexes object's sub info during loading

	public:
		size_t GetCatalogID() const {
			return CatalogID;
		}
		std::byte GetSubcatalogID() const {
			return SubcatalogID;
		}

	protected:
		CatalogObject(size_t CatalogID, std::byte SubcatalogID)
			:CatalogID(CatalogID), SubcatalogID(SubcatalogID) {}

		CatalogObject();

	public:
		struct EqCompFunc_ByID_n_SubID_ref final : public CollectionsExts::EqualCompareFunc<CatalogObject*> {

			bool Equal(CatalogObject* const& first, CatalogObject* const& second) const override {

				return first->CatalogID == second->CatalogID &&
					first->SubcatalogID == second->SubcatalogID;
			}
		};

		template<typename TTargetType>
		struct Predicate_ByID_n_SubID_ref final : public CollectionsExts::Predicate<TTargetType* const&> {

			Predicate_ByID_n_SubID_ref(size_t ID, std::byte SubID) 
				:ID(ID), SubID(SubID){

			}

			bool Condition(TTargetType* const& input) const override {
				return input->CatalogID == ID && input->SubcatalogID == SubID;
			}

			size_t ID;
			std::byte SubID;
		};

		static inline const EqCompFunc_ByID_n_SubID_ref Instance_EqCompFunc_ID_n_SubID_ref;
	};
}