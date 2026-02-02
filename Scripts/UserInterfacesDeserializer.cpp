
#include <UserInterfacesDeserializer.h>
#include <fstream>
#include <_Extensions.h>

using namespace std;
using namespace KrostganEngine;
using namespace KrostganEngine::Core;

UserInterfacesDeserializer::UserInterfacesDeserializer() 
	:ValuesListDeserializer(){

	if (Singleton != nullptr)
		delete Singleton;
	Singleton = this;
}
UserInterfacesDeserializer::~UserInterfacesDeserializer() {
	Singleton = nullptr;
}

void UserInterfacesDeserializer::Deserialize() {
	DeserializeValues();

	string serLay;
	xml_document<>* layout=nullptr;

	for (auto p : StrValuesArr) {

		layout = new xml_document<>();
		FStreamExts::ClearPath(p->Value);
		char* file = FStreamExts::ReadToEnd(p->Value);
		layout->parse<0>(file);
		Layouts.push_back(new XMLLayout(p->Name, layout));
	}
}
void UserInterfacesDeserializer::Clear() {
	
	for (auto p : StrValuesArr) {
		delete p;
	}
	StrValuesArr.clear();
	for (auto p : Layouts) {
		delete p;
	}
	Layouts.clear();
}
const xml_document<>& UserInterfacesDeserializer::GetLayout(const string& name) const {

	UserInterfacesDeserializer::XMLLayout* lay=nullptr;
	lay = *CollectionsExts::Get_c
		<vector<UserInterfacesDeserializer::XMLLayout*>,
		UserInterfacesDeserializer::XMLLayout*>
			(Layouts,GetLayoutCondition(name));
	if (lay == nullptr)
		throw exception("Cannot find layout");
	return *lay->Layout;
}

UserInterfacesDeserializer* UserInterfacesDeserializer::GetInstance() {
	return Singleton;
}

const string UserInterfacesDeserializer::GetFilePath() {
	return UI_LAYOUTS_PATH;
}
const char UserInterfacesDeserializer::GetValuesDefEndSym() {
	return UI_LAYOUTS_END_SYM;
}