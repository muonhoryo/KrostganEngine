
#include <LineAAAnimation.h>
#include <Engine.h>
#include <EntityBattleStats.h>

using namespace KrostganEngine::Visual;
using namespace KrostganEngine::GameObjects;


LineAAAnimation::LineAAAnimation(WorldTransfObj& Owner)
	:AutoAttackAnimation(Owner),
	LineRender(Owner.GetGlobalPosition(), Owner.GetGlobalPosition(), Engine::GetGlobalConsts().AAAnim_LineWidth, Color::Red),
	LineEffect(*new FadingVisualEff_MRes(LineRender)){

	LineRender.AddEffect(LineEffect);
}

LineAAAnimation::~LineAAAnimation() {

	if (Target != nullptr)
		delete Target;
	delete &LineEffect;
}

void LineAAAnimation::OnTakeDmg(const AutoAttackHitInfo& attInfo) {

	float cdown = attInfo.AAStats.GetCooldown();
	LineEffect.ResetFade(cdown);
	Target = new watch_ptr_handler_wr<WorldTransfObj>(attInfo.Target);
	LineRender.SetStart(Owner.GetGlobalPosition());
	auto ptr = Target->GetPtr_t();
	if (ptr != nullptr) {

		LineRender.SetEnd(ptr->GetGlobalPosition());
	}
	
}
void LineAAAnimation::RenderGraphicAction(RenderWindow& window) {

	if (LineEffect.GetIsFadingState()) {

		LineRender.SetStart(Owner.GetGlobalPosition());
		if (Target != nullptr) {
			auto ptr = Target->GetPtr_t();
			if (ptr != nullptr) {

				LineRender.SetEnd(ptr->GetGlobalPosition());
			}
		}
	}
}