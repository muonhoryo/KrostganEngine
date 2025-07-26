#pragma once

#include <ExternalGlobalResources.h>

namespace KrostganEngine::Core {
	struct ExtGlRes_Shader : public ExtGlResource {

		ExtGlRes_Shader(const string& Name, Shader& Shader_)
			:ExtGlResource(Name),
			Shader_(Shader_) {}

		virtual ~ExtGlRes_Shader() {
			delete& Shader_;
		}

		Shader& Shader_;
	};
}