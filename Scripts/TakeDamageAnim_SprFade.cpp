
#include <TakeDamageAnim_SprFade.h>
#include <Engine.h>

using namespace KrostganEngine;
using namespace KrostganEngine::Visual;

TakeDamageAnim_SprFade::TakeDamageAnim_SprFade(SpriteRenderer& HitSprite)
	:HitSprite(HitSprite),
	HitEffect(*new FadingVisualEff_MRes(Engine::GetGlobalConsts().TakeDmg_FadeTime, HitSprite)){

	HitSprite.SetColor(Color(255, 0, 0, HitSprite.GetColor().a));
	HitSprite.AddEffect(HitEffect);
}
TakeDamageAnim_SprFade::~TakeDamageAnim_SprFade() {

	delete& HitEffect;
}

void TakeDamageAnim_SprFade::OnTakeDmg(const AttackHitInfo& attInfo, size_t totalDmg) {
	
	HitEffect.ResetFade();
}