#pragma once

#include <IAttackableObj.h>
#include <ICallbackRec_LUpd.h>
#include <ICallbackRec_Upd.h>
#include <AutoAttackAnimation.h>
#include <AutoAttackStats.h>
#include <forward_list>
#include <CatalogObject.h>
#include <CachedBattleStats.h>
#include <PhysicsLayer.h>

using namespace std;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::Visual;
using namespace KrostganEngine::Physics;

namespace KrostganEngine::GameObjects {
	class AutoAttackModule;

	struct AAProjectileCtorParams {

		AAProjectileCtorParams(AutoAttackModule& Owner);

		AutoAttackModule& Owner;
		float									Speed = 1;
		bool									LockRotation = true;
		Vector2f								GlobalPosition = DEFAULT_POSITION;
		float									GlobalScale = DEFAULT_SCALE_SNG;
		size_t									CatalogID = 0;
		std::byte								SubcatalogID = (std::byte)0;
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
		AutoAttackStats& AAStats;

		shared_ptr<CachedBattleStats
			<AutoAttackStats_Consts::FIELDS_COUNT_S_T,
			AutoAttackStats_Consts::FIELDS_COUNT_F,
			AutoAttackStats_Consts::FIELDS_COUNT_BOOL,
			LvlObjInstantiationInfo>>					CachedAAStats = nullptr;

		/// <summary>
		/// Return false if projectile should be destroyed immidietly cause target is unreachable.
		/// </summary>
		/// <returns></returns>
		virtual bool CheckTargetReachability() const = 0;
		virtual Vector2f GetTargetPosition() const = 0;
		virtual void CollideWithTarget() = 0;
		virtual const AttackHitInfo& GetAttInfo_FromOwn(IAttackableObj& target) const;
		virtual const AttackHitInfo& GetAttInfo_FromCache(IAttackableObj& target) const;

		const AttackHitInfo& GetAttInfo(IAttackableObj& target) const;
		bool GetState_IsValidAAStatsRef() const;
		void DealDmgToSingleTarget(IAttackableObj& target) const;
		void DealDmgByAOE(Vector2f center) const;

	private:
		bool IsValidAAStatsRef = true;

		void OnDestroy();

		friend class AutoAttackModule;

	public:
		static inline const PhysicsLayer AA_PROJS_COLLISION_LAYER = (PhysicsLayer)
				((size_t)PhysicsLayer::Decorations |
				(size_t)PhysicsLayer::Buildings |
				(size_t)PhysicsLayer::Units);
	};

	class AutoAttackModule: public ICallbackRec_Upd {
	public:
		virtual ~AutoAttackModule();
		AutoAttackModule(AutoAttackAnimation& AAAnimation, AutoAttackStats& OwnerAAStats, ITransformableObj& Owner);

		/// <summary>
		/// If target is nullptr, stops AAModule
		/// </summary>
		/// <param name="target"></param>
		void				SetAsTarget(watch_ptr_handler_wr<IAttackableObj>* target);
		void				SetAAStats(AutoAttackStats& stats);

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
		AutoAttackStats*	GetCurrAAStats() const { return OwnerAAStats; }

		IAttackableObj* GetCurrentTarget();

		float GetRemReloadTime() const;

		void Update(CallbackRecArgs_Upd args) override;

		ExecutedEvent<AutoAttackStats*> ChangeAutoAttackStatsEvent = ExecutedEvent<AutoAttackStats*>();

	private:

		void CreateProjectile();
		/// <summary>
		/// Set RemReloadTime to infinity if AASpeed is near zero 
		/// or else set RemReloadTime to AACooldown.
		/// 
		/// Return true if RemReloadTime isn't equal infinity.
		/// </summary>
		bool UpdateByAASpeed();
		void CacheAAStats();

		EventHandler<AutoAttackStats*> ChangedAAStatsEventHan = EventHandler<AutoAttackStats*>(ChangeAutoAttackStatsEvent);

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

		void OnDestroyProjectile(AutoAttackProjectile& proj);

		friend void AutoAttackProjectile::OnDestroy();
	};


}