
#include <IWarFogObserver.h>
#include <WarFogStencilGen.h>

using namespace KrostganEngine::Core;
using namespace KrostganEngine::Physics;

IWarFogObserver::IWarFogObserver(bool isObservingActive)
	:ITransformableObj(),
	ICallbackRec(),
	IsObservingActive(isObservingActive){

	if (IsObservingActive)
		SetActive();
}

IWarFogObserver::~IWarFogObserver() {

	if (IsObservingActive)
		SetInactive();
}

void IWarFogObserver::SetObservingActive(bool isActive) {
	if (IsObservingActive != isActive) {
		if (IsObservingActive)
			SetInactive();
		else
			SetActive();

		IsObservingActive = isActive;
	}
}
bool IWarFogObserver::GetObservingActivity() const {
	return IsObservingActive;
}

void IWarFogObserver::SetActive() {
	WarFogStencilGen::GetInstance()->Add(*this);
	ObservingArea = new WarFogObserver_ObsrArea(*this);
}
void IWarFogObserver::SetInactive() {
	WarFogStencilGen::GetInstance()->Remove(*this);
	delete ObservingArea;
	ObservingArea = nullptr;
}