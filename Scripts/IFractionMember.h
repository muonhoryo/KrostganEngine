#pragma once

#include <FractionsSystem.h>
#include <Events.h>

namespace KrostganEngine::EntitiesControl {

	class IFractionMember {
	public:
		struct ChangeFractionEvArgs final {

			ChangeFractionEvArgs(IFractionMember& Owner, Fraction OldFraction, Fraction NewFraction) 
				:Owner(Owner),
				OldFraction(OldFraction),
				NewFraction(NewFraction)
			{}

			IFractionMember& Owner;
			Fraction OldFraction;
			Fraction NewFraction;
		};

		static inline ExecutedEvent<const ChangeFractionEvArgs> MemberHasChangedFracEvent = ExecutedEvent<const ChangeFractionEvArgs>();

		virtual ~IFractionMember(){}

		virtual Fraction GetFraction()const=0;

		virtual void SetFraction(Fraction fraction) = 0;

	protected:
		IFractionMember(){}

		static inline EventHandler<const ChangeFractionEvArgs> MemberHasChangedFracEvHandler = EventHandler<const ChangeFractionEvArgs>(MemberHasChangedFracEvent);
	};
}