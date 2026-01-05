
#include <GameEffectsSystem.h>

using namespace KrostganEngine::GameObjects;

ComposeGameEff_Permanent::ComposeGameEff_Permanent() {

}
ComposeGameEff_Permanent::ComposeGameEff_Permanent(const ComposeGameEff_Permanent& copy)
	:ComposeGameEff_Durable(copy){

}
ComposeGameEff_Permanent::~ComposeGameEff_Permanent() {

}
ComposeGameEffect& ComposeGameEff_Permanent::Clone() const {
	return *new ComposeGameEff_Permanent(*this);
}