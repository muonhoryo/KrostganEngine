#pragma once

#include <ExternalGlobalResources.h>
#include <ValuesListDeserializer.h>
#include <vector>
#include <string>
#include <ExtGlRes_Texture.h>
#include <ExtGlRes_Font.h>
#include <ExtGlRes_Sprite.h>
#include <ExtGlRes_Shader.h>
#include <SFML/Graphics.hpp>

using namespace std;

namespace KrostganEngine::Core {
	class ExtGlobalResourcesLoad final: public ValuesListDeserializer {
	public:
		ExtGlobalResourcesLoad();
		~ExtGlobalResourcesLoad(){}

		void LoadGlobalResources();

	private:

		void LoadAdditionalResources();
		void LoadCoreResources();

		ExtGlResource& DeserRes	();
		ExtGlRes_Texture&	DeserRes_Texture();
		ExtGlRes_Sprite&	DeserRes_Sprite();
		ExtGlRes_Font&		DeserRes_Font();
		ExtGlRes_Shader&	DeserRes_Shader();

		Texture*	LoadTextureByPath();
		Font*		LoadFontByPath();
		Shader*		LoadShaderByPath();

		const Texture*	GetTextureByName() const;
		const Font*		GetFontByName() const;
		Shader*			GetShaderByName() const;

		const string GetFilePath() override;
		const char GetValuesDefEndSym() override;

		string LineBuffer;
		vector<string> ParamsBuffer;

		static const inline string GLOBAL_RESOURCES_PATH = "GlobalResources.txt";
		static const inline char RESOURCE_DEF_END_SYM = ':';
		static const inline string RESOURCE_DEF_SEP_LINE= "endl;";
		//Resource type definitions
		static const inline string DEF_RESOURCE_TYPE = "Type";

		static const inline string RESOURCETYPE_TEXTURE		= "Texture";
		static const inline string RESOURCETYPE_SPRITE		= "Sprite";
		static const inline string RESOURCETYPE_FONT		= "Font";
		static const inline string RESOURCETYPE_SHADER		= "Shader";
		//Resource param definitions
		static const inline string DEF_RESOURCE_NAME	= "Name";
		static const inline string DEF_SOURCE			= "Source";
		static const inline string DEF_PATH				= "Path";

		static const inline string DEF_SPRITE_OFFSET	= "Offset";
		static const inline string DEF_SPRITE_MAXSIZE	= "MaxSize";

		static const inline string DEF_RENDER_SHADER	= "Shader";

		//Shader type definitions
		static const inline string DEF_SHADER_TYPE		= "ShaderType";

		static const inline string SHADERTYPE_FRAG		= "Frag";
		static const inline string SHADERTYPE_VERT		= "Vert";
		static const inline string SHADERTYPE_GEO		= "Geo";

	};
}