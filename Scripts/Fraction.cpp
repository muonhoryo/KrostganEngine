
#include <FractionsSystem.h>

using namespace KrostganEngine::EntitiesControl;

Fraction::Fraction()
	:Index(INT16_MAX){

}
Fraction::Fraction(const FRACTION_INDEX Index, const string& Name, Color FracColor)
	:Index(Index),
	Name(Name),
	FracColor(FracColor),
	ProgramName(FractionsSystem::GetProgramName(Name)) {

	if (FractionsSystem::GetFractionByProgramName(ProgramName) != nullptr)
		throw exception("The fraction is already created");
}
Fraction::Fraction(const Fraction& copy)
	:Index(copy.Index),
	Name(copy.Name),
	ProgramName(copy.ProgramName),
	FracColor(copy.FracColor) {

}

Fraction& Fraction::operator = (const Fraction& frac) {
	Index = frac.Index;
	Name = frac.Name;
	ProgramName = frac.ProgramName;
	FracColor = frac.FracColor;
	return *this;
}