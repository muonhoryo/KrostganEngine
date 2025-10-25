
#include <LineAAAnimation.h>
#include <EntityBattleStats.h>

using namespace KrostganEngine::UI;
using namespace KrostganEngine::GameObjects;


LineAAAnimation::LineAAAnimation(WorldTransfObj& Owner)
	:AutoAttackAnimation(Owner),
	LineRender(Owner.GetGlobalPosition(), Owner.GetGlobalPosition(), Engine::GetGlobalConsts().AAAnim_LineWidth, Color::Red),
	LineEffect(*new FadingVisualEff_MRes(LineRender)){

	auto hitSpr = ExternalGlobalResources::GetRes_t<ExtGlRes_Sprite>(ExternalGlobalResources::CORE_RES_AA_HITSPRITE);
	HitSprite = new SpriteRenderer(
		hitSpr->Tex,
		Engine::GetGlobalConsts().GameObjs_OneSizeSpriteResolution,
		Owner.GetGlobalPosition(),
		DEFAULT_SCALE_SNG,
		0,
		Color::Red,
		hitSpr->RenShader);
	HitSprite->SetDesWithParent(false);
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
	Target = new watch_ptr_handler_wr<WorldTransfObj>(attInfo.Target);
	LineRender.SetStart(Owner.GetGlobalPosition());
	auto ptr = Target->GetPtr_t();
	if (ptr != nullptr) {

		LineRender.SetEnd(ptr->GetGlobalPosition());
		HitSprite->SetParent(ptr);
		HitSprite->SetGlobalPosition(ptr->GetGlobalPosition());
		Vector2f glPos = HitSprite->GetGlobalPosition();
		glPos = HitSprite->GetGlobalPosition();
	}
	
}
void LineAAAnimation::RenderGraphic(RenderWindow& window) {

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