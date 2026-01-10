#pragma once

#include <UIEmpty.h>
#include <ICallbackRec_LUpd.h>
#include <vector>
#include <ValueDependency.h>
#include <FirstChoosenEntityDependsManager.h>
#include <UIRoot.h>

using namespace std;
using namespace KrostganEngine;
using namespace KrostganEngine::Core;

namespace KrostganEngine::UI {
	class UserInterfaceManager final{

	private:
		/// <summary>
		/// Used to move UI to camera's view center
		/// </summary>
		class UIRootMover final : public ICallbackRec_LUpd {
		public:
			UIRootMover(UIRoot& Root);

			void Update(CallbackRecArgs_LUpd args) override;

		private:
			UIRoot& Root;
		};

		UserInterfaceManager() {}

		static inline UIRoot*						UserInterface = nullptr;
		static inline FirstChoosenEntityDependsManager* FirstSelEntityDepend = new FirstChoosenEntityDependsManager();
		static inline vector<IUIDependency*>	UIDependencies{
			FirstSelEntityDepend
		};
			
	public:
		static void Initialize();
		static void Unload();
		static UIRoot& GetRoot() {
			return *UserInterface;
		}
		static FirstChoosenEntityDependsManager& GetFirstSelEntityDepend() {
			return *FirstSelEntityDepend;
		}

		static void AddDependency(IUIDependency& dependency) {
			if(!CollectionsExts::Contains(UIDependencies,&dependency))
				UIDependencies.push_back(&dependency);
		}
		static void RemoveDependency(IUIDependency& dependency) {
			CollectionsExts::Remove(UIDependencies, &dependency);
		}

	};
}