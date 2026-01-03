#pragma once

#include <watch_ptr.h>
#include <CollectionsExts.h>

namespace KrostganEngine {

	template <typename TPtrHandlerType>
	struct w_ptr_han_pred_eqByOwners final : public CollectionsExts::EqualCompareFunc<TPtrHandlerType*> {

		w_ptr_han_pred_eqByOwners(){}
		virtual ~w_ptr_han_pred_eqByOwners(){}

		bool Equal(TPtrHandlerType* const& first, TPtrHandlerType* const& second) const override {
			return first->GetPtr_b_c() == second->GetPtr_b_c();
		}
	};
}