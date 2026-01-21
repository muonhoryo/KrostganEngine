
#include <EngineRenderModule.h>
#include <EngineCore.h>
#include <vector>
#include <Extensions.h>

using namespace std;
using namespace KrostganEngine::Core;

EngineRenderModule::EngineRenderModule(RenderWindow& Window): EngineCallbackHandler<ICallbackRec_GraphRen>(),
	Window(Window)
{
}
void EngineRenderModule::Execute() {
	FrameRenderTime.restart();
	if (!Window.isOpen())
		return;

	IsIteratingCallbacks = true;

	if (NeedToSort) {

		Callbacks.sort(RenCallbks_SortPred);
		NeedToSort = false;
	}

	auto it = Callbacks.begin();
	auto itEnd = Callbacks.cend();
	ICallbackRec_GraphRen* calbck = nullptr;

	//Fill stencil buffer
	glEnable(GL_STENCIL_TEST);

	Window.clear();

	auto warFogGen = WarFogStencilGen::GetInstance();
	if (warFogGen != nullptr)
		warFogGen->Execute();
	else {

		glStencilMask(0xFF);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		glClear(GL_STENCIL_BUFFER_BIT);
	}

	//Render objects which are hidden by war fog (IsHidenByWarFog & !IsShownByWarFog)
	
	bool reachedEnd = RenderObjects_FogHidden(it, itEnd);
	if (!reachedEnd) {

		//Render objects which are shown under war fog only (IsShownByWarFog)
		reachedEnd = RenderObjects_FogShown(it, itEnd);
		if (!reachedEnd) {

			//Render objects which are not hidden by any stencil-test value (!IsHidenByWarFog & !IsShownByWarFog)
			reachedEnd = RenderObjects_AlwaysShown(it, itEnd);
		}
	}

	glEnable(GL_STENCIL_TEST);
	//Repeat for late rendered-objects
	if (!reachedEnd) {

		//Render objects which are hidden by war fog (IsHidenByWarFog & !IsShownByWarFog)
		reachedEnd = RenderObjects_FogHidden(it, itEnd);
		if (!reachedEnd) {

			//Render objects which are shown under war fog only (IsShownByWarFog)
			reachedEnd = RenderObjects_FogShown(it, itEnd);
			if (!reachedEnd) {

				//Render objects which are not hidden by any stencil-test value (!IsHidenByWarFog & !IsShownByWarFog)
				RenderObjects_AlwaysShown(it, itEnd);
			}
		}
	}

	//Render objects which are hidden by war fog (IsHidenByWarFog & !IsShownByWarFog)

	//glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	//glStencilMask(0x00);
	//glStencilFunc(GL_NOTEQUAL, WarFogStencilGen::WARFOG_STENCIL_MASK, 0xFF);
	//while (it != itEnd) {

	//	if (*it == nullptr) {
	//		++it;
	//		continue;
	//	}

	//	calbck = *it;
	//	if (!calbck->Get_IsHidenByWarFog() ||
	//		calbck->Get_IsShownByWarFog()) {
	//			//Check if iterator came to next group of render
	//		break;
	//	}

	//	calbck->RenderGraphic(Window);
	//	++it;
	//}

	//Render objects which are shown under war fog only (IsShownByWarFog)

	//glStencilFunc(GL_EQUAL, WarFogStencilGen::WARFOG_STENCIL_MASK, 0xFF);
	//while (it != itEnd) {

	//	if (*it == nullptr) {
	//		++it;
	//		continue;
	//	}

	//	calbck = *it;
	//	if (!calbck->Get_IsShownByWarFog()) {
	//		//Check if iterator came to next group of render
	//		break;
	//	}

	//	calbck->RenderGraphic(Window);
	//	++it;
	//}


	//Render objects which are not hidden by any stencil-test value (!IsHidenByWarFog & !IsShownByWarFog)
	/*glDisable(GL_STENCIL_TEST);
	while (it != itEnd) {

		if (*it == nullptr) {
			++it;
			continue;
		}

		calbck = *it;

		calbck->RenderGraphic(Window);
		++it;
	}*/

	IsIteratingCallbacks = false;

	DeleteDelayedCallbacks();

	Window.display();
	SetFrameRenderTime(FrameRenderTime.getElapsedTime().asSeconds());
}

bool EngineRenderModule::RenderObjects_FogHidden
	(list<ICallbackRec_GraphRen*>::iterator& it, list<ICallbackRec_GraphRen*>::const_iterator& end) {

	ICallbackRec_GraphRen* calbck = nullptr;
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	glStencilMask(0x00);
	glStencilFunc(GL_NOTEQUAL, WarFogStencilGen::WARFOG_STENCIL_MASK, 0xFF);
	while (it != end) {

		if (*it == nullptr) {
			++it;
			continue;
		}

		calbck = *it;
		if (!calbck->Get_IsHidenByWarFog() ||
			calbck->Get_IsShownByWarFog()) {
			//Check if iterator came to next group of render
			return false;
		}

		calbck->RenderGraphic(Window);
		++it;
	}
	return true;
}
bool EngineRenderModule::RenderObjects_FogShown
	(list<ICallbackRec_GraphRen*>::iterator& it, list<ICallbackRec_GraphRen*>::const_iterator& end){

	ICallbackRec_GraphRen* calbck = nullptr;
	glStencilFunc(GL_EQUAL, WarFogStencilGen::WARFOG_STENCIL_MASK, 0xFF);
	while (it != end) {

		if (*it == nullptr) {
			++it;
			continue;
		}

		calbck = *it;
		if (!calbck->Get_IsShownByWarFog()) {
			//Check if iterator came to next group of render
			return false;
		}

		calbck->RenderGraphic(Window);
		++it;
	}
	return true;
}
bool EngineRenderModule::RenderObjects_AlwaysShown
	(list<ICallbackRec_GraphRen*>::iterator& it, list<ICallbackRec_GraphRen*>::const_iterator& end){

	ICallbackRec_GraphRen* calbck = nullptr;
	glDisable(GL_STENCIL_TEST);
	while (it != end) {

		if (*it == nullptr) {
			++it;
			continue;
		}

		calbck = *it;
		if (calbck->Get_IsShownByWarFog() ||
			calbck->Get_IsHidenByWarFog()) {
			//Check if iterator came to next group of render
			return false;
		}

		calbck->RenderGraphic(Window);
		++it;
	}
	return true;
}

void EngineRenderModule::SetFrameRenderTime(float time) {
	Engine::Singleton->FrameRenderTime = time;
}
void EngineRenderModule::SetNeedToSort() {
	NeedToSort = true;
}

void EngineRenderModule::OnAddCallback(ICallbackRec_GraphRen& callbck) {
	NeedToSort = true;
}