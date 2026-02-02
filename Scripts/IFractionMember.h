#pragma once

#include <FractionsSystem.h>
#include <_Events.h>

namespace KrostganEngine::EntitiesControl {

	class IFractionMember {
	public:
		struct ChangeFractionEvArgs final {

			ChangeFractionEvArgs(IFractionMember& Owner, FractionWrapper OldFraction, FractionWrapper NewFraction)
				:Owner(Owner),
				OldFraction(OldFraction),
				NewFraction(NewFraction)
			{}

			IFractionMember& Owner;
			FractionWrapper OldFraction = FractionWrapper();
			FractionWrapper NewFraction = FractionWrapper();
		};

		static inline ExecutedEvent<const ChangeFractionEvArgs> MemberHasChangedFracEvent = ExecutedEvent<const ChangeFractionEvArgs>();

		virtual ~IFractionMember(){}

		virtual FractionWrapper GetFraction()const=0;

		virtual void SetFraction(FractionWrapper fraction) = 0;
		void SetFraction(const Fraction& fraction) {
			SetFraction(FractionWrapper(fraction));
		}

	protected:
		IFractionMember(){}

		static inline EventHandler<const ChangeFractionEvArgs> MemberHasChangedFracEvHandler = EventHandler<const ChangeFractionEvArgs>(MemberHasChangedFracEvent);
	};
}