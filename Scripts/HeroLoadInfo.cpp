
#include <WorldObjectLoadInfo.h>

using namespace KrostganEngine::GameObjects;

WorldTransfObj* HeroLoadInfo::InstantiateObject_Action(const WorldObjectLoadInfo& usedInfo) const {

	auto& params = *new HeroObjectCtorParams();
	FillCtorParams(params, *dynamic_cast<const GameObjectLoadInfo*>(&usedInfo));
	HeroObject* hero = new HeroObject(params);
	delete& params;

	return hero;
}
bool HeroLoadInfo::WriteParam(Attr& param) {
	return UnitLoadInfo::WriteParam(param);
}
WorldObjectLoadInfo& HeroLoadInfo::Clone() const {
	return *new HeroLoadInfo(*this);
}
