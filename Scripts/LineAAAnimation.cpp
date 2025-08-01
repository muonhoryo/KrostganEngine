
#include <LineAAAnimation.h>
#include <EntityBattleStats.h>

using namespace KrostganEngine::UI;
using namespace KrostganEngine::GameObjects;


LineAAAnimation::LineAAAnimation(TransformableObj& Owner)
	:AutoAttackAnimation(Owner),
	LineRender(Owner.GetPosition(), Owner.GetPosition(), Engine::GetGlobalConsts().AAAnim_LineWidth, Color::Red),
	LineEffect(*new FadingVisualEff_MRes(LineRender)){

	auto hitSpr = ExternalGlobalResources::GetRes_t<ExtGlRes_Sprite>(ExternalGlobalResources::CORE_RES_AA_HITSPRITE);
	HitSprite = new SingleSprite(
		hitSpr->Tex,
		Engine::GetGlobalConsts().GameObjs_OneSizeSpriteResolution,
		hitSpr->Offset,
		Owner.GetPosition(),
		1,
		Color::Red,
		hitSpr->RenShader);
	HitEffect = new FadingVisualEff_MRes(*HitSprite);
	LineRender.AddEffect(LineEffect);
	HitSprite->AddEffect(*HitEffect);
}

LineAAAnimation::~LineAAAnimation() {

	if (Target != nullptr)
		delete Target;
	delete HitSprite;
	delete HitEffect;
	delete &LineEffect;
}

void LineAAAnimation::OnDealDmg(AutoAttackInfo attInfo) {

	float cdown = EntityBattleStats::GetAACooldown(attInfo.AASpeed);
	LineEffect.ResetFade(cdown);
	HitEffect->ResetFade(cdown);
	Target = new watch_ptr_handler_wr<TransformableObj>(attInfo.Target);
	LineRender.SetStart(Owner.GetPosition());
	auto ptr = Target->GetPtr_t();
	if (ptr != nullptr) {

		LineRender.SetEnd(ptr->GetPosition());
		HitSprite->SetPosition(ptr->GetPosition());
	}
	
}
void LineAAAnimation::RenderGraphic(RenderWindow& window) {

	if (LineEffect.GetIsFadingState()) {

		LineRender.SetStart(Owner.GetPosition());
		if (Target != nullptr) {
			auto ptr = Target->GetPtr_t();
			if (ptr != nullptr) {

				LineRender.SetEnd(ptr->GetPosition());
				HitSprite->SetPosition(ptr->GetPosition());
			}
		}
	}
}