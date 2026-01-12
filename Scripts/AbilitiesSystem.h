#pragma once

#include <CatalogObject.h>
#include <vector>
#include <IHierarchyTrObj.h>
#include <ICallbackRec_Upd.h>

using namespace std;
using namespace KrostganEngine::Core;

namespace KrostganEngine::GameObjects {

	class AbilityUserObject;


	class Ability : public CatalogObject, public virtual ICallbackRec_Upd{

	public:
		virtual ~Ability();

		void TurnToCooldown(float duration);
		void ResetCooldown();
		bool Get_IsOnCooldown() const;
		float GetCooldownDuration() const;

		void Update(CallbackRecArgs_Upd args) override;

	protected:
		Ability(size_t CatalogID, std::byte SubcatalogID);
		Ability();

		virtual void OnAddToUser(AbilityUserObject& user) {};
		virtual void OnRemoveFromUser(AbilityUserObject& user) {};

	private:
		friend class AbilityUserObject;
		Clock CooldownTimer;
		float CooldownDuration = 0;
		bool IsOnCooldown = false;
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
		void RemoveAbility(Ability& ability, bool isSafe = false);
		void RemoveCatalogAbility(size_t catID, std::byte subCatID = (std::byte)0, bool isSafe = false);
		void RemoveAbilityByArrIndex(size_t index, bool isSafe = false);

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
		void RemoveAbilityFromArr(size_t index, bool isSafe = false);
		size_t AddNewAbilityToArr(Ability& ability);

		vector<Ability*>* Abilities = nullptr;
	};
}