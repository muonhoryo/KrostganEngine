#pragma once

#include <SpriteRenderer.h>
#include <IAttackableObj.h>
#include <_GameVisualEffects.h>

using namespace KrostganEngine::GameObjects;

namespace KrostganEngine::Visual {
	class TakeDamageAnim_SprFade : public TakeDamageAnimation {

	public:
		TakeDamageAnim_SprFade(SpriteRenderer& HitSprite);
		virtual ~TakeDamageAnim_SprFade();

		void OnTakeDmg(const AttackHitInfo& attInfo, size_t totalDmg) override;

	private:
		SpriteRenderer& HitSprite;
		TransparencyVisEff_MRes& HitEffect;
	};
}