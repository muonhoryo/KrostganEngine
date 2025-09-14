#pragma once

#include <UIEmpty.h>
#include <ICallbackRec_LUpd.h>
#include <vector>
#include <ValueDependency.h>
#include <FirstSelEntityDependsManager.h>

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
			UIRootMover(UIEmpty& Root);

			void Update(CallbackRecArgs_LUpd args) override;

		private:
			UIEmpty& Root;
		};

		UserInterfaceManager() {}

		static inline UIEmpty*						UserInterface = nullptr;
		static inline FirstSelEntityDependsManager* FirstSelEntityDepend = new FirstSelEntityDependsManager();
		static inline vector<IUIDependency*>	UIDependencies{
			FirstSelEntityDepend
		};
			
	public:
		static void Initialize();
		static void Unload();
		static UIEmpty& GetRoot() {
			return *UserInterface;
		}
		static FirstSelEntityDependsManager& GetFirstSelEntityDepend() {
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