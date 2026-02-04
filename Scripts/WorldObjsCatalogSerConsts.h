#pragma once

#include <string>

using namespace std;

namespace KrostganEngine::GameObjects {

	struct WorldObjsLoad_Type{

		static inline const string OBJECT_TYPE_UNIT				= "Unit";
		static inline const string OBJECT_TYPE_WALL				= "Wall";
		static inline const string OBJECT_TYPE_HERO				= "Hero";
		static inline const string OBJECT_TYPE_SPRITE			= "Sprite";
		static inline const string OBJECT_TYPE_AA_PROJECTILE	= "Projectile";
		static inline const string OBJECT_TYPE_DECORATION		= "Decoration";
		static inline const string OBJECT_TYPE_AURA				= "Aura";
	};
	struct WorldObjsLoad_XMLChildrenType {

		static inline const string SUBINFO		= "Subcatalog";
		static inline const string CHILDREN		= "Children";
		static inline const string CHILD		= "Child";
		static inline const string AASTATS		= "AAStats";
		static inline const string BATSTATS		= "BattleStats";
		static inline const string COLLIDER		= "Collider";
		static inline const string ABILITY		= "Ability";
	};
	struct WorldObjsLoad_ParamDefNames {

		static inline const string OBJECT_NAME = "Name";
		static inline const string OBJECT_POSITION = "Position";
		static inline const string OBJECT_ROTATION = "Rotation";
		static inline const string OBJECT_SIZE = "Size";
		static inline const string OBJECT_TYPE = "Type";

		static inline const string OBJECT_REND_WARFOG_ISHIDEN = "WarFog_IsHiden";
		static inline const string OBJECT_REND_WARFOG_ISSHOWED = "WarFog_IsShowed";
		static inline const string OBJECT_REND_LATERENDER = "LateRender";

		static inline const string OBJECT_FRACTION = "Fraction";

		static inline const string IMAGEUSR_SPRITE_SOURCE = "SpriteSource";
		static inline const string IMAGEUSR_SPRITE_LAYER = "Layer";
		static inline const string SPRITE_ORIGIN = "Origin";

		static inline const string GAMEOBJ_ISSOLID_COLL = "SolidCollision";

		static inline const string ATTBLEOBJ_HITEFF_SPRITE_SOURCE = "HitEffectSprite";

		static inline const string ENTITY_SELECT_AREA_SOURCE = "SelectionAreaSource";
		static inline const string ENTITY_HPBAR_SPRITE_SOURCE = "HPBarSprite";
		static inline const string ENTITY_HPBAR_MASK = "HPBarMask";

		static inline const string DECOR_HP_CURRENT = "CurrentHP";
		static inline const string DECOR_HP_MAX = "MaxHP";
		static inline const string DECOR_ISTARGBLE_FORAA = "IsTargetableForAA";

		static inline const string AURA_TOTAR_RELATIONMASK = "ToTargetRelationMask";

		static inline const string PHYS_COLLIDER_DEF = "Collider";

		static inline const string AASTATS_INDEX		= "Index";
		static inline const string GAMEEFF_CATALOGID	= "GameEff_CatalogID";
		static inline const string GAMEEFF_SUBCATALOGID = "GameEff_SubCatalogID";
	};
}