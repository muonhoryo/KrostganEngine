#pragma once

#include <UIEmpty.h>

namespace KrostganEngine::UI {
	class UIRoot final : public UIEmpty {
	public:
		UIRoot(Vector2f UISize = DEFAULT_SCALE)
			:UIEmpty(&ROOT_NAME,UISize){
		
			DestroyOnUnload = false;
		}

		void	SetParent(IHierarchyTrObj* parent) override{}

		static inline const string ROOT_NAME = "root";
	};
}