#pragma once

#include <EngineWorkCycleModule.h>
#include <ICallbackRec_LUpd.h>

namespace KrostganEngine::Core {

	class EngineLateUpdateModule :public EngineCallbackHandler<ICallbackRec_LUpd>,
		public EngineWorkCycleModule {

	public:
		EngineLateUpdateModule();

		void Execute() override;
	};
}