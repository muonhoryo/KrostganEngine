#pragma once

#include <SFML/Window.hpp>
#include <string>

using namespace sf;
using namespace std;

namespace KrostganEngine::PlayerControl {

	struct PlayerControlSettings {

		//Window input
		Keyboard::Key Btn_OpenConsole;
		Keyboard::Key Btn_CloseApp;
		Keyboard::Key Btn_FullScreen;

		//Orders
		Keyboard::Key Btn_Order_Attack;
		Keyboard::Key Btn_Order_Idle;
		Keyboard::Key Btn_Order_Cancel;
		Keyboard::Key Btn_Order_HoldPosition;
		Keyboard::Key Btn_Order_UseAbility_1;

		//GroupSelectionSystem
		Keyboard::Key Btn_GSS_ChoiseNext;

		//Camera moving
		float CameraMoveSpeed;
	};

	struct PlayerControlSettingsDefNames {

		static inline const string DEF_BTN_OPENCONSOLE			= "Btn_OpenConsole";
		static inline const string DEF_BTN_CLOSEAPP				= "Btn_CloseApp";
		static inline const string DEF_BTN_FULLSCREEN			= "Btn_Fullscreen";
		static inline const string DEF_BTN_ORDER_ATTACK			= "Btn_Order_Attack";
		static inline const string DEF_BTN_ORDER_IDLE			= "Btn_Order_Idle";
		static inline const string DEF_BTN_ORDER_CANCEL			= "Btn_Order_Cancel";
		static inline const string DEF_BTN_ORDER_HOLDPOS		= "Btn_Order_HoldPosition";
		static inline const string DEF_BTN_ORDER_USEABILITY_1	= "Btn_Order_UseAbility_1";
		static inline const string DEF_GSS_CHOISENEXT			= "Btn_GSS_ChoiseNext";

		static inline const string DEF_CAMERA_MOVESPEED = "CameraMoveSpeed";
	};
}