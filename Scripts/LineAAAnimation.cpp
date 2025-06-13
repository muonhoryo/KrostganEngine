
#include <LineAAAnimation.h>
#include <EntityBattleStats.h>

using namespace KrostganEngine::UI;
using namespace KrostganEngine::GameObjects;

void LineAAAnimation::OnDealDmg(AutoAttackInfo attInfo) {

	IsRender = true;
	Cooldown = EntityBattleStats::GetAACooldown(attInfo.AASpeed);
	HidingTimer.restart();
	LineRender.SetColor(Color::Red);
	Target = &attInfo.Target;
	LineRender.SetStart(Owner.GetPosition());
	LineRender.SetEnd(Target->GetPosition());
}
void LineAAAnimation::RenderGraphic(RenderWindow& window) {

	if (IsRender) {
		float time = HidingTimer.getElapsedTime().asSeconds();
		if (time < Cooldown) {

			LineRender.SetStart(Owner.GetPosition());
			LineRender.SetEnd(Target->GetPosition());
			float transparency = (1 - time)/Cooldown;
			Color clr = LineRender.GetEdgeColor();
			clr = Color(clr.r, clr.g, clr.b, (Uint8)(transparency * 255));
			LineRender.SetColor(clr);
		}
		else {
			IsRender = false;
			Color clr = LineRender.GetEdgeColor();
			LineRender.SetColor(Color(clr.r, clr.g, clr.b, 0));
		}
	}
}