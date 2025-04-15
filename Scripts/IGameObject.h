#pragma once

#include <ICallbacks.h>

namespace KrostganEngine {
	namespace GameObjects {
		class IGameObject :ICallbackRec_GraphRen {
			void GraphicRender() override;
		};
	}
}