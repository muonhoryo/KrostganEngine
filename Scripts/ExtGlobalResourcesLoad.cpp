
#include <ExtGlobalResourcesLoad.h>
#include <string>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <Extensions.h>
#include <iostream>
#include <fstream>
#include <ValuesListDeserializer.h>

using namespace sf;
using namespace rapidxml;
using namespace std;
using namespace KrostganEngine::Core;

void ExtGlobalResourcesLoad::LoadGlobalResources() {
	
	ExternalGlobalResources::Unload();

	LoadAdditionalResources();
	LoadCoreResources();
}

void ExtGlobalResourcesLoad::LoadAdditionalResources() {

	auto doc = new xml_document<>();
	char* file = FStreamExts::ReadToEnd(GLOBAL_RESOURCES_PATH);
	doc->parse<0>(file);

	char* type = nullptr;
	xml_node<>* serRes = doc->first_node()->first_node();
	ExtGlResource* deserRes = nullptr;

	while (serRes != nullptr) {

		type = serRes->name();

		if (type == RESOURCETYPE_TEXTURE) {

			deserRes = &DeserRes_Texture(*serRes);
		}
		else if (type == RESOURCETYPE_SPRITE) {

			deserRes = &DeserRes_Sprite(*serRes);
		}
		else if (type == RESOURCETYPE_FONT) {

			deserRes = &DeserRes_Font(*serRes);
		}
		else if (type == RESOURCETYPE_SHADER) {

			deserRes = &DeserRes_Shader(*serRes);
		}
		else {
			cout << "!!!Unknown type of resource: " << type << endl;
			serRes = doc->next_sibling();
			continue;
		}
		
		ExternalGlobalResources::AddRes(*deserRes);
		serRes = serRes->next_sibling();
	}

	delete doc;
}

void ExtGlobalResourcesLoad::LoadCoreResources() {

}

ExtGlRes_Texture& ExtGlobalResourcesLoad::DeserRes_Texture(xml_node<>& serRes) {

	xml_attribute<>* attr = serRes.first_attribute();
	char* attrName = nullptr;

	string name = "";
	const Texture* tex = nullptr;
	while (attr != nullptr) {

		attrName = attr->name();

		if (attrName == DEF_RESOURCE_NAME) {

			name = string(attr->value());
		}
		else if (attrName == DEF_PATH) {

			if (tex != nullptr)
				delete tex;
			string path = string(attr->value());
			tex = LoadTextureByPath(path);
		}

		attr = attr->next_attribute();
	}

	FStreamExts::ClearPath(name);
	if (tex == nullptr)
		throw exception("Absent texture");
	return *new ExtGlRes_Texture(name, *tex);
}

ExtGlRes_Sprite& ExtGlobalResourcesLoad::DeserRes_Sprite(xml_node<>& serRes) {

	xml_attribute<>* attr = serRes.first_attribute();
	char* attrName = nullptr;

	string name = "";
	const Texture* tex = nullptr;
	Shader* shad = nullptr;
	float maxSize = Engine::GetGlobalConsts().GameObjs_OneSizeSpriteResolution;
	while (attr != nullptr) {

		attrName = attr->name();

		if (attrName == DEF_RESOURCE_NAME) {

			name = string(attr->value());
		}
		else if (attrName == DEF_SOURCE) {

			char* attrValue = attr->value();
			if (tex != nullptr)
				delete tex;
			if (ValuesListDeserializer::CouldBeName(attrValue)) {

				string texName = string(attrValue);
				tex = GetTextureByName(texName);
			}
			else {

				string path = string(attrValue);
				tex = LoadTextureByPath(path);
			}
		}
		else if (attrName == DEF_RENDER_SHADER) {

			if (shad != nullptr)
				delete shad;
			string shadName = string(attr->value());
			shad = GetShaderByName(shadName);
		}
		else if (attrName == DEF_SPRITE_MAXSIZE) {

			maxSize = stof(attr->value());
		}

		attr = attr->next_attribute();
	}

	FStreamExts::ClearPath(name);
	if (tex == nullptr)
		throw exception("Absebt texture");
	return *new ExtGlRes_Sprite(name, *tex, maxSize, shad);
}

