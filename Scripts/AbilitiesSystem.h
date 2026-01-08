#pragma once

#include <CatalogObject.h>
#include <vector>
#include <IHierarchyTrObj.h>

using namespace std;
using namespace KrostganEngine::Core;

namespace KrostganEngine::GameObjects {

	class AbilityUserObject;


	class Ability : public CatalogObject{

	public:
		virtual ~Ability();

	protected:
		Ability(size_t CatalogID, std::byte SubcatalogID);
		Ability();

		virtual void OnAddToUser(AbilityUserObject& user) = 0;
		virtual void OnRemoveFromUser(AbilityUserObject& user) = 0;

	private:
		friend class AbilityUserObject;
	};

	class AbilityUserObject : public virtual IHierarchyTrObj {

	public:
		virtual ~AbilityUserObject();

		/// <summary>
		/// Return order of added ability in abilities' array.
		/// Return SIZE_MAX if input ability has a clone in array.
		/// </summary>
		/// <param name="ability"></param>
		/// <returns></returns>
		size_t AddAbility(Ability& ability);
		/// <summary>
		/// Return order of added ability in abilities' array.
		/// Return SIZE_MAX if input ability has a clone in array.
		/// </summary>
		/// <param name="ability"></param>
		/// <returns></returns>
		size_t AddAbilityFromCatalog(size_t catID, std::byte subCatID = (std::byte)0);
		void RemoveAbility(Ability& ability);
		void RemoveCatalogAbility(size_t catID, std::byte subCatID = (std::byte)0);
		void RemoveAbilityByArrIndex(size_t index);

		/// <summary>
		/// Return nullptr if object hasn't any abilities or input index out of range of array
		/// </summary>
		/// <param name="orderInArr"></param>
		/// <returns></returns>
		Ability* GetAbility(size_t orderInArr) const;
		vector<Ability*>::iterator GetAbilitiesIter_Begin() const;
		vector<Ability*>::iterator GetAbilitiesIter_End() const;
		size_t GetAbilitiesCount() const;
		bool HasAbilities() const;

	protected:
		AbilityUserObject();

	private:
		bool CheckAbilityClone(size_t catID, std::byte subCatID) const;

		vector<Ability*>* Abilities = nullptr;
	};
}