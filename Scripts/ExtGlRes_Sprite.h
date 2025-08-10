#pragma once

#include <ExtGlRes_Texture.h>

using namespace sf;
using namespace std;

namespace KrostganEngine::Core {
	struct ExtGlRes_Sprite : public ExtGlRes_Texture {

		ExtGlRes_Sprite(
			const string&	Name,
			const Texture&	Tex,
			float			MaxSize,
			Shader*	RenShader)
				:ExtGlRes_Texture(Name,Tex),
				MaxSize			(MaxSize),
				RenShader		(RenShader)
		{}

		const float		MaxSize;
		Shader*			RenShader	= nullptr;
	};

}