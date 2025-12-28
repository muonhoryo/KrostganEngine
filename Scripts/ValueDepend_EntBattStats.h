#pragma once

#include <StatsWrapperDepend_toTxt.h>
#include <IEntityUIDependency.h>
#include <MemoryExts.h>
#include <GetEntStatsWrapperFunc.h>

using namespace KrostganEngine;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::GameObjects;

namespace KrostganEngine::UI {


	template<typename TObjValue>
	class BattleStatDepend_toTxt final : protected StatsWrapperDepend_toTxt<TObjValue>, public IEntityUIDependency {

	public:
		using StatsWrapperDepend_toTxt<TObjValue>::SubjStatType;

	private:
		const GetEntStatsWrapperFunc& GetStatsFunc;

	public:
		virtual ~BattleStatDepend_toTxt(){}
		BattleStatDepend_toTxt
			(Entity* entity,
			const GetEntStatsWrapperFunc& GetStatsFunc,
			int SubjStatType,
			UIText& Subject,
			TObjValue const* Object,
			const string& Format = "{}")
				:GetStatsFunc(GetStatsFunc),
				StatsWrapperDepend_toTxt<TObjValue>
					(entity==nullptr? nullptr : &entity->GetPtr_c(),
					GetStatsFunc.GetStatsWrapper(entity),
					SubjStatType,
					Subject,
					Object,
					Format){}

		void ChangeDepTarget(Entity* entity) override {

			if (entity == nullptr) {
				StatsWrapperDepend_toTxt<TObjValue>::ChangeDepTarget(nullptr, nullptr);
			}
			else {

				StatsWrapperDepend_toTxt<TObjValue>::ChangeDepTarget(&entity->GetPtr_c(),
					GetStatsFunc.GetStatsWrapper(entity));
			}

		}
		
	};

	typedef BattleStatDepend_toTxt<float> BattleStatDepend_toTxt_f;
	typedef BattleStatDepend_toTxt<size_t> BattleStatDepend_toTxt_s_t;
}