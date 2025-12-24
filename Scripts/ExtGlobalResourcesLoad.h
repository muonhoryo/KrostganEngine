#pragma once

#include <ExternalGlobalResources.h>
#include <vector>
#include <string>
#include <ExtGlRes_Texture.h>
#include <ExtGlRes_Font.h>
#include <ExtGlRes_Sprite.h>
#include <ExtGlRes_Shader.h>
#include <SFML/Graphics.hpp>
#include <rapidxml.hpp>

using namespace std;
using namespace rapidxml;

namespace KrostganEngine::Core {

	class ExtGlobalResourcesLoad final {
	private:
		ExtGlobalResourcesLoad(){}
		~ExtGlobalResourcesLoad() {}

	public:
		static void LoadGlobalResources();

	private:
		static void LoadAdditionalResources();
		static void LoadCoreResources();

		static ExtGlRes_Texture&	DeserRes_Texture(xml_node<>& serRes);
		static ExtGlRes_Sprite&		DeserRes_Sprite(xml_node<>& serRes);
		static ExtGlRes_Font&		DeserRes_Font(xml_node<>& serRes);
		static ExtGlRes_Shader&		DeserRes_Shader(xml_node<>& serRes);

		static const Texture*	GetTextureByName(string& path);
		static const Font*		GetFontByName(string& path);
		static Shader*			GetShaderByName(string& path);

		static Texture*		LoadTextureByPath(string& path);
		static Font*		LoadFontByPath(string& path);
		static Shader*		LoadShaderByPath(string& path, Shader::Type type);

// Consts
	private:
		static const inline string GLOBAL_RESOURCES_PATH = "GlobalResources.xml";
		//Resource type definitions
		static const inline string DEF_RESOURCE_TYPE = "Type";

		static const inline string RESOURCETYPE_TEXTURE = "Texture";
		static const inline string RESOURCETYPE_SPRITE = "Sprite";
		static const inline string RESOURCETYPE_FONT = "Font";
		static const inline string RESOURCETYPE_SHADER = "Shader";
		//Resource param definitions
		static const inline string DEF_RESOURCE_NAME = "Name";
		static const inline string DEF_SOURCE = "Source";
		static const inline string DEF_PATH = "Path";

		static const inline string DEF_SPRITE_MAXSIZE = "MaxSize";

		static const inline string DEF_RENDER_SHADER = "Shader";

		//Shader type definitions
		static const inline string DEF_SHADER_TYPE = "ShaderType";

		static const inline string SHADERTYPE_FRAG = "Frag";
		static const inline string SHADERTYPE_VERT = "Vert";
		static const inline string SHADERTYPE_GEO = "Geo";
	};
}