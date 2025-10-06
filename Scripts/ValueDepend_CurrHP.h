#pragma once

#include <IEntityUIDependency.h>
#include <ValueDependency.h>
#include <string>

using namespace std;
using namespace KrostganEngine;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::GameObjects;

namespace KrostganEngine::UI {

	class CurrHPDepend_toTxt final : public IUIDependency, public IEntityUIDependency {
	
	private:
		class OnHPChangedSubsc;

	private:
		watch_ptr_handler_wr<Entity>* Target = nullptr;
		OnHPChangedSubsc* HPChangeSubs;
		UIText& Subject;
		const string_view& Format;

		struct OnHPChangedSubsc final : public INoArgsEventSubscriber {
			OnHPChangedSubsc(CurrHPDepend_toTxt& Owner)
				:Owner(Owner)
			{}
			void Execute() override {
				Owner.Update();
			}
		private:
			CurrHPDepend_toTxt& Owner;
		};

	public:
		virtual ~CurrHPDepend_toTxt() {
			delete HPChangeSubs;
		}
		CurrHPDepend_toTxt
		(watch_ptr_handler_wr<Entity>* Target,
			UIText& Subject,
			const string& Format = "{}")
			:Target(Target),
			Format(*new string_view(Format)),
			Subject(Subject){

			HPChangeSubs = new OnHPChangedSubsc(*this);
			if (Target != nullptr)
				ChangeDepTarget(Target->GetPtr_t());
			else
				ChangeDepTarget(nullptr);
		}

		void ChangeDepTarget(Entity* target) {

			if (IsValueRefValid()) {
				auto tarRef = Target->GetPtr_t();
				if (tarRef != nullptr)
					tarRef->GetHPModule().ChangedHPEvent.Remove((INoArgsEventSubscriber&)*HPChangeSubs);
				delete Target;
			}
			if (target != nullptr) {
				target->GetHPModule().ChangedHPEvent.Add((INoArgsEventSubscriber&)*HPChangeSubs);
				auto& ptr = target->GetPtr();
				Target = new watch_ptr_handler_wr<Entity>(ptr);
				delete& ptr;
				SetByObject();
			}
			else {
				Target = nullptr;
				SetDefault();
			}
		}

	protected:
		void Update() override {
			if (IsValueRefValid())
				SetByObject();
			else
				SetDefault();
		}

	private:
		size_t	GetValue() const 
			{ return Target->GetPtr_t_c()->GetHPModule().GetCurrentHP(); }
		bool	IsValueRefValid() const {
			return Target != nullptr && Target->GetPtr_t_c() != nullptr;
		}
		string	FormatStr(string obj) const {
			string str = vformat(Format, make_format_args(obj));
			return str; 
		}
		string	FormatField() const { 
			string str = std::to_string(GetValue());
			return FormatStr(str); 
		}
		string	GetDefault() const 
			{ return FormatStr(""); }
		void	SetDefault() 
			{ Subject.text->setString(GetDefault()); }
		void	SetByObject() 
			{ Subject.text->setString(FormatField()); }
	};
}