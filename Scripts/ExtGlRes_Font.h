#pragma once

#include <ExternalGlobalResources.h>

namespace KrostganEngine::Core {
	struct ExtGlRes_Font : public ExtGlResource {

		ExtGlRes_Font(const string& Name, const Font& Font_)
			:ExtGlResource(Name),
			Font_(Font_){}

		virtual ~ExtGlRes_Font() {
			delete& Font_;
		}

		const Font& Font_;
	};
}