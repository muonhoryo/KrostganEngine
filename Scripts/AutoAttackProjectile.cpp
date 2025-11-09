
#include <AutoAttackModule.h>
#include <VectExts.h>
#include <AutoAttackHitInfo.h>
#include <ProjAAHitInfo.h>

using namespace KrostganEngine;
using namespace KrostganEngine::GameObjects;

AAProjectileCtorParams::AAProjectileCtorParams(AutoAttackModule& Owner, watch_ptr_handler_wr<IAttackableObj> Target)
	:Owner(Owner),
	Target(Target){

	Speed = Owner.GetAAStats()->GetAAProjSpeed();
	LockRotation = Owner.GetAAStats()->GetState_Proj_LockRotation();
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
	Target(Params.Target),
	Speed(Params.Speed),
	LockRotation(Params.LockRotation)
{
	SetGlobalPosition(Params.GlobalPosition);
	SetGlobalScale_Sng(Params.GlobalScale);
}

AutoAttackProjectile::~AutoAttackProjectile() {

	if (IsValidOwnerRef)
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

	Vector2f delta = Target.GetPtr_t_c()->GetGlobalPosition()-GetGlobalPosition();
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
bool AutoAttackProjectile::CheckTargetReachability() const {
	return Target.GetPtr_t_c() != nullptr;
}
void AutoAttackProjectile::CollideWithTarget() {
	
	const AttackHitInfo& info = IsValidOwnerRef? GetAttInfo_FromOwn() : GetAttInfo_FromCache();
	Target.GetPtr_t()->GetHPModule().TakeDamage(info);
	delete this;
}
const AttackHitInfo& AutoAttackProjectile::GetAttInfo_FromOwn() const {
	auto stats = Owner.GetAAStats();
	IFractionMember* parOwner = dynamic_cast<IFractionMember*>(&Owner);
	Fraction frac = parOwner == nullptr ? Fraction::Neutral : parOwner->GetFraction();
	return *new AutoAttackHitInfo(stats->GetAADamage(), Target, *stats,frac);
}
const AttackHitInfo& AutoAttackProjectile::GetAttInfo_FromCache() const {

	int index = AutoAttackStats::GetArrayIndexOfField((int)AutoAttackStats_Consts::StatType::AADamage);
	size_t dmg = CachedAAStats->GetPtr_t_c()->Params_s_t[index];
	Fraction frac = Fraction::Neutral;
	return *new ProjAAHitInfo(dmg, Target, *CachedAAStats->GetPtr_t_c(),frac);
}
void AutoAttackProjectile::OnDestroy() {
	if (IsValidOwnerRef)
		Owner.OnDestroyProjectile(*this);
}