#pragma once

#include <AutoAttackAnimation.h>
#include <CoreUIUX.h>
#include <Engine.h>
#include <GameVisualEffects.h>

using namespace std;
using namespace sf;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::Visual;

namespace KrostganEngine::UI {
	class LineAAAnimation :public AutoAttackAnimation ,public ICallbackRec_GraphRen{

	public:
		LineAAAnimation(TransformableObj& Owner);
		~LineAAAnimation();

		void OnDealDmg(AutoAttackInfo attInfo) override;

		void RenderGraphic(RenderWindow& window) override;

	private:
		WideLineVisual LineRender;
		SingleSprite* HitSprite=nullptr;
		FadingVisualEff_MRes& LineEffect;
		FadingVisualEff_MRes* HitEffect = nullptr;
		watch_ptr_handler_wr<TransformableObj>* Target = nullptr;
	};
}