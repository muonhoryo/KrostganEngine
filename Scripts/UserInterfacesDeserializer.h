#pragma once

#include <string>
#include <ValuesListDeserializer.h>
#include <rapidxml.hpp>
#include <CollectionsExts.h>

using namespace std;
using namespace rapidxml;

namespace KrostganEngine::Core {
	/// <summary>
	/// Read every user interface XML-layouts by pathes, which is written in file of layouts.
	/// XML-layouts are stored until deserialized is cleared.
	/// </summary>
	class UserInterfacesDeserializer final : public ValuesListDeserializer{

	public:
		UserInterfacesDeserializer();
		~UserInterfacesDeserializer();

		void					Deserialize();
		void					Clear();
		const xml_document<>&	GetLayout(const string& name) const;

		static UserInterfacesDeserializer* GetInstance();

	protected:
		const string GetFilePath() override;
		const char GetValuesDefEndSym() override;


	private:
		struct XMLLayout {
			XMLLayout(const string& Name, xml_document<>* Layout)
				:Name(string(Name)), Layout(Layout)
			{}
			~XMLLayout() {
				delete Layout;
			}

			string Name;
			xml_document<>* Layout;
		};
		struct GetLayoutCondition : public CollectionsExts::Predicate<XMLLayout* const&> {
			GetLayoutCondition(const string& name)
				:name(name){}

			const string& name;

			bool Condition(XMLLayout* const& input) const override {
				return input->Name == name;
			}
		};

		static inline const string UI_LAYOUTS_PATH = "UILayouts.txt";
		static inline const char UI_LAYOUTS_END_SYM = ':';

		vector<XMLLayout*> Layouts;

		static inline UserInterfacesDeserializer* Singleton=nullptr;
	};
}