#pragma once

#include <IAttackableObj.h>
#include <ICallbackRec_LUpd.h>
#include <ICallbackRec_Upd.h>
#include <AutoAttackAnimation.h>
#include <AutoAttackStats.h>
#include <forward_list>
#include <CatalogObject.h>
#include <CachedBattleStats.h>

using namespace std;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::Visual;

namespace KrostganEngine::GameObjects {
	class AutoAttackModule;

	struct AAProjectileCtorParams {

		AAProjectileCtorParams(AutoAttackModule& Owner, watch_ptr_handler_wr<IAttackableObj> Target);

		AutoAttackModule& Owner;
		watch_ptr_handler_wr<IAttackableObj>	Target;
		float									Speed = 1;
		bool									LockRotation = true;
		Vector2f								GlobalPosition = DEFAULT_POSITION;
		float									GlobalScale = DEFAULT_SCALE_SNG;
		size_t									CatalogID = 0;
		byte									SubcatalogID = (byte)0;
	};

	class AutoAttackProjectile : public WorldTransfObj, public CatalogObject, public ICallbackRec_LUpd {
	public:
		AutoAttackProjectile(const AAProjectileCtorParams& Params);

		virtual ~AutoAttackProjectile();

		void SetParent(IHierarchyTrObj* parent) override;

		void Update(CallbackRecArgs_LUpd args) override;

		float	Speed;
		bool	LockRotation;

	protected:
		AutoAttackModule& Owner;
		watch_ptr_handler_wr<IAttackableObj> Target;
		watch_ptr_handler_wr_c<CachedBattleStats
			<AutoAttackStats_Consts::FIELDS_COUNT_S_T,
			AutoAttackStats_Consts::FIELDS_COUNT_F,
			AutoAttackStats_Consts::FIELDS_COUNT_BOOL>>*CachedAAStats = nullptr;

		/// <summary>
		/// Return false if projectile should be destroyed immidietly cause target is unreachable.
		/// </summary>
		/// <returns></returns>
		virtual bool CheckTargetReachability() const;
		virtual void CollideWithTarget();
		virtual const AttackHitInfo& GetAttInfo_FromOwn() const;
		virtual const AttackHitInfo& GetAttInfo_FromCache() const;

	private:
		bool IsValidOwnerRef = true;

		void OnDestroy();

		friend class AutoAttackModule;
	};

	class AutoAttackModule final: public ICallbackRec_Upd {
	public:
		virtual ~AutoAttackModule();
		AutoAttackModule(AutoAttackAnimation& AAAnimation, AutoAttackStats& OwnerAAStats, ITransformableObj& Owner);

		/// <summary>
		/// If target is nullptr, stops AAModule
		/// </summary>
		/// <param name="target"></param>
		void				SetAsTarget(watch_ptr_handler_wr<IAttackableObj>* target);
		/// <summary>
		/// Return true if attacked target is in attack range.
		/// </summary>
		/// <returns></returns>
		bool				CheckTargetReach() const;
		/// <summary>
		/// Return true if potential target is in attack range.
		/// </summary>
		/// <returns></returns>
		bool				CheckTargetReach(const IAttackableObj& potentTarget) const;
		bool				TryDealDamageToTarget();
		AutoAttackStats*	GetAAStats() { return OwnerAAStats; }

		IAttackableObj* GetCurrentTarget();

		float GetRemReloadTime() const;

		void Update(CallbackRecArgs_Upd args) override;

	private:

		void CreateProjectile();
		/// <summary>
		/// Set RemReloadTime to infinity if AASpeed is near zero 
		/// or else set RemReloadTime to AACooldown.
		/// 
		/// Return true if RemReloadTime isn't equal infinity.
		/// </summary>
		bool UpdateByAASpeed();

		watch_ptr_handler_wr<IAttackableObj>* Target;
		AutoAttackStats* OwnerAAStats;
		ITransformableObj& Owner;
		/// <summary>
		/// In milliseconds
		/// </summary>
		float RemReloadTime = 0;
		bool ZeroSpeed = false;
		AutoAttackAnimation& AAAnimation;
		forward_list<AutoAttackProjectile*> CreatedProjectiles;

	private:
		void OnDestroyProjectile(AutoAttackProjectile& proj);

		friend void AutoAttackProjectile::OnDestroy();
	};


}