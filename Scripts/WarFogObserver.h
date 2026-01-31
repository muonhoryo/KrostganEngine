#pragma once

#include <ITransformableObj.h>
#include <ICallbackRec.h>
#include <IPhysicalObject.h>
#include <IFractionMember.h>

using namespace KrostganEngine::Physics;
using namespace KrostganEngine::EntitiesControl;

namespace KrostganEngine::Core {
	class WarFogObserver : public virtual ITransformableObj, public virtual ICallbackRec, public virtual IFractionMember {

	public:
		virtual ~WarFogObserver();

		virtual float GetObservingRange() const = 0;

		bool GetObservingActivity() const;
		
	protected:
		WarFogObserver(bool isObservingActive=true);

		void SetObservingActive(bool isActive);

		void OnChangeFraction(FractionWrapper frac);

	private:
		/// <summary>
		///	Mark observer as used for warfog's render
		/// </summary>
		void SetActive();
		/// <summary>
		///	Mark observer as unused for warfog's render
		/// </summary>
		void SetInactive();

		bool IsObservingActive;
	};
}