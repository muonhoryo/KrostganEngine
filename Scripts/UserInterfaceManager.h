#pragma once

#include <UIEmpty.h>
#include <ICallbackRec_LUpd.h>

using namespace KrostganEngine;
using namespace KrostganEngine::Core;

namespace KrostganEngine::UI {
	class UserInterfaceManager final{

	private:
		class UIRootMover final : public ICallbackRec_LUpd {
		public:
			UIRootMover(UIEmpty& Root);

			void Update(CallbackRecArgs_LUpd args) override;

		private:
			UIEmpty& Root;
		};

		UserInterfaceManager() {}

		static inline UIEmpty* UserInterface = nullptr;

	public:
		static void Initialize();
		static UIEmpty& GetRoot() {
			return *UserInterface;
		}

	};
}