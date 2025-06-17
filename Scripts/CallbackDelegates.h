#pragma once

#include <ICallbackRec_Upd.h>
#include <ICallbackRec_LUpd.h>
#include <ICallbackRec_GraphRen.h>
#include <ICallbackRec_GraphPostRen.h>

namespace KrostganEngine::Core {
	template <typename TArg>
	class CallbackDelegate_Upd :public ICallbackRec_Upd {
	public:
		CallbackDelegate_Upd(void(*Delegate)(TArg a), TArg arg) :ICallbackRec_Upd(),
			Delegate(Delegate), arg(arg){}

		void Update(CallbackRecArgs_Upd args) override {
			Delegate(arg);
			delete this;
		}

	private:
		void(*Delegate)(TArg a);

		TArg arg;
	};
	template<typename TArg>
	class CallbackDelegate_LUpd :  public ICallbackRec_LUpd {
	public:
		CallbackDelegate_LUpd(void(*Delegate)(TArg a), TArg arg) :ICallbackRec_LUpd(),
			Delegate(Delegate), arg(arg) {}

		void Update(CallbackRecArgs_LUpd args) override {
			Delegate(arg);
			delete this;
		}

	private:
		void(*Delegate)(TArg a);

		TArg arg;
	};
	template <typename TArg>
	class CallbackDelegate_GraphRen :  public ICallbackRec_GraphRen {
	public:
		CallbackDelegate_GraphRen(void(*Delegate)(TArg a), TArg arg) :ICallbackRec_GraphRen(),
			Delegate(Delegate), arg(arg) {}

		void RenderGraphic(RenderWindow& window) override {
			Delegate(arg);
			delete this;
		}

	private:
		void(*Delegate)(TArg a);

		TArg arg;
	};
	template <typename TArg>
	class CallbackDelegate_GraphPostRen :public ICallbackRec_GraphPostRen {
	public:
		CallbackDelegate_GraphPostRen(void(*Delegate)(TArg a), TArg arg) :ICallbackRec_GraphPostRen(),
			Delegate(Delegate), arg(arg) {}

		void RenderGraphic(RenderWindow& window) override {
			Delegate(arg);
			delete this;
		}

	private:
		void(*Delegate)(TArg a);

		TArg arg;
	};
}