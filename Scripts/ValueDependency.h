#pragma once

#include <UIText.h>
#include <format>

using namespace std;
using namespace KrostganEngine::UI;

namespace KrostganEngine::UI {

	class IUIDependency {
	public:
		virtual ~IUIDependency() {}

	protected:
		IUIDependency(){}

		virtual void Update() = 0;
	};

	template<typename TObject>
	class ValueDependency_toTxt : public IUIDependency {

	protected:
		UIText& Subject;
		TObject const* Object;
		const string_view& Format;

		ValueDependency_toTxt(UIText& Subject, TObject const* Object,const string& Format="{}")
			:IUIDependency(),
			Subject(Subject),
			Object(Object),
			Format(*new string_view(Format))
		{}

		virtual bool	IsValueRefValid		() const					{ return true; }
		virtual string	FormatStr			(string obj) const			{ return vformat(Format, make_format_args(obj));}
		string			FormatStr			(TObject const& obj) const	{ return FormatStr(to_string(obj)); }
		virtual string	GetDefault			() const					{ return FormatStr("0"); }
		void	SetDefault	() { Subject.SetString(GetDefault()); }
		void	SetByObject() { Subject.SetString(FormatStr(*Object)); }
		void Update() override{
			if (IsValueRefValid())
				SetByObject();
			else
				SetDefault();
		}

	};
}