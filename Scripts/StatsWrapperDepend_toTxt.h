#pragma once

#include <IModifiableStatsWrapper.h>
#include <ValueDependency.h>
#include <MemoryExts.h>

using namespace KrostganEngine;
using namespace KrostganEngine::GameObjects;

namespace KrostganEngine::UI {

	template<typename TObjValue>
	class StatsWrapperDepend_toTxt : public ValueDependency_toTxt<TObjValue> {

		template <typename TObjValue>
		class OnStatsUpdate;

	public:
		const int SubjStatType;
	private:
		watch_ptr_handler_c* NullValidationObj = nullptr;
		IModifiableStatsWrapper* StatsWrapper = nullptr;
		OnStatsUpdate<TObjValue>* StatUpdateSubs;

		template<typename TObj>
		struct OnStatsUpdate final : public IEventSubscriber<int> {

			OnStatsUpdate(StatsWrapperDepend_toTxt<TObj>& Owner)
				:Owner(Owner)
			{}

			StatsWrapperDepend_toTxt<TObj>& Owner;

			void Execute(int& args) override {
				if (args == Owner.SubjStatType)
					Owner.Update();
			}

		};

	public:
		virtual ~StatsWrapperDepend_toTxt() {

			delete StatUpdateSubs;
		}
		StatsWrapperDepend_toTxt
			(watch_ptr_handler_c* NullValidationObj,
			IModifiableStatsWrapper* StatsWrapper,
			int							SubjStatType,
			UIText& Subject,
			TObjValue const* Object,
			const string& Format = "{}")
			:ValueDependency_toTxt<TObjValue>(Subject, Object, Format),
			SubjStatType((int)SubjStatType) {

			StatUpdateSubs = new OnStatsUpdate<TObjValue>(*this);
			if (NullValidationObj != nullptr) {
				ChangeDepTarget(NullValidationObj, StatsWrapper);
			}
			else {
				ChangeDepTarget(nullptr, nullptr);
			}
		}

		void ChangeDepTarget(watch_ptr_handler_c* validObj, IModifiableStatsWrapper* statsWrap) {

			bool isOldTarValid = IsValueRefValid();

			if (isOldTarValid) {
				statsWrap->StatChangedEvent.Remove((IEventSubscriber<int>&) * StatUpdateSubs);
			}
			else {
				this->Object = nullptr;
			}

			if (validObj != nullptr) {
				statsWrap->StatChangedEvent.Add((IEventSubscriber<int>&) * StatUpdateSubs);
				if (this->Object == nullptr)
					this->Object = reinterpret_cast<TObjValue const*>(statsWrap->GetFieldRef(SubjStatType));
				else
					this->Object = &GetSameFieldOfObj<TObjValue, IModifiableStatsWrapper>(*this->Object, *StatsWrapper, *statsWrap);
				if (isOldTarValid)
					delete NullValidationObj;
				NullValidationObj = validObj;
				StatsWrapper = statsWrap;
				this->SetByObject();
			}
			else {

				if (isOldTarValid)
					delete NullValidationObj;
				NullValidationObj = nullptr;
				StatsWrapper = nullptr;
				this->SetDefault();
			}
		}

	protected:
		bool IsValueRefValid() const override {
			return NullValidationObj != nullptr && 
				NullValidationObj->GetPtr_c<void>() != nullptr;
		}
	};

	typedef StatsWrapperDepend_toTxt<float> StatsWrapperDepend_toTxt_f;
	typedef StatsWrapperDepend_toTxt<size_t> StatsWrapperDepend_toTxt_s_t;
}