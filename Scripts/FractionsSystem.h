#pragma once

#include <SFML/Graphics.hpp>
#include <map> 
#include <string>
#include <vector>
#include <CollectionsExts.h>
#include <rapidxml.hpp>
#include <forward_list>

using namespace std;
using namespace sf;
using namespace rapidxml;
using namespace KrostganEngine;

#define FRACTION_INDEX unsigned int

namespace KrostganEngine::EntitiesControl {

	class FractionsDeserializator;
	class FractionsSystem;

	enum class Relation{
		None	= -1,
		Ally	= 1,
		Neutral	= 2,
		Enemy	= 4,
		All		= ~0 
	};

	struct Fraction final {

		FRACTION_INDEX Index;
		string Name;
		string ProgramName;
		Color FracColor;

		Fraction();
		Fraction(const FRACTION_INDEX Index, const string& Name, Color FracColor = Color::White);
		Fraction(const Fraction& copy);

		Fraction& operator = (const Fraction& frac);
	};

	struct FractionWrapper final {

		FractionWrapper();
		FractionWrapper(const Fraction& Fraction_);
		FractionWrapper(FRACTION_INDEX fracIndex);
		FractionWrapper(const string& programName);
		FractionWrapper(const FractionWrapper& copy);

		const Fraction& Fraction_;

		Relation GetRelationTo(const Fraction& objectFrac) const;
		Relation GetRelationTo(FRACTION_INDEX objectFracIndex) const;
		Relation GetRelationToPlayer() const;

		bool operator == (const FractionWrapper& other) const;
		bool operator < (const FractionWrapper& other) const;
		bool operator > (const FractionWrapper& other) const;
		bool operator <= (const FractionWrapper& other) const;
		bool operator >= (const FractionWrapper& other) const;
		operator int() const;
		FractionWrapper& operator = (const FractionWrapper& copy);
	};


	
	class FractionsSystem final{

	private:
		static inline vector<Fraction> Fractions = vector<Fraction>();
		/// <summary>
		/// 1st dimension of array - subject's fraction. 
		/// 2st dimension of array - object's fraction
		/// </summary>
		static inline vector<vector<Relation>> RelationsMatrix = vector<vector<Relation>>();

	public:
		static Relation			GetRelation					(const Fraction& subjectFrac, const Fraction& objectFrac);
		/// <summary>
		/// Return DEFAULT_RELATION if any of input indexes are not compared with created fractions
		/// </summary>
		/// <param name="subjectFrac"></param>
		/// <param name="objectFrac"></param>
		/// <returns></returns>
		static Relation			GetRelation					(FRACTION_INDEX subjectFracIndex, FRACTION_INDEX objectFracIndex);

		static Relation			GetRelationToPlayer			(const Fraction& subjectFrac);
		/// <summary>
		/// Return DEFAULT_RELATION if any of input indexes are not compared with created fractions
		/// </summary>
		/// <param name="subjectFrac"></param>
		/// <param name="objectFrac"></param>
		/// <returns></returns>
		static Relation			GetRelationToPlayer			(FRACTION_INDEX subjectFracIndex);
		/// <summary>
		/// Return nullptr if haven't fraction with input index
		/// </summary>
		/// <param name="fracIndex"></param>
		/// <returns></returns>
		static const Fraction*	GetFraction					(FRACTION_INDEX fracIndex);
		/// <summary>
		/// Return nullptr if haven't fraction with input name
		/// </summary>
		/// <param name="fracIndex"></param>
		/// <returns></returns>
		static const Fraction*	GetFractionByProgramName	(const string& fracProgramName);
		/// <summary>
		/// Return nullptr if haven't fraction with input name
		/// </summary>
		/// <param name="fracIndex"></param>
		/// <returns></returns>
		static const Fraction*	GetFractionByName			(const string& fracName);

		static FractionWrapper GetDefaultFraction();
		static FractionWrapper GetPlayerFraction();


		static const size_t		GetFractionsCount			();

		static string& GetProgramName(const string& name);
		static void Unload();


		static void AddFraction(const Fraction& frac);
		static void SetFractionRelation(const Fraction& fraction, const vector<Relation>& fracRelations);
		static void SetFractionRelation(FRACTION_INDEX fracIndex, const vector<Relation>& fracRelations);

		static inline const FRACTION_INDEX DEFAULT_FRACTION = 0;
		static inline const FRACTION_INDEX PLAYER_FRACTION = 1;
		static inline const Relation DEFAULT_RELATION = Relation::Neutral;

	private:
		friend class FractionsDeserializator;

		struct FractionsPredicate_ByProgName : public CollectionsExts::Predicate<const Fraction&>{

			FractionsPredicate_ByProgName(const string& Name):
				Name(Name){}

			const string& Name;

			bool Condition(const Fraction& input) const override {
				return input.ProgramName == Name;
			}
		};
	};

	class FractionsDeserializator final{

	public:
		static void						DeserializeFractions(const string& fractionsFilePath);

		static inline const string DEF_TYPE_FRACTION		= "Fraction";
		static inline const string DEF_TYPE_RELATION		= "Relation";
		static inline const string DEF_FRACTION_NAME		= "Name";
		static inline const string DEF_FRACTION_COLOR		= "Color";
		static inline const string DEF_RELATION_OBJECT		= "Fraction";
		static inline const string DEF_RELATION_RELATION	= "Relation";

	private:
		static const Fraction& DeserializeFraction(xml_node<>& fractionNode, FRACTION_INDEX& index);
		static const vector<Relation>& DeserializeFractionRelations(xml_node<>& fractionNode);
		//static FRACTION_INDEX GetFractionIndex(xml_node<>& fractionNode);
	};

	class RelationSerialization final {

	public:
		static inline const map<string, Relation> RelationNames{

			pair{"Ally", Relation::Ally},
			pair{"Neutral", Relation::Neutral},
			pair{"Enemy", Relation::Enemy},
			pair{"All", Relation::All}
		};

		/// <summary>
		/// If cannot parse by name (return Relation::None on first try), try parse by int-value of relation
		/// </summary>
		static Relation DeserializeRelation(const string& rel);
		/// <summary>
		/// Return Relation::None if cannot parse by name
		/// </summary>
		static Relation GetRelationByName(const string& name);
		/// <summary>
		/// Return Relation::None if cannot parse by name
		/// </summary>
		static Relation GetRelationByInt(int rel);
	};
}