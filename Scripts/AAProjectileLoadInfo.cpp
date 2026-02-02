
#include <WorldObjectLoadInfo.h>
#include <WorldObjsCatalogSerConsts.h>
#include <_AutoAttackProjectiles.h>

using namespace KrostganEngine::GameObjects;

AAProjectileLoadInfo::AAProjectileLoadInfo(const AAProjectileLoadInfo& copy)
	:WorldObjectLoadInfo(copy) {

	Target = copy.Target;
	Owner = copy.Owner;
}
AutoAttackProjectile& AAProjectileLoadInfo::InstantiateProjectile
(AutoAttackModule& Owner,
	IAttackableObj& Target,
	LvlObjAdditParams* additParams) const {

	this->Owner = &Owner;
	this->Target = &Target;
	auto proj = InstantiateObject(additParams);
	this->Owner = nullptr;
	this->Target = nullptr;
	return *dynamic_cast<AutoAttackProjectile*>(proj);
}
WorldTransfObj* AAProjectileLoadInfo::InstantiateObject_Action(const WorldObjectLoadInfo& usedInfo) const {

	AutoAttackProjectile* proj = nullptr;
	auto aastats = Owner->GetCurrAAStats();
	if (aastats->GetState_IsSiege() && !aastats->GetState_Proj_IsSelfHoming()) {

		AAProjectileCtorParams_NoTar params = AAProjectileCtorParams_NoTar(*Owner, Target->GetGlobalPosition());
		params.CatalogID = CatalogID;
		params.GlobalPosition = Position;
		params.GlobalScale = Size;
		proj = new AAProj_NoTar(params);
	}
	else {
		auto& ptr = Target->GetPtr();
		AAProjectileCtorParams_TarDir params = AAProjectileCtorParams_TarDir(*Owner, ptr);
		params.CatalogID = CatalogID;
		params.GlobalPosition = Position;
		params.GlobalScale = Size;
		proj = new AAProj_TarDir(params);
		delete& ptr;
	}
	return proj;
}
WorldObjectLoadInfo& AAProjectileLoadInfo::Clone() const {
	return *new AAProjectileLoadInfo(*this);
}