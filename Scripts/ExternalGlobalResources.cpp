
#include <ExtGlResources.h>

using namespace KrostganEngine::Core;
using namespace sf;

const Font& ExternalGlobalResources::Get_DefaultFont() {
	return GetRes_t<ExtGlRes_Font>(CORE_RES_DEFAULT_FONT)->Font_;
}

const Texture& ExternalGlobalResources::Get_CursorTex_Attack() {
	return GetRes_t<ExtGlRes_Texture>(CORE_RES_CURSORTEX_ATTACK)->Tex;
}
const Texture& ExternalGlobalResources::Get_UnitDeathEffect_Tex() {
	return GetRes_t<ExtGlRes_Texture>(CORE_RES_UNIT_DEATHEFFECT_TEX)->Tex;
}