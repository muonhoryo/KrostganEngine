
#include <ExtGlobalResourcesLoad.h>
#include <string>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <Extensions.h>
#include <iostream>
#include <fstream>

using namespace sf;
using namespace std;
using namespace KrostganEngine::Core;

ExtGlobalResourcesLoad::ExtGlobalResourcesLoad() :ValuesListDeserializer() { }

void ExtGlobalResourcesLoad::LoadGlobalResources() {

	ExternalGlobalResources::Unload();

	LoadAdditionalResources();
	LoadCoreResources();
}

void ExtGlobalResourcesLoad::LoadAdditionalResources() {

	string line;
	ifstream st(GetFilePath());
	if (st.bad() == true ||
		st.fail() == true)
		throw exception("Cannot open resource file");

	while (getline(st, line)) {

		if (line.find(RESOURCE_DEF_SEP_LINE) != string::npos) {

			DeserializeValues(ParamsBuffer);
			ExternalGlobalResources::AddRes(DeserRes());
			ParamsBuffer.clear();
		}
		else {

			ParamsBuffer.push_back(line);
		}
	}
	st.close();
	size_t size = ParamsBuffer.size();
	if (size > 1 ||
		size == 1 && ParamsBuffer[0].size() > 1) {

		DeserializeValues(ParamsBuffer);
		ExternalGlobalResources::AddRes(DeserRes());
	}
	ParamsBuffer.clear();
}
void ExtGlobalResourcesLoad::LoadCoreResources() {

}

ExtGlResource& ExtGlobalResourcesLoad::DeserRes() {

	string serType;
	GetValueByDef(DEF_RESOURCE_TYPE, serType);

	if (serType.find(RESOURCETYPE_TEXTURE) != string::npos) {

		return DeserRes_Texture();
	}
	else if (serType.find(RESOURCETYPE_SPRITE) != string::npos) {

		return DeserRes_Sprite();
	}
	else if (serType.find(RESOURCETYPE_FONT) != string::npos) {

		return DeserRes_Font();
	}
	else if (serType.find(RESOURCETYPE_SHADER) != string::npos) {

		return DeserRes_Shader();
	}
	else
		throw exception("Cant parse resource type");

}

ExtGlRes_Texture&	ExtGlobalResourcesLoad::DeserRes_Texture(){

	string* name=new string();
	GetValueByDef(DEF_RESOURCE_NAME, *name);
	FStreamExts::ClearPath(name);
	const Texture* tex = nullptr;
	GetValueByDef(DEF_PATH ,LineBuffer);
	tex = LoadTextureByPath();
	auto& res = *new ExtGlRes_Texture(*name, *tex);
	delete name;
	return res;
}
ExtGlRes_Sprite&	ExtGlobalResourcesLoad::DeserRes_Sprite(){

	string* name = new string();
	GetValueByDef(DEF_RESOURCE_NAME, *name);
	FStreamExts::ClearPath(name);
	const Texture* tex = nullptr;
	GetValueByDef(DEF_SOURCE, LineBuffer);
	FStreamExts::ClearPath(&LineBuffer);
	if (CouldBeName(LineBuffer)) {
		tex = GetTextureByName();
	}
	else {
		tex = LoadTextureByPath();
	}
	Shader* shad = nullptr;
	if (TryGetValue(DEF_RENDER_SHADER, LineBuffer)) {

		FStreamExts::ClearPath(&LineBuffer);
		shad = GetShaderByName();
	}
	float maxSize = 0;
	if (TryGetValue(DEF_SPRITE_MAXSIZE, LineBuffer)) {

		maxSize = stof(LineBuffer);
	}
	else {

		maxSize = Engine::GetGlobalConsts().GameObjs_OneSizeSpriteResolution;
	}
	auto& res = *new ExtGlRes_Sprite(*name, *tex,maxSize,shad);
	delete name;
	return res;
}
ExtGlRes_Font& ExtGlobalResourcesLoad::DeserRes_Font() {

	string* name = new string();
	GetValueByDef(DEF_RESOURCE_NAME, *name);
	FStreamExts::ClearPath(name);
	Font* font = nullptr;
	GetValueByDef(DEF_PATH, LineBuffer);
	FStreamExts::ClearPath(&LineBuffer);
	font = LoadFontByPath();
	auto& res = *new ExtGlRes_Font(*name, *font);
	delete name;
	return res;
}
ExtGlRes_Shader& ExtGlobalResourcesLoad::DeserRes_Shader() {

	string* name = new string();
	GetValueByDef(DEF_RESOURCE_NAME, *name);
	FStreamExts::ClearPath(name);
	Shader* shad = new Shader();
	GetValueByDef(DEF_PATH, LineBuffer);
	FStreamExts::ClearPath(&LineBuffer);
	shad=LoadShaderByPath();
	auto& res = *new ExtGlRes_Shader(*name, *shad);
	delete name;
	return res;
}

Texture*	ExtGlobalResourcesLoad::LoadTextureByPath() {

	FStreamExts::ClearPath(&LineBuffer);
	Texture* tex = new Texture();
	tex->loadFromFile(LineBuffer);
	return tex;
}
Font*		ExtGlobalResourcesLoad::LoadFontByPath(){

	FStreamExts::ClearPath(&LineBuffer);
	Font* font = new Font();
	font->loadFromFile(LineBuffer);
	return font;
}
Shader* ExtGlobalResourcesLoad::LoadShaderByPath() {

	FStreamExts::ClearPath(&LineBuffer);
	string shadPath = string(LineBuffer);
	Shader* shad = new Shader();
	GetValueByDef(DEF_SHADER_TYPE, LineBuffer);
	Shader::Type type;
	if (LineBuffer.find(SHADERTYPE_FRAG) != string::npos) {
		type = Shader::Fragment;
	}
	else if (LineBuffer.find(SHADERTYPE_VERT) != string::npos) {
		type = Shader::Vertex;
	}
	else if (LineBuffer.find(SHADERTYPE_GEO) != string::npos) {
		type = Shader::Geometry;
	}
	else
		throw exception("Cant get shader type");
	LineBuffer.clear();
	LineBuffer.append(shadPath);
	shad->loadFromFile(LineBuffer, type);
	return shad;
}

const Texture*	ExtGlobalResourcesLoad::GetTextureByName() const{
	ExtGlResource* res = ExternalGlobalResources::GetRes(LineBuffer);
	if (res == nullptr)
		return nullptr;
	return &dynamic_cast<ExtGlRes_Texture*>(res)->Tex;
}
const Font*		ExtGlobalResourcesLoad::GetFontByName() const{
	ExtGlResource* res = ExternalGlobalResources::GetRes(LineBuffer);
	if (res == nullptr)
		return nullptr;
	return &dynamic_cast<ExtGlRes_Font*>(res)->Font_;
}
Shader*	ExtGlobalResourcesLoad::GetShaderByName() const{
	ExtGlResource* res = ExternalGlobalResources::GetRes(LineBuffer);
	if (res == nullptr)
		return nullptr;
	return &dynamic_cast<ExtGlRes_Shader*>(res)->Shader_;
}

const string ExtGlobalResourcesLoad::GetFilePath() {
	return GLOBAL_RESOURCES_PATH;
}
const char ExtGlobalResourcesLoad::GetValuesDefEndSym() {
	return RESOURCE_DEF_END_SYM;
}
