
#include <AutoAttackModule.h>
#include <VectExts.h>
#include <Engine.h>
#include <ProjAAHitInfo.h>
#include <GameVisualEffects.h>
#include <ObjectsCatalog.h>

using namespace KrostganEngine;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::Visual;

AAProjectileCtorParams::AAProjectileCtorParams(AutoAttackModule& Owner)
	:Owner(Owner){

	Speed = Owner.GetCurrAAStats()->GetProjSpeed();
	LockRotation = Owner.GetCurrAAStats()->GetState_Proj_LockRotation();
}

//
//
//AutoAttackModule
//
//

AutoAttackProjectile::AutoAttackProjectile(const AAProjectileCtorParams& Params) 
	:WorldTransfObj(*new Transformable()),
	CatalogObject(Params.CatalogID,Params.SubcatalogID),
	Owner(Params.Owner),
	AAStats(*Owner.GetCurrAAStats()),
	Speed(Params.Speed),
	LockRotation(Params.LockRotation)
{
	SetGlobalPosition(Params.GlobalPosition);
	SetGlobalScale_Sng(Params.GlobalScale);
}

AutoAttackProjectile::~AutoAttackProjectile() {

	if (IsValidAAStatsRef)
		OnDestroy();
}

void AutoAttackProjectile::SetParent(IHierarchyTrObj* parent) {
	return;
}

void AutoAttackProjectile::Update(CallbackRecArgs_LUpd args) {

	if (!CheckTargetReachability()) {
		delete this;
		return;
	}

	Vector2f delta =GetTargetPosition()-GetGlobalPosition();
	Vector2 dir = Normalize(delta);
	float sqDist = SquareLength(delta);
	float sqSpeed = Speed * Speed;
	
	if (sqDist<=sqSpeed) {
		CollideWithTarget();
	}
	else {
		Move_Global(dir * Speed);
		if (!LockRotation)
			SetGlobalRotation(DirectionToAngle(dir));
	}
}
const AttackHitInfo& AutoAttackProjectile::GetAttInfo(IAttackableObj& target) const {

	return GetState_IsValidAAStatsRef() ? GetAttInfo_FromOwn(target) : GetAttInfo_FromCache(target);
}

const AttackHitInfo& AutoAttackProjectile::GetAttInfo_FromOwn(IAttackableObj& target) const {

	IFractionMember* parOwner = dynamic_cast<IFractionMember*>(&Owner);
	Fraction frac = parOwner == nullptr ? Fraction::Neutral : parOwner->GetFraction();
	return *new AutoAttackHitInfo(AAStats.GetDamage(), target.GetPtr(), AAStats, frac);
}
const AttackHitInfo& AutoAttackProjectile::GetAttInfo_FromCache(IAttackableObj& target) const {

	int index = AutoAttackStats::GetArrayIndexOfField((int)AutoAttackStats_Consts::StatType::Damage);
	size_t dmg = CachedAAStats.get()->Params_s_t[index];
	Fraction frac = Fraction::Neutral;
	return *new ProjAAHitInfo(dmg, target.GetPtr(), *CachedAAStats.get(), frac);
}

void AutoAttackProjectile::OnDestroy() {
	if (IsValidAAStatsRef)
		Owner.OnDestroyProjectile(*this);
}
bool AutoAttackProjectile::GetState_IsValidAAStatsRef() const {
	return IsValidAAStatsRef;
}
void AutoAttackProjectile::DealDmgToSingleTarget(IAttackableObj& target) const {

	const AttackHitInfo& info = GetAttInfo(target);
	target.GetHPModule().TakeDamage(info);
	delete& info;
}
void AutoAttackProjectile::DealDmgByAOE(Vector2f center) const {
	float range;
	const LvlObjInstantiationInfo* hitEff = nullptr;
	bool isValidOwner = GetState_IsValidAAStatsRef();
	if (isValidOwner) {

		range = Owner.GetCurrAAStats()->GetSiegeRange().Stat;
		hitEff = &Owner.GetCurrAAStats()->GetSiegeHitEffInfo();
	}
	else {
		size_t index = AutoAttackStats::GetArrayIndexOfField((int)AAStatType::SiegeRange);
		range = CachedAAStats.get()->Params_f[index];
		hitEff = &CachedAAStats.get()->AdditionalParams;
	}
	auto tars = Engine::GetPhysicsEngine().OverlapCircle_All(center, range, AA_PROJS_COLLISION_LAYER);
	const AttackHitInfo* info = nullptr;
	IAttackableObj* partar = nullptr;
	for (auto target : tars) {
		partar = dynamic_cast<IAttackableObj*>(target);
		if (partar != nullptr) {
			info = &(isValidOwner ? GetAttInfo_FromOwn(*partar) : GetAttInfo_FromCache(*partar));
			partar->GetHPModule().TakeDamage(*info);
		}
	}

	if (hitEff->CatalogID != ObjectsCatalog::EMPTY_CATALOG_ID) {

		auto hitEffObj = dynamic_cast<SpriteRenderer*>(hitEff->InstantiateObj());
		hitEffObj->SetGlobalPosition(center);
		hitEffObj->SetScaleByPixelSize_Global(range*2);
		auto& eff = *new TransparencyVisEff_Des(
			TransparencyVisEff::GetEffectType(TransparencyEffectType::Fading, TransparencyEffectType::Linear),
			Engine::GetGlobalConsts().AverageLifeTime_DeathEffect, 
			*hitEffObj);
		hitEffObj->AddEffect(eff);
	}
}