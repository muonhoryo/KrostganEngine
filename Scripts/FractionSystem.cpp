
#include <FractionsSystem.h>
#include <FStreamExts.h>
#include <iostream>

using namespace sf;
using namespace std;
using namespace KrostganEngine;
using namespace KrostganEngine::EntitiesControl;

Relation FractionsSystem::GetRelation(const Fraction& subjectFrac, const Fraction& objectFrac) {
	return GetRelation(subjectFrac.Index, objectFrac.Index);
}
Relation FractionsSystem::GetRelation(FRACTION_INDEX subjectFracIndex, FRACTION_INDEX objectFracIndex) {
	if (subjectFracIndex >= Fractions.size() || objectFracIndex >= Fractions.size())
		return DEFAULT_RELATION;

	return RelationsMatrix[subjectFracIndex][objectFracIndex];
}
Relation FractionsSystem::GetRelationToPlayer(const Fraction& subjectFrac) {
	return GetRelationToPlayer(subjectFrac.Index);
}
Relation FractionsSystem::GetRelationToPlayer(FRACTION_INDEX subjectFracIndex) {
	if (subjectFracIndex >= Fractions.size())
		return DEFAULT_RELATION;

	return RelationsMatrix[subjectFracIndex][PLAYER_FRACTION];
}
const Fraction* FractionsSystem::GetFraction(FRACTION_INDEX fracIndex) {
	if (fracIndex >= Fractions.size())
		return nullptr;

	return &Fractions[fracIndex];
}
const Fraction* FractionsSystem::GetFractionByProgramName(const string& fracProgramName) {

	auto predicate = FractionsPredicate_ByProgName(fracProgramName);
	return CollectionsExts::Get(Fractions, predicate);
}
const size_t FractionsSystem::GetFractionsCount() {
	return RelationsMatrix.size();
}
const Fraction* FractionsSystem::GetFractionByName(const string& fracName) {
	string& programName = GetProgramName(fracName);
	const Fraction* frac = GetFractionByProgramName(programName);
	delete& programName;
	return frac;
}

FractionWrapper FractionsSystem::GetDefaultFraction() {
	return FractionWrapper(*FractionsSystem::GetFraction(DEFAULT_FRACTION));
}
FractionWrapper FractionsSystem::GetPlayerFraction() {
	return FractionWrapper(*FractionsSystem::GetFraction(PLAYER_FRACTION));
}

string& FractionsSystem::GetProgramName(const string& name) {

	string& programName = *new string(name);

	int nameSize = programName.size();
	char* nameData = programName.data();

	for (int i = 0;i < nameSize;++i) {

		*nameData = tolower(*nameData);
		++nameData;
	}
	return programName;
}

void FractionsSystem::Unload() {
	Fractions = vector<Fraction>();
	RelationsMatrix = vector<vector<Relation>>();
}

void FractionsSystem::AddFraction(const Fraction& frac) {

	if (GetFractionByProgramName(frac.ProgramName) != nullptr)
		return;

	size_t oldMatrixSize = RelationsMatrix.size();
	size_t newMatrixSize = oldMatrixSize + 1;
	for (auto& relsArr : RelationsMatrix) {

		relsArr.resize(newMatrixSize);
		relsArr[oldMatrixSize] = DEFAULT_RELATION;
	}
	RelationsMatrix.resize(newMatrixSize);
	RelationsMatrix[oldMatrixSize].resize(newMatrixSize);
	for (int i = 0;i < newMatrixSize;++i) {
		RelationsMatrix[oldMatrixSize][i] = DEFAULT_RELATION;
	}
	Fractions.push_back(frac);
}
void FractionsSystem::SetFractionRelation(const Fraction& fraction, const vector<Relation>& fracRelations) {
	SetFractionRelation(fraction.Index, fracRelations);
}
void FractionsSystem::SetFractionRelation(FRACTION_INDEX fracIndex, const vector<Relation>& fracRelations) {

	size_t size = GetFractionsCount();

	if (fracRelations.size() != size)
		throw exception("fracRelations' size must be equal to RelationsMatrix's size");
	if (fracIndex >= size)
		throw exception("Index out of range");

	for (int i = 0; i < size;++i) {
		RelationsMatrix[fracIndex][i] = fracRelations[i];
	}
}