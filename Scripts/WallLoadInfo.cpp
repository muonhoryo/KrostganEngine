
#include <WorldObjectLoadInfo.h>
#include <Wall.h>

using namespace KrostganEngine::GameObjects;

WorldTransfObj* WallLoadInfo::InstantiateObject_Action(const WorldObjectLoadInfo& usedInfo) const {

	auto& parInfo = *dynamic_cast<const WallLoadInfo*>(&usedInfo);

	auto& params = *new GameObjectCtorParams();
	FillCtorParams(params, *dynamic_cast<const GameObjectLoadInfo*>(&usedInfo));
	WallObject* wall = new WallObject(params);
	delete& params;

	return wall;
}
bool WallLoadInfo::WriteParam(Attr& param) {
	return GameObjectLoadInfo::WriteParam(param);
}
WorldObjectLoadInfo& WallLoadInfo::Clone() const {
	return *new WallLoadInfo(*this);
}
