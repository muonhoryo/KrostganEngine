
#include <FadingVisualEff_Des.h>

using namespace sf;
using namespace KrostganEngine::Visual;

FadingVisualEff_Des::FadingVisualEff_Des(float LifeTime, IColoredObject& Owner) 
	:FadingVisualEffect(LifeTime,Owner){

}

void FadingVisualEff_Des::Update() {

	if (Fade()) {

		delete& Owner;
		delete this;
	}
}