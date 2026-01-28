
#include <WorldObjectLoadInfo.h>

using namespace KrostganEngine::GameObjects;

WorldTransfObj* UnitLoadInfo::InstantiateObject_Action(const WorldObjectLoadInfo& usedInfo) const {

	UnitObjectCtorParams& params = *new UnitObjectCtorParams();
	FillCtorParams(params, *dynamic_cast<const GameObjectLoadInfo*>(&usedInfo));
	UnitObject* unit = new UnitObject(params);
	delete& params;

	return unit;
}
WorldObjectLoadInfo& UnitLoadInfo::Clone() const {
	return *new UnitLoadInfo(*this);
}
