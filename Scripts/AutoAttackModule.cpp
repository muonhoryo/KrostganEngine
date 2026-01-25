
#include <AutoAttackModule.h>
#include <Engine.h>
#include <VectExts.h>
#include <CachedBattleStats.h>
#include <watch_ptr.h>
#include <WorldTransfObjsCatalog.h>

using namespace KrostganEngine;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::Visual;

AutoAttackModule::AutoAttackModule(AutoAttackAnimation& AAAnimation, AutoAttackStats& OwnerAAStats, ITransformableObj& Owner)
	:ICallbackRec_Upd(),
	AAAnimation(AAAnimation),
	OwnerAAStats(&OwnerAAStats),
	Owner(Owner),
	Target(nullptr)
{
	if (UpdateByAASpeed())
		RemReloadTime = 0;
}
AutoAttackModule::~AutoAttackModule() {
	delete &AAAnimation;
	if (Target != nullptr)
		delete Target;

	CacheAAStats();
}

IAttackableObj* AutoAttackModule::GetCurrentTarget() {
	return Target->GetPtr_t();
}

void AutoAttackModule::SetAsTarget(watch_ptr_handler_wr<IAttackableObj>* target) {

	if (Target != nullptr)
		delete Target;

	if (target != nullptr &&
		target->GetPtr_t() != nullptr) {

		Target = target;
	}
	else
	{
		Target = nullptr;
	}
}
void AutoAttackModule::SetAAStats(AutoAttackStats& stats) {
	
	if (&stats == OwnerAAStats)
		return;
	
	CacheAAStats();
	OwnerAAStats = &stats;
	ChangedAAStatsEventHan.Execute(OwnerAAStats);
}

bool AutoAttackModule::CheckTargetReach() const {

	//Check if target has been deleted
	if (Target == nullptr)
		return false;
	auto ptr = Target->GetPtr_t();
	if (ptr == nullptr)
		return false;
	return CheckTargetReach(*ptr);
}

bool AutoAttackModule::CheckTargetReach(const IAttackableObj& potentTarget) const {

	if (OwnerAAStats == nullptr)
		return false;

	if (!potentTarget.CheckAttackReachability(IAttackableObj::AtkParam::IsAA))
		return false;

	Vector2f pos = Owner.GetGlobalPosition();
	Vector2f closPoint = potentTarget.GetClosestPoint(pos);
	float dist = Length(closPoint - pos);
	return dist - OwnerAAStats->GetRange() <= eps;
}

bool AutoAttackModule::TryDealDamageToTarget() {

	if (CheckTargetReach())
	{
		if (ZeroSpeed)
			UpdateByAASpeed();
		else if (RemReloadTime <= 0) {

			size_t dealedDmg = OwnerAAStats->GetDamage();
			if (OwnerAAStats->GetState_IsRange() &&	
				OwnerAAStats->GetProjectileInfo().CatalogID!=EMPTY_CATALOG_ID) {

				CreateProjectile();
			}
			else {

				IFractionMember* parOwner = dynamic_cast<IFractionMember*>(&Owner);
				Fraction frac = parOwner == nullptr ? Fraction::Neutral : parOwner->GetFraction();
				AutoAttackHitInfo attInfo = AutoAttackHitInfo(dealedDmg, watch_ptr_handler_wr<IAttackableObj>(*Target), *OwnerAAStats,frac);
				Target->GetPtr_t()->GetHPModule().TakeDamage(attInfo);
				AAAnimation.OnTakeDmg(attInfo);
			}

			if (!UpdateByAASpeed())
				return true;

			RemReloadTime = OwnerAAStats->GetCooldown();
			return true;
		}
	}
	return false;
}

float AutoAttackModule::GetRemReloadTime() const {
	return RemReloadTime;
}

void AutoAttackModule::Update(CallbackRecArgs_Upd args) {
	
		if (RemReloadTime > 0)
			RemReloadTime -= args.LastFrameDeltaTime;
}

bool AutoAttackModule::UpdateByAASpeed() {
	
	if (OwnerAAStats == nullptr || OwnerAAStats->GetSpeed() < eps) {

		RemReloadTime = FLT_MAX;
		ZeroSpeed = true;
		return false;
	}
	else {

		RemReloadTime = OwnerAAStats->GetCooldown();
		ZeroSpeed = false;
		return true;
	}
}

void AutoAttackModule::CacheAAStats() {

	if (CreatedProjectiles.begin() != CreatedProjectiles.end()) {

		auto stats = new CachedBattleStats
		(OwnerAAStats->GetParamsArray_s_t(),
			OwnerAAStats->GetParamsArray_f(),
			OwnerAAStats->GetParamsArray_bool(),
			OwnerAAStats->GetSiegeHitEffInfo());
		auto ptr = shared_ptr<CachedBattleStats
			<AAStatsConsts::FIELDS_COUNT_S_T,
			AAStatsConsts::FIELDS_COUNT_F,
			AAStatsConsts::FIELDS_COUNT_BOOL,
			LvlObjInstantiationInfo>>(stats);
		for (auto proj : CreatedProjectiles) {
			proj->IsValidAAStatsRef = false;
			proj->CachedAAStats = ptr;
		}
		CreatedProjectiles.clear();
	}
}

void AutoAttackModule::CreateProjectile() {
	
	auto& projInfo = OwnerAAStats->GetProjectileInfo();
	WorldObjectLoadInfo* projObjInfo = nullptr;
	if (projInfo.CatalogSubID != ABSENT_SUB_CATALOG_ID)
		projObjInfo = WorldTransfObjsCatalog::GetSubObjInfo(projInfo.CatalogID, projInfo.CatalogSubID);
	else
		projObjInfo = &WorldTransfObjsCatalog::GetObjectInfo(projInfo.CatalogID);
	AAProjectileLoadInfo* parProjInfo = dynamic_cast<AAProjectileLoadInfo*>(projObjInfo);
	auto& proj= parProjInfo->InstantiateProjectile
		(*this,
		*Target->GetPtr_t(),
				projInfo.AdditParams != nullptr && projInfo.AdditParams->Attrs.size() != 0 ?
				projInfo.AdditParams :
				nullptr);
	proj.SetGlobalPosition(Owner.GetGlobalPosition());
	AutoAttackProjectile& parproj = *dynamic_cast<AutoAttackProjectile*>(&proj);
	CreatedProjectiles.push_front(&parproj);
}

void AutoAttackModule::OnDestroyProjectile(AutoAttackProjectile& proj) {
	CollectionsExts::Remove(CreatedProjectiles, &proj);
}