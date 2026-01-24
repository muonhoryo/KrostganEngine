
#include <PlayerControlSettsLoad.h>

using namespace KrostganEngine::Core;

PlayerControlSettsLoad::PlayerControlSettsLoad()
	:LoadedPlayerCtrlSetts(*new PlayerControlSettings()){

}
PlayerControlSettsLoad::~PlayerControlSettsLoad() {

}

PlayerControlSettings& PlayerControlSettsLoad::LoadPlayerCtrlSettings() {
	DeserializeValues();

	string buffer=string();

	LoadedPlayerCtrlSetts.Btn_OpenConsole  = (Keyboard::Key)DeserValueByDef_int(PlayerControlSettingsDefNames::DEF_BTN_OPENCONSOLE, buffer);
	LoadedPlayerCtrlSetts.Btn_CloseApp = (Keyboard::Key)DeserValueByDef_int(PlayerControlSettingsDefNames::DEF_BTN_CLOSEAPP, buffer);
	LoadedPlayerCtrlSetts.Btn_FullScreen = (Keyboard::Key)DeserValueByDef_int(PlayerControlSettingsDefNames::DEF_BTN_FULLSCREEN, buffer);
	LoadedPlayerCtrlSetts.Btn_Order_Attack= (Keyboard::Key)DeserValueByDef_int(PlayerControlSettingsDefNames::DEF_BTN_ORDER_ATTACK, buffer);
	LoadedPlayerCtrlSetts.Btn_Order_Idle = (Keyboard::Key)DeserValueByDef_int(PlayerControlSettingsDefNames::DEF_BTN_ORDER_IDLE, buffer);
	LoadedPlayerCtrlSetts.Btn_Order_Cancel = (Keyboard::Key)DeserValueByDef_int(PlayerControlSettingsDefNames::DEF_BTN_ORDER_CANCEL, buffer);
	LoadedPlayerCtrlSetts.Btn_Order_HoldPosition = (Keyboard::Key)DeserValueByDef_int(PlayerControlSettingsDefNames::DEF_BTN_ORDER_HOLDPOS, buffer);
	LoadedPlayerCtrlSetts.Btn_Order_UseAbility_1 = (Keyboard::Key)DeserValueByDef_int(PlayerControlSettingsDefNames::DEF_BTN_ORDER_USEABILITY_1, buffer);
	LoadedPlayerCtrlSetts.Btn_GSS_ChoiseNext = (Keyboard::Key)DeserValueByDef_int(PlayerControlSettingsDefNames::DEF_GSS_CHOISENEXT, buffer);

	LoadedPlayerCtrlSetts.CameraMoveSpeed = DeserValueByDef_float(PlayerControlSettingsDefNames::DEF_CAMERA_MOVESPEED, buffer);

	return LoadedPlayerCtrlSetts;
}