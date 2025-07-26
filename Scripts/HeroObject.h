#pragma once

#include <UnitObject.h>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace KrostganEngine::EntitiesControl;

namespace KrostganEngine::GameObjects {
	
	class HeroObject;

	class HeroDeathModule : public UnitDeathModule{
	public:
		HeroDeathModule(Entity& Owner) : UnitDeathModule(Owner) {

		}

		void Death() override;
	};

	struct HeroObjectCtorParams : public UnitObjectCtorParams{

		HeroObjectCtorParams():UnitObjectCtorParams(){}
		HeroObjectCtorParams(const UnitObjectCtorParams& params):HeroObjectCtorParams(reinterpret_cast<const HeroObjectCtorParams&>(params))
		{}

		void Init_DeathModule(Entity& owner) override {
			DeathModule = new HeroDeathModule(owner);
		}
	};
	class HeroObject:public UnitObject {
	public:
		HeroObject(HeroObjectCtorParams& params);
		virtual ~HeroObject();
	};
}