ExtGlRes_Font& ExtGlobalResourcesLoad::DeserRes_Font(xml_node<>& serRes) {

	xml_attribute<>* attr = serRes.first_attribute();
	char* attrName = nullptr;

	string name = "";
	Font* font = nullptr;
	while (attr != nullptr) {

		attrName = attr->name();

		if (attrName == DEF_RESOURCE_NAME) {

			name = string(attr->value());
		}
		else if (attrName == DEF_PATH) {

			if (font != nullptr)
				delete font;
			string path = string(attr->value());
			font = LoadFontByPath(path);
		}

		attr = attr->next_attribute();
	}

	FStreamExts::ClearPath(name);
	if (font == nullptr)
		throw exception("Absent font");
	return *new ExtGlRes_Font(name, *font);
}

ExtGlRes_Shader& ExtGlobalResourcesLoad::DeserRes_Shader(xml_node<>& serRes) {

	xml_attribute<>* attr = serRes.first_attribute();
	char* attrName = nullptr;

	string name = "";
	Shader* shad = nullptr;
	Shader::Type shadType = Shader::Type::Fragment;
	while (attr != nullptr) {

		attrName = attr->name();

		if (attrName == DEF_RESOURCE_NAME) {

			name = string(attr->value());
		}
		else if (attrName == DEF_SHADER_TYPE) {

			char* attrValue = attr->value();
			if (attrValue == SHADERTYPE_FRAG) {
				shadType = Shader::Fragment;
			}
			else if (attrValue == SHADERTYPE_VERT) {
				shadType = Shader::Vertex;
			}
			else if (attrValue == SHADERTYPE_GEO) {
				shadType = Shader::Geometry;
			}
			else
				throw exception("Cant get shader type");
		}
		else if (attrName == DEF_PATH) {

			if (shad != nullptr)
				delete shad;
			string shadPath = string(attr->value());
			shad = LoadShaderByPath(shadPath, shadType);
		}

		attr = attr->next_attribute();
	}

	FStreamExts::ClearPath(name);
	if (shad == nullptr)
		throw exception("Absent shader");
	return *new ExtGlRes_Shader(name, *shad);
}


const Texture* ExtGlobalResourcesLoad::GetTextureByName(string& path) {

	FStreamExts::ClearPath(path);
	ExtGlResource* res = ExternalGlobalResources::GetRes(path);
	if (res == nullptr)
		return nullptr;
	return &dynamic_cast<ExtGlRes_Texture*>(res)->Tex;
}
const Font* ExtGlobalResourcesLoad::GetFontByName(string& path) {

	FStreamExts::ClearPath(path);
	ExtGlResource* res = ExternalGlobalResources::GetRes(path);
	if (res == nullptr)
		return nullptr;
	return &dynamic_cast<ExtGlRes_Font*>(res)->Font_;
}
Shader* ExtGlobalResourcesLoad::GetShaderByName(string& path) {

	FStreamExts::ClearPath(path);
	ExtGlResource* res = ExternalGlobalResources::GetRes(path);
	if (res == nullptr)
		return nullptr;
	return &dynamic_cast<ExtGlRes_Shader*>(res)->Shader_;
}

Texture* ExtGlobalResourcesLoad::LoadTextureByPath(string& path) {

	FStreamExts::ClearPath(path);
	Texture* tex = new Texture();
	tex->loadFromFile(path);
	return tex;
}
Font* ExtGlobalResourcesLoad::LoadFontByPath(string& path) {

	FStreamExts::ClearPath(path);
	Font* font = new Font();
	font->loadFromFile(path);
	return font;
}
Shader* ExtGlobalResourcesLoad::LoadShaderByPath(string& path, Shader::Type type) {

	FStreamExts::ClearPath(path);
	Shader* shad = new Shader();
	shad->loadFromFile(path, type);
	return shad;
}