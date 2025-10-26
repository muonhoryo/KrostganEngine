#pragma once

#include <IAttackableObj.h>
#include <ICallbackRec_Upd.h>
#include <AutoAttackAnimation.h>

using namespace KrostganEngine::Core;
using namespace KrostganEngine::Visual;

namespace KrostganEngine::GameObjects {
	class AutoAttackModule: public ICallbackRec_Upd {
	public:
		virtual ~AutoAttackModule();

		virtual void SetAsTarget(watch_ptr_handler_wr<IAttackableObj>* target) = 0;
		/// <summary>
		/// Return true if attacked target is in attack range.
		/// </summary>
		/// <returns></returns>
		virtual bool CheckTargetReach() = 0;
		/// <summary>
		/// Return true if potential target is in attack range.
		/// </summary>
		/// <returns></returns>
		virtual bool CheckTargetReach(const IAttackableObj& potentTarget) = 0;
		virtual bool TryDealDamageToTarget() = 0;

		virtual IAttackableObj* GetCurrentTarget();

		float GetRemReloadTime() const;

		void Update(CallbackRecArgs_Upd args) override;

	protected:
		AutoAttackModule(AutoAttackAnimation& AAAnimation);

		watch_ptr_handler_wr<IAttackableObj>* Target;
		/// <summary>
		/// In milliseconds
		/// </summary>
		float RemReloadTime = 0;
		AutoAttackAnimation& AAAnimation;
	};
}