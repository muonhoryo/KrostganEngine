#pragma once

#include <ExternalGlobalResources.h>

using namespace sf;
using namespace std;

namespace KrostganEngine::Core {
	struct ExtGlRes_Texture : public ExtGlResource {
	
		ExtGlRes_Texture(const string& Name, const Texture& Tex)
			: ExtGlResource(Name),
			Tex(Tex)
		{}

		virtual ~ExtGlRes_Texture() {
			delete& Tex;
		}

		const Texture& Tex;

		//virtual ExtGlResource::ResType GetType() override { return ExtGlResource::ResType::Texture; }
	};
}