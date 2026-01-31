
#include <WarFogObserver.h>
#include <WarFogStencilGen.h>
#include <WarFogObserversManager.h>

using namespace KrostganEngine::Core;
using namespace KrostganEngine::Physics;

WarFogObserver::WarFogObserver(bool isObservingActive)
	:ITransformableObj(),
	ICallbackRec(),
	IFractionMember(),
	IsObservingActive(isObservingActive){

	if (IsObservingActive)
		SetActive();

	WarFogObserversManager::GetInstance()->Add(*this);
}

WarFogObserver::~WarFogObserver() {

	if (IsObservingActive)
		SetInactive();

	WarFogObserversManager::GetInstance()->Remove(*this);
}

void WarFogObserver::SetObservingActive(bool isActive) {
	if (IsObservingActive != isActive) {
		if (IsObservingActive)
			SetInactive();
		else
			SetActive();

		IsObservingActive = isActive;
	}
}
void WarFogObserver::OnChangeFraction(FractionWrapper frac) {
	WarFogObserversManager::GetInstance()->Set_NeedToSort();
}

bool WarFogObserver::GetObservingActivity() const {
	return IsObservingActive;
}

void WarFogObserver::SetActive() {
	WarFogStencilGen::GetInstance()->Add(*this);
}
void WarFogObserver::SetInactive() {
	WarFogStencilGen::GetInstance()->Remove(*this);
}