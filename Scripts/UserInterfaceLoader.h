#pragma once

#include <rapidxml.hpp>
#include <ValueDependency.h>

using namespace rapidxml;
using namespace KrostganEngine::UI;

namespace KrostganEngine::Core {
	class UserInterfaceLoader {
		
	public:
		static void Load(const xml_document<>& layout);
		static void Load(const string& layoutName);
		static void UnloadCurrent();

	private:
		UserInterfaceLoader(){}

		enum class DependStatsWrapperType {

			ABSENT,
			Base,
			AutoAttack
		};

		template<typename TInput>
		struct Predicate {
			virtual bool Condition(TInput input) const = 0;
		};

		struct GetDependByTypePred : public CollectionsExts::Predicate<IUIDependency* const&> {

			GetDependByTypePred(const type_info& info)
				:type(info)
			{}
			bool Condition(IUIDependency* const& input) const override {
				return typeid(input) == type;
			}

			const type_info& type;
		};

		static void DeserializeNode(xml_node<>* node, UIElement& parent);
		static IUIDependency* GetDependencyByType(forward_list<IUIDependency*>& list, const type_info& typeInfo);
		

		static inline const string UI_LAYOUT_MAINMENU		= "MainMenu";
		static inline const string UI_LAYOUT_LEVELDESER		= "LevelDeserialization";
		static inline const string UI_LAYOUT_LOSEMSG		= "LoseMsg";
		static inline const string UI_LAYOUT_WINMSG			= "WinMsg";
		static inline const string UI_LAYOUT_GAMEUI			= "GameUI";

		static inline const string UIEL_NAME_EMPTY			= "Empty";
		static inline const string UIEL_NAME_TEXT			= "TextBlock";
		static inline const string UIEL_NAME_SPRITE			= "Sprite";

		static inline const string ATTR_POSITION_X			= "PosX";
		static inline const string ATTR_POSITION_Y			= "PosY";
		static inline const string ATTR_SCALE_X				= "ScaleX";
		static inline const string ATTR_SCALE_Y				= "ScaleY";
		static inline const string ATTR_ANCHOR_X			= "AnchorX";
		static inline const string ATTR_ANCHOR_Y			= "AnchorY";
		static inline const string ATTR_ORIGIN_X			= "OriginX";
		static inline const string ATTR_ORIGIN_Y			= "OriginY";
		static inline const string ATTR_LAYER				= "Layer";
		static inline const string ATTR_ACTIVE				= "Active";
		static inline const string ATTR_COLOR				= "Color";
		static inline const string ATTR_RESIZEINHERIT_UI	= "ResizeInherit_UI";
		static inline const string ATTR_SHADER				= "Shader";
		static inline const string ATTR_NAME				= "Name";
		static inline const string ATTR_UISIZE_X			= "UISizeX";
		static inline const string ATTR_UISIZE_Y			= "UISizeY";

		static inline const string ATTR_SPRITE_SOURCE		= "Source";

		static inline const string ATTR_TEXT_TEXT			= "Text";
		static inline const string ATTR_TEXT_FONTSIZE		= "FontSize";
		static inline const string ATTR_TEXT_FONT			= "Font";

		static inline const string ATTR_TAG_DEPEND_HIEACT_GRS		= "HieAct_GroupSelDepend";
		static inline const string ATTR_TAG_DEPEND_HIEACT_ABLE2AA	= "HieAct_AAActivityDepend";
		static inline const string ATTR_TAG_DEPEND_FIRST_SEL_ENTITY = "FirstSelEnt_Depend";

		static inline const string ATTR_DEPEND_HIEACT_GRS_THRESHOLD	= "HieAct_GroupSelDepend_Threshold";
		static inline const string ATTR_DEPEND_HIEACT_GRS_GREAT		= "HieAct_GroupSelDepend_IsGreaterToAct";
		static inline const string ATTR_DEPEND_HIEACT_GRS_EQUAL		= "HieAct_GroupSelDepend_IsEqualToAct";

		static inline const string ATTR_DEPEND_TXT_BATSTAT_FIELDTYPE	= "TextDepend_BatStats_FieldType";
		static inline const string ATTR_TAG_DEPEND_TXT_CURRHP			= "TextDepend_CurrentHP";

		static inline const string ATTR_DEPEND_STATS_CONTAINER_BASE		= "Base";
		static inline const string ATTR_DEPEND_STATS_CONTAINER_AA		= "AutoAttack";
	public:
		static void Load_MainMenu() {
			Load(UI_LAYOUT_MAINMENU);
		}
		static void Load_LevelDeserialization() {
			Load(UI_LAYOUT_LEVELDESER);
		}
		static void Load_LoseMessage() {
			Load(UI_LAYOUT_LOSEMSG);
		}
		static void Load_WinMessage() {
			Load(UI_LAYOUT_WINMSG);
		}
		static void Load_GameUI() {
			Load(UI_LAYOUT_GAMEUI);
		}
	};
}