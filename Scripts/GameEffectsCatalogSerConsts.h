#pragma once

#include <string>

using namespace std;

namespace KrostganEngine::GameObjects {

	struct GameEffLoad_Types {

		static inline const string TYPE_INSTANT		= "Instant";
		static inline const string TYPE_PERMANENT	= "Permanent";
		static inline const string TYPE_TEMPORAL	= "Temporal";
		static inline const string TYPE_PERIODICAL	= "Periodical";

	};

	struct GameEffLoad_XMLChildrenTypes {

		static inline const string TYPE_SUBINFO			= "Subcatalog";
		static inline const string TYPE_GENERALGAMEEFF	= "GameEffect";
	};
	
	struct GameEffLoad_GeneralGameEffTypes {

		static inline const string TYPE_DEF = "Type";

		static inline const string DESERTER					= "Deserter";
		static inline const string DISARM					= "Disarm";
		static inline const string ENTBATSTAT_CONST_BOOL	= "EntBatStat_Const_Bool";
		static inline const string ENTBATSTAT_MULT			= "EntBatStat_Mult";
		static inline const string ADDDUREFF				= "AddDurEff";

		static bool IsGameEffectType_Instant(const string& type) {

			return type == ADDDUREFF;
		}
		static bool IsGameEffectType_Durable(const string& type) {

			return
				type ==	DESERTER ||
				type ==	DISARM ||
				type ==	ENTBATSTAT_CONST_BOOL ||
				type ==	ENTBATSTAT_MULT;
		}
		static bool IsGameEffectType_TimeDepended(const string& type) {
			return false;
		}
	};
	struct GameEffLoad_ParamDefNames {

		static inline const string EFFECT_NAME				= "Name";
		static inline const string EFFECT_STACKABLE			= "IsStackable";

		static inline const string EFFECT_TEMP_DURATION			= "EffectTime";

		static inline const string EFFECT_PERIOD_TICK_TIME			= "TickEff_SubCatalogID";
		static inline const string EFFECT_PERIOD_TICK_CATALOG_ID	= "TickEff_CatalogID";
		static inline const string EFFECT_PERIOD_TICK_SUBCATALOG_ID	= "TickEff_SubCatalogID";
		
		static inline const string EFFECT_DESERTER_FRACTION		= "DesertingFraction";

		static inline const string EFFECT_STATMOD_PARAMNAME		= "ParamName";
		static inline const string EFFECT_STATMOD_VALUE			= "Value";

		static inline const string GEN_EFFECT_ADDGAMEEFF_CATALOG_ID		= "Add_CatalogID";
		static inline const string GEN_EFFECT_ADDGAMEEFF_SUB_CATALOG_ID = "Add_SubCatalogID";
	};
}