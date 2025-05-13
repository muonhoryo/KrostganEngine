#pragma once

#include <FractionsSystem.h>

namespace KrostganEngine::EntitiesControl {
	class IFractionMember {
	public:
		virtual Fraction GetFraction()const=0;

	protected:
		IFractionMember(){}
	};
}