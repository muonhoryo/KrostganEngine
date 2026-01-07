
#include <HeroObject.h>
#include <Engine.h>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <UnitObject.h>

#include <GeneralGameEffects.h>

using namespace sf;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::EntitiesControl;

HeroObject::HeroObject(HeroObjectCtorParams& params) 
	:UnitObject(params){


	ComposeGameEff_Permanent& gameEff = *new ComposeGameEff_Permanent();
	gameEff.AddGameEffect_Durable(*new GameEff_Dur_EntBatStatMult(EntityBattleStatType::MovingSpeed, 2));
	TestAura = new Aura(300, GetFraction(), Relation::Ally, gameEff, *this);
	TestAura->SetGlobalPosition(GetGlobalPosition());
	TestAura->CreateToFracMemDependency(*this);
}
HeroObject::~HeroObject(){}