
#include <FractionsSystem.h>

using namespace KrostganEngine::EntitiesControl;

FractionWrapper::FractionWrapper()
	:Fraction_(*FractionsSystem::GetFraction(FractionsSystem::DEFAULT_FRACTION)){}
FractionWrapper::FractionWrapper(const Fraction& Fraction_)
	:Fraction_(Fraction_)
{}
FractionWrapper::FractionWrapper(FRACTION_INDEX fracIndex)
	:Fraction_(*FractionsSystem::GetFraction(fracIndex))
{}
FractionWrapper::FractionWrapper(const string& programName)
	:Fraction_(*FractionsSystem::GetFractionByProgramName(programName))
{}
FractionWrapper::FractionWrapper(const FractionWrapper& copy)
	:Fraction_(copy.Fraction_){}

Relation FractionWrapper::GetRelationTo(const Fraction& objectFrac) const {
	return FractionsSystem::GetRelation(Fraction_, objectFrac);
}
Relation FractionWrapper::GetRelationTo(FRACTION_INDEX objectFracIndex) const {
	return FractionsSystem::GetRelation(Fraction_.Index, objectFracIndex);
}
Relation FractionWrapper::GetRelationToPlayer() const {
	return FractionsSystem::GetRelationToPlayer(Fraction_);
}

bool FractionWrapper::operator == (const FractionWrapper& other) const {
	return &Fraction_ == &other.Fraction_;
}
bool FractionWrapper::operator < (const FractionWrapper& other) const {
	return Fraction_.Index < other.Fraction_.Index;
}
bool FractionWrapper::operator > (const FractionWrapper& other) const{
	return Fraction_.Index > other.Fraction_.Index;
}
bool FractionWrapper::operator <= (const FractionWrapper& other) const {
	return Fraction_.Index <= other.Fraction_.Index;
}
bool FractionWrapper::operator >= (const FractionWrapper& other) const {
	return Fraction_.Index >= other.Fraction_.Index;
}
FractionWrapper::operator int() const {
	return (int)Fraction_.Index;
}
FractionWrapper& FractionWrapper::operator = (const FractionWrapper& copy) {
	int* ref = (int*)this;
	auto inputRef = &copy.Fraction_;
	*ref = (int)inputRef;
	return *this;
}