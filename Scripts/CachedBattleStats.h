#pragma once

#include <ModifiableStatsWrapper.h>

using namespace std;

namespace KrostganEngine::GameObjects {
	
	template<size_t FIELDSCOUNT_S_T, size_t FIELDSCOUNT_F, size_t FIELDSCOUNT_BOOL>
	struct CachedBattleStats final : public  w_ptr_observable{

	private:
		template<typename T, size_t ARRAY_SIZE>
		static const array<T, ARRAY_SIZE>& GetValuesFromParams(const array<Parameter<T>, ARRAY_SIZE>& params) {
			auto& arr = *new array<T, ARRAY_SIZE>();
			for (int i = 0;i < ARRAY_SIZE;++i) {
				arr[i] = params[i].Stat;
			}
			return arr;
		}

	public:
		CachedBattleStats
			(const array<Parameter<size_t>, FIELDSCOUNT_S_T>& params_s_t,
			const array<Parameter<float>, FIELDSCOUNT_F>& params_f,
			const array<bool, FIELDSCOUNT_BOOL>& params_bool)
				:Params_s_t(GetValuesFromParams(params_s_t)),
				Params_f(GetValuesFromParams(params_f)),
				Params_bool(*new array<bool, FIELDSCOUNT_BOOL>(params_bool))
		{}
		
		virtual ~CachedBattleStats(){
			delete& Params_s_t;
			delete& Params_f;
			delete& Params_bool;
		}

		const array<size_t, FIELDSCOUNT_S_T>& Params_s_t;
		const array<float, FIELDSCOUNT_F>& Params_f;
		const array<bool, FIELDSCOUNT_BOOL>& Params_bool;
	};
}