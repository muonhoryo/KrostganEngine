#pragma once

#include <AutoAttackAnimation.h>
#include <CoreUIUX.h>
#include <Engine.h>

using namespace std;
using namespace sf;
using namespace KrostganEngine::GameObjects;

namespace KrostganEngine::UI {
	class LineAAAnimation :public AutoAttackAnimation ,public ICallbackRec_GraphRen{

	public:
		LineAAAnimation(TransformableObj& Owner) : AutoAttackAnimation(Owner),
			LineRender(Owner.GetPosition(),Owner.GetPosition(),Engine::GetGlobalConsts().AAAnim_LineWidth, Color::Red),
			Target(nullptr){

		}
		~LineAAAnimation(){}

		void OnDealDmg(AutoAttackInfo attInfo) override;

		void RenderGraphic(RenderWindow& window) override;

	private:
		WideLineVisual LineRender;
		float Cooldown=0;
		Clock HidingTimer;
		bool IsRender = false;
		TransformableObj* Target;
	};
}