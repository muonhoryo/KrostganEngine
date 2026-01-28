#pragma once

#include <SFML/Graphics.hpp>
#include <map> 
#include <string>

using namespace std;
using namespace sf;

namespace KrostganEngine::EntitiesControl {
	enum class Fraction {
		Neutral,
		Player,
		Enemy
	};

	enum class Relation {
		None	= -1,
		Ally	= 1,
		Neutral	= 2,
		Enemy	= 4,
		All = ~0 
	};

	struct RelationSerialization {

		static inline const map<string, Relation> RelationNames{

			pair{"Ally", Relation::Ally},
			pair{"Neutral", Relation::Neutral},
			pair{"Enemy", Relation::Enemy},
			pair{"All", Relation::All}
		};

		static Relation GetRelationByName(const string& name);
		static Relation DeserializeRelation(const string& rel);
	};

	
	class FractionsSystem {
	public:
		static Relation			GetRelation					(Fraction objFrac,Fraction subjFrac);
		static Relation			GetRelationToPlayer			(Fraction objFrac);
		static Color			GetRelationColor			(Relation rel);
		static Color			GetRelationToPlayerColor	(Fraction objFrac);
		static const string&	GetNameOfFraction			(Fraction frac);
		static Fraction			GetFractionByName			(const string& name);

		static inline const map<string, Fraction>& FractionNames = *new map<string, Fraction>
		{
			pair{ "player",Fraction::Player },
			pair{ "neutral",Fraction::Neutral },
			pair{ "enemy",Fraction::Enemy }
		};
		static inline const Fraction DEFAULT_FRAC = Fraction::Neutral;
		static inline const Relation DefaultRel = Relation::Neutral;

	private:
		FractionsSystem();
	};
}