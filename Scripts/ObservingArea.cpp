
#include <ObservingArea.h>

using namespace KrostganEngine::GameObjects;

ObservingArea::ObservingArea(float ObservingRange, WorldTransfObj& Parent) 
	:WorldTransfObj(*new Transformable(), Parent),
		ObservingRange(ObservingRange)
{}
ObservingArea::ObservingArea(float ObservingRange) 
	:WorldTransfObj(*new Transformable()),
		ObservingRange(ObservingRange)
{}
ObservingArea::~ObservingArea() {

}

float ObservingArea::GetObservingRange() const {
	return ObservingRange;
}
Fraction ObservingArea::GetFraction()const {
	return Fraction::Neutral;
}