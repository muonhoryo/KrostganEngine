#pragma once

#include <Entity.h>
#include <Events.h>

using namespace std;
using namespace KrostganEngine;
using namespace KrostganEngine::GameObjects;

namespace KrostganEngine::Debug {
	/// <summary>
	/// Makes ally army unconquerable
	/// 
	/// -> Deal 10x damage buff to all entities
	/// </summary>
	class DBG_ImmortalArmy final {
	public:
		static void TurnOn();
		static void TurnOff();

		static bool GetActivity() {
			return IsActive;
		}

	private:
		DBG_ImmortalArmy(){}

		struct OnAddEntityAction final : public IEventSubscriber<Entity> {

			void Execute(Entity& args) override;
		};
		struct OnRemoveEntityAction final : public IEventSubscriber<Entity> {
			
			void Execute(Entity& args) override;
		};
		struct OnUnloadEntitiesAction final : public INoArgsEventSubscriber {
			
			void Execute() override;
		};

		struct Immortality final {

			Immortality(const EntityBattleStats::ParamModifier_Mul& DmgBuff, Entity& BuffsOwner)
				:DmgBuff(DmgBuff),
				BuffsOwner(BuffsOwner)
			{}

			bool operator == (Immortality& a) const {
				return &a.BuffsOwner == &BuffsOwner;
			}
			bool operator == (const Immortality& a) const {
				return &a.BuffsOwner == &BuffsOwner;
			}
			Immortality& operator = (const Immortality& a) const {
				return *new Immortality(DmgBuff, BuffsOwner);
			}

			const EntityBattleStats::ParamModifier_Mul& DmgBuff;
			Entity& BuffsOwner;
		};
		struct FindImmByEntPredicate final : public CollectionsExts::Predicate<const Immortality&> {
			
			FindImmByEntPredicate(const Entity& ImmOwner) 
				:ImmOwner(ImmOwner)
			{}
			
			bool Condition(const Immortality& input) const {
				return &input.BuffsOwner == &ImmOwner;
			}

			const Entity& ImmOwner;
		};

		static inline vector<Immortality> Buffs = vector<Immortality>();

		static inline bool IsActive = false;
		static inline OnAddEntityAction& AddAction = *new OnAddEntityAction();
		static inline OnRemoveEntityAction& RemAction = *new OnRemoveEntityAction();
		static inline OnUnloadEntitiesAction& UnloadAction = *new OnUnloadEntitiesAction();

		/// <summary>
		/// Return true if entity could be target of dealed immortality
		/// </summary>
		/// <param name="entity"></param>
		/// <returns></returns>
		static bool CheckImmDealCondition(Entity& entity);
		static void SetImmortality(Entity& entity);
		static void RemoveImmortality(Immortality& immort, bool remFromlist = false);
	};
}