#pragma once

#include <rapidxml.hpp>
#include <CoreVisual_UI.h>
#include <UserInterfacesDeserializer.h>

using namespace rapidxml;
using namespace KrostganEngine::UI;
using namespace KrostganEngine::Core;

namespace KrostganEngine::Core {
	class UserInterfaceLoader {
		
	public:
		static void Load(const xml_document<>& layout) {

			UIEmpty& root = UserInterfaceManager::GetRoot();
			root.DestroyChildren();
			DeserializeNode(layout.first_node()->first_node(), root);
		}
		static void Load(const string& layoutName) {
			Load(UserInterfacesDeserializer::GetInstance()->GetLayout(layoutName));
		}
		static void UnloadCurrent() {
			UserInterfaceManager::GetRoot().DestroyChildren();
		}

	private:
		UserInterfaceLoader(){}

		static void DeserializeNode(xml_node<>* node, UIElement& parent);
		

		static inline const string UI_LAYOUT_MAINMENU		= "MainMenu";
		static inline const string UI_LAYOUT_LEVELDESER		= "LevelDeserialization";
		static inline const string UI_LAYOUT_LOSEMSG		= "LoseMsg";
		static inline const string UI_LAYOUT_WINMSG			= "WinMsg";
		static inline const string UI_LAYOUT_GAMEUI			= "GameUI";

		static inline const string UIEL_NAME_TEXT			= "TextBlock";

		static inline const string ATTR_POSITION_X			= "PosX";
		static inline const string ATTR_POSITION_Y			= "PosY";
		static inline const string ATTR_SCALE_X				= "ScaleX";
		static inline const string ATTR_SCALE_Y				= "ScaleY";
		static inline const string ATTR_ANCHOR_X			= "AnchorX";
		static inline const string ATTR_ANCHOR_Y			= "AnchorY";
		static inline const string ATTR_LAYER				= "Layer";
		static inline const string ATTR_ACTIVE				= "Active";
		static inline const string ATTR_COLOR = "Color";
		static inline const string ATTR_TEXT_TEXT = "Text";
		static inline const string ATTR_TEXT_FONTSIZE = "FontSize";
		static inline const string ATTR_TEXT_FONT = "Font";

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