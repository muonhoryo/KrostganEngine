#pragma once

#include <GameObject.h>
#include <SFML/System.hpp>
#include <Physics.h>
#include <IAttackableObj.h>
#include <DecorationDeathModule.h>
#include <DecorationHPModule.h>
#include<TakeDamageAnim_SprFade.h>

using namespace sf;
using namespace std;
using namespace KrostganEngine::Physics;
using namespace KrostganEngine::Visual;

namespace KrostganEngine::GameObjects {

	struct DecorationCtorParams;

	class DecorationObject :public GameObject, public IAttackableObj{

	public:
		DecorationObject(DecorationCtorParams& params);
		virtual ~DecorationObject();

	//
	// GameObject
	//

		void Update(CallbackRecArgs_LUpd args) override;

		PhysicsLayer GetLayer() const override;

		void SetGlobalPosition(Vector2f position) override;
		void SetGlobalScale(Vector2f scale) override;

	protected:
		const ColliderShape& GetCollider() const override;
		vector<IPhysicalObject*> OverlapAll() const override;
		Vector2f GetResolvingPnt(const ColliderShape& objShape, Vector2f movDir, bool isSlideColl) const override;

	//
	// IAttackableObj
	//

	public:
		IHitPointModule& GetHPModule() const override;
		Vector2f GetClosestPoint(Vector2f dmgDealerPos) const override;

		bool IsTargetableForAA() const override;

		void SetTargetableForAA(bool isTargetable) override;

	//
	// Internal
	//
	private:
		ColliderShape&		Collider;
		IHitPointModule*	HPModule;
		bool				IsTargetableForAutoAttack = true;
		SpriteRenderer*		HitEffectSprite;

		void RecreateCollider(float oldSize, float newSize);
	};

	struct DecorationCtorParams : public GameObjectCtorParams {

		DecorationCtorParams() :GameObjectCtorParams() {}

		size_t CurrentHP =1;
		size_t MaxHP = 1;
		bool IsTargetableForAutoAttack = true;
		SpriteRenderer* HitEffectSprite = nullptr;

		IHitPointModule* GetHPModule() const { return HPModule; }
		IDeathModule* GetDeathModule() const { return DeathModule; }

	protected:
		virtual void InitDeathModule() {
			DeathModule = new DecorationDeathModule(*Owner);
		}
		virtual void InitHPModule() {
			TakeDamageAnim_SprFade& dmgAnim = *new TakeDamageAnim_SprFade(*HitEffectSprite);
			HPModule = new DecorationHPModule(CurrentHP, MaxHP, *DeathModule, dmgAnim);
		}

		IDeathModule* DeathModule = nullptr;
		IHitPointModule* HPModule = nullptr;

		DecorationObject* Owner = nullptr;

		friend class DecorationObject;
	};
}