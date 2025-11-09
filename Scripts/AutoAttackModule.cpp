
#include <AutoAttackModule.h>
#include <Engine.h>
#include <VectExts.h>
#include <CachedBattleStats.h>
#include <watch_ptr.h>
#include <ObjectsCatalog.h>

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

	if (CreatedProjectiles.begin() != CreatedProjectiles.end()) {

		auto stats = new CachedBattleStats
			(OwnerAAStats->GetParamsArray_s_t(),
			OwnerAAStats->GetParamsArray_f(),
			OwnerAAStats->GetParamsArray_bool());
		watch_ptr_handler_c* ptr = nullptr;
		for (auto proj : CreatedProjectiles) {
			proj->IsValidOwnerRef = false;
			ptr = &stats->GetPtr_c();
			proj->CachedAAStats = new watch_ptr_handler_wr_c
				<CachedBattleStats
					<AAStatsConsts::FIELDS_COUNT_S_T,
					AAStatsConsts::FIELDS_COUNT_F, 
					AAStatsConsts::FIELDS_COUNT_BOOL>>(*ptr);
			delete ptr;
		}
	}
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

bool AutoAttackModule::CheckTargetReach() const {

	if (Target == nullptr)
		return false;
	auto ptr = Target->GetPtr_t();
	if (ptr == nullptr || ptr->GetHPModule().DeathModule.GetIsDeadState())
		return false;
	return CheckTargetReach(*ptr);
}

bool AutoAttackModule::CheckTargetReach(const IAttackableObj& potentTarget) const {

	Vector2f pos = Owner.GetGlobalPosition();
	Vector2f closPoint = potentTarget.GetClosestPoint(pos);
	float dist = Length(closPoint - pos);
	return dist - OwnerAAStats->GetAARange() <= eps;
}

bool AutoAttackModule::TryDealDamageToTarget() {

	if (CheckTargetReach())
	{
		if (ZeroSpeed)
			UpdateByAASpeed();
		else if (RemReloadTime <= 0) {

			size_t dealedDmg = OwnerAAStats->GetAADamage();
			if (OwnerAAStats->GetState_IsRange() &&	
				OwnerAAStats->GetProjectileInfo().CatalogID!=ObjectsCatalog::EMPTY_CATALOG_ID) {

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

			RemReloadTime = OwnerAAStats->GetAACooldown();
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
	
	if (OwnerAAStats == nullptr || OwnerAAStats->GetAASpeed() < eps) {

		RemReloadTime = FLT_MAX;
		ZeroSpeed = true;
		return false;
	}
	else {

		RemReloadTime = OwnerAAStats->GetAACooldown();
		ZeroSpeed = false;
		return true;
	}
}

void AutoAttackModule::CreateProjectile() {
	
	auto& projInfo = OwnerAAStats->GetProjectileInfo();
	auto projMainInfo = dynamic_cast<const AAProjectileLoadInfo*>(ObjectsCatalog::GetObjectInfo(projInfo.CatalogID));
	auto projSubInfo = ObjectsCatalog::GetSubObjInfo(projInfo.CatalogID, projInfo.CatalogSubID);
	auto& proj= projMainInfo->InstantiateProjectile
		(*this,
		*Target->GetPtr_t(),
			projSubInfo,
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