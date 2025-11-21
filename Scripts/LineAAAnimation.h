#pragma once

#include <AutoAttackAnimation.h>
#include <CoreVisual_UI.h>
#include <GameVisualEffects.h>

using namespace std;
using namespace sf;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::UI;

namespace KrostganEngine::Visual {
	class LineAAAnimation :public AutoAttackAnimation ,public ICallbackRec_GraphRen{

	public:
		LineAAAnimation(WorldTransfObj& Owner);
		virtual ~LineAAAnimation();

		void OnTakeDmg(const AutoAttackHitInfo& attInfo) override;

		void RenderGraphicAction(RenderWindow& window) override;

	private:
		WideLineVisual							LineRender;
		FadingVisualEff_MRes&					LineEffect;
		watch_ptr_handler_wr<WorldTransfObj>*	Target = nullptr;
	};
}