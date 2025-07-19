#pragma once

#include <ICallbackRec_Upd.h>
#include <ICallbackRec_LUpd.h>
#include <ICallbackRec_GraphRen.h>
#include <ICallbackRec_GraphPostRen.h>
#include <Events.h>

using namespace KrostganEngine;

namespace KrostganEngine::Core {

	class CallbackDelegate_Upd :public ICallbackRec_Upd {

	public:
		CallbackDelegate_Upd() :ICallbackRec_Upd(){}

		void Update(CallbackRecArgs_Upd args) override {
			Execute(args);
			delete this;
		}

	protected:
		virtual void Execute(CallbackRecArgs_Upd args) = 0;
	};

	class CallbackDelegate_LUpd :public ICallbackRec_LUpd {

	public:
		CallbackDelegate_LUpd() :ICallbackRec_LUpd() {}

		void Update(CallbackRecArgs_LUpd args) override {
			Execute(args);
			delete this;
		}

	protected:
		virtual void Execute(CallbackRecArgs_LUpd args) = 0;
	};

	class CallbackDelegate_GraphRen :public ICallbackRec_GraphRen {

	public:
		CallbackDelegate_GraphRen() :ICallbackRec_GraphRen() {}

		void RenderGraphic(RenderWindow& window) override {
			Execute(window);
			delete this;
		}

	protected:
		virtual void Execute(RenderWindow& window) = 0;
	};

	class CallbackDelegate_GraphPostRen :public ICallbackRec_GraphPostRen {

	public:
		CallbackDelegate_GraphPostRen() :ICallbackRec_GraphPostRen() {}

		void RenderGraphic(RenderWindow& window) override {
			Execute(window);
			delete this;
		}

	protected:
		virtual void Execute(RenderWindow& window) = 0;
	};
}