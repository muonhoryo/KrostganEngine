
#include <Entity.h>
#include <Engine.h>

using namespace KrostganEngine::Core;
using namespace KrostganEngine::GameObjects;

Entity::StealthStatChangedSubs::StealthStatChangedSubs(Entity& Owner)
	:Owner(Owner) {

	new DelayedInit(*this);
}

void Entity::StealthStatChangedSubs::Execute(int& args) {
	ExecuteAction(args);
}

void Entity::StealthStatChangedSubs::ExecuteAction(int args) {

	if (FractionsSystem::GetRelationToPlayer(Owner.GetFraction()) != Relation::Ally &&
		args == (int)EntityBattleStatType::Stealth) {

		if (Owner.StlHider == nullptr) {

			if (Owner.GetBattleStats().GetStealth() > eps) {
				Owner.StlHider = new OnStealthGraphHider(Owner);
			}
		}
		else {

			if (Owner.GetBattleStats().GetStealth() <= eps) {
				delete Owner.StlHider;
				Owner.StlHider = nullptr;
			}
		}
	}
}
