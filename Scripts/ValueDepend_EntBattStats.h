#pragma once

#include <EntityBattleStats.h>
#include <IEntityUIDependency.h>

using namespace KrostganEngine;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::GameObjects;

namespace KrostganEngine::UI {

	template<typename TObjValue>
	class BattleStatDepend_toTxt final : public ValueDependency_toTxt<TObjValue>, public IEntityUIDependency {

		template <typename TObjValue>
		class OnStatsUpdate;

	public:
		const EntityBattleStats::StatType SubjStat;
	private:
		watch_ptr_handler_wr<Entity>* Target = nullptr;
		OnStatsUpdate<TObjValue>* StatUpdateSubs;

		template<typename TObj>
		struct OnStatsUpdate final : public IEventSubscriber<EntityBattleStats::StatType> {

			OnStatsUpdate(BattleStatDepend_toTxt<TObj>& Owner)
				:Owner(Owner)
			{}

			BattleStatDepend_toTxt<TObj>& Owner;

			void Execute(const EntityBattleStats::StatType& args) override {
				if (args == Owner.SubjStat)
					Owner.Update();
			}

		};
		TObjValue& GetObjectRefForNewTar(Entity& newTar) {
			size_t objRef = (size_t)(this->Object);
			size_t oldTarRef = (size_t)(&Target->GetPtr_t_c()->GetBattleStats());
			size_t newTarRef = (size_t)(&newTar.GetBattleStats());
			return *(TObjValue*)(objRef - oldTarRef + newTarRef);
		}
		/*TObjValue& ctor_GetObject(BattleStatDepend_toTxt& toCopy) {

			if (!IsValueRefValid() || !toCopy.IsValueRefValid())
				throw exception("Can't read memory to get object's reference");

			size_t objRef = (size_t)(&toCopy.Object);
			size_t oldTarRef = (size_t)(&toCopy.Target->GetPtr_t_c()->GetBattleStats());
			size_t newTarRef = (size_t)(Target->GetPtr_t_c()->GetBattleStats());
			return *(float*)(objRef - oldTarRef + newTarRef);
		}*/

	public:
		virtual ~BattleStatDepend_toTxt() {

			delete StatUpdateSubs;
		}
		BattleStatDepend_toTxt
			(watch_ptr_handler_wr<Entity>* Target, 
			EntityBattleStats::StatType SubjStat, 
			UIText& Subject, 
			TObjValue const* Object,
			const string& Format="{}")
				:ValueDependency_toTxt<TObjValue>(Subject, Object,Format),
				Target(Target),
				SubjStat(SubjStat) {

			StatUpdateSubs = new OnStatsUpdate<TObjValue>(*this);
			if (Target != nullptr)
				ChangeDepTarget(Target->GetPtr_t());
			else
				ChangeDepTarget(nullptr);
		}
		/*/// <summary>
		/// Copy another dependency with different owner.
		/// </summary>
		/// <param name="Owner"></param>
		/// <param name="toCopy"></param>
		BattleStatDepend_toTxt(watch_ptr_handler_wr_c<Entity>* Target, BattleStatDepend_toTxt& toCopy)
			:BattleStatDepend_toTxt(Target, toCopy.SubjStat, toCopy.Subject, ctor_GetObject(toCopy))
		{}*/

		void ChangeDepTarget(Entity* target) override {
			if (IsValueRefValid()) {
				auto tarRef = Target->GetPtr_t_c();
				if (tarRef != nullptr)
					tarRef->GetBattleStats().StatChangedEvent.Remove((IEventSubscriber<EntityBattleStats::StatType>&)*StatUpdateSubs);
			}
			else {
				this->Object = nullptr;
			}
			if (target != nullptr) {
				target->GetBattleStats().StatChangedEvent.Add((IEventSubscriber<EntityBattleStats::StatType>&)*StatUpdateSubs);
				auto& ptr = target->GetPtr();
				if (this->Object == nullptr)
					this->Object = reinterpret_cast<TObjValue const*>(target->GetBattleStats().GetFieldRef(SubjStat));
				else
					this->Object = &this->GetObjectRefForNewTar(*target);
				delete Target;
				Target = new watch_ptr_handler_wr<Entity>(ptr);
				delete& ptr;
				this->SetByObject();
			}
			else {
				delete Target;
				Target = nullptr;
				this->SetDefault();
			}
		}
		
	protected:
		bool IsValueRefValid() const override {
			return Target != nullptr && Target->GetPtr_t_c() != nullptr;
		}
	};

	typedef BattleStatDepend_toTxt<float> BattleStatDepend_toTxt_f;
	typedef BattleStatDepend_toTxt<size_t> BattleStatDepend_toTxt_s_t;
}