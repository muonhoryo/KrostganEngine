#pragma once

#include <string>

using namespace std;

namespace KrostganEngine::GameObjects {

	struct AbilitiesLoading_Types {

		static inline const string AURA				= "Aura";
		static inline const string NONTAR_DURABLE	= "NonTar_Durable";
		static inline const string NONTAR_SETAA		= "NonTar_SetAA";
		static inline const string NONTAR_TEMPEFF	= "NonTar_TempEff";
	};

	struct AbilitiesLoading_XMLChildrenType {

		static inline const string ABILITY_SUBINFO					= "SubCatalog";
		static inline const string ABILITY_NONTAR_SETAA_NEXTABILITY = "NextAbility";
	};

	struct AbilitiesLoading_ParamDefNames {

		static inline const string ABILITY_NAME				= "Name";
		static inline const string ABILITY_COOLDOWN_DUR		= "CooldownDuration";
		static inline const string ABILITY_CATALOG_ID		= "CatalogID";
		static inline const string ABILITY_SUB_CATALOG_ID	= "SubCatalogID";

		static inline const string ABILITY_GAMEEFF_CATALOGID		= "GameEff_CatalogID";
		static inline const string ABILITY_GAMEEFF_SUB_CATALOGID	= "GameEff_SubCatalogID";
		static inline const string ABILITY_GAMEEFF_DURATION			= "GameEff_Duration";

		static inline const string ABILITY_AURA_RANGE					= "Range";
		static inline const string ABILITY_AURA_TOTARGET_RELATIONMASK	= "ToTargetRelationMask";

		static inline const string ABILITY_NONTAR_DURABLE_CDOWN_SSTART	= "CooldownSinceStart";

		static inline const string ABILITY_NONTAR_SETAA_AAINDEX				= "AAIndex";
		static inline const string ABILITY_NONTAR_SETAA_NEXTAB_COOLDOWN		= "NextAbilityCooldown";
		static inline const string ABILITY_NONTAR_SETAA_DELETEGAMEEFFONREM	= "DeleteGameEffOnRemove";

	};
}