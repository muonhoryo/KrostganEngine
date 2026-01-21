#pragma once

#include <EngineWorkCycleModule.h>
#include <ICallbackRec_GraphRen.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

namespace KrostganEngine::Core {

	static bool RenCallbks_SortPred(ICallbackRec_GraphRen* const& first, ICallbackRec_GraphRen* const& second) {

		//!!!Refactore with logic arichmetic!!!

		bool lateRender_1 = first->Get_LateRender();
		bool lateRender_2 = second->Get_LateRender();
		bool isHide_1 = first->Get_IsHidenByWarFog();
		bool isHide_2 = second->Get_IsHidenByWarFog();
		bool isShow_1 = first->Get_IsShownByWarFog();
		bool isShow_2 = second->Get_IsShownByWarFog();

		if (lateRender_1 != lateRender_2) {

			return lateRender_2;	//second clbk is rendered later than first
		}

		if (isHide_1) {

			return !isHide_2 ||
				first->GetRendLayer() < second->GetRendLayer();
		}
		else if (isHide_2) {

			return false;
		}
		else {

			if (isShow_1) {
				
				return !isShow_2 ||
					first->GetRendLayer() < second->GetRendLayer();
			}
			else if (isShow_2) {

				return false;
			}
			else {
				return first->GetRendLayer() < second->GetRendLayer();
			}
		}
	}

	class EngineRenderModule :public EngineCallbackHandler<ICallbackRec_GraphRen>, public EngineWorkCycleModule {
	public:
		EngineRenderModule(RenderWindow& Window);

		void Execute() override;

		void OnAddCallback(ICallbackRec_GraphRen& callbck) override;

	private:
		/// <summary>
		/// Return true if reached end of the list
		/// </summary>
		/// <param name="it"></param>
		/// <param name="end"></param>
		/// <returns></returns>
		bool RenderObjects_FogHidden
			(list<ICallbackRec_GraphRen*>::iterator& it, list<ICallbackRec_GraphRen*>::const_iterator& end);
		/// <summary>
		/// Return true if reached end of the list
		/// </summary>
		/// <param name="it"></param>
		/// <param name="end"></param>
		/// <returns></returns>
		bool RenderObjects_FogShown
			(list<ICallbackRec_GraphRen*>::iterator& it, list<ICallbackRec_GraphRen*>::const_iterator& end);
		/// <summary>
		/// Return true if reached end of the list
		/// </summary>
		/// <param name="it"></param>
		/// <param name="end"></param>
		/// <returns></returns>
		bool RenderObjects_AlwaysShown
			(list<ICallbackRec_GraphRen*>::iterator& it, list<ICallbackRec_GraphRen*>::const_iterator& end);

		RenderWindow& Window;
		Clock FrameRenderTime;
		bool NeedToSort = true;

	public:

		void SetFrameRenderTime(float time);
		void SetNeedToSort();
	};
}