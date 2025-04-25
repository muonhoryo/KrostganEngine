#pragma once

#include <GameObjects.h>

namespace KrostganEngine {
	namespace GameObjects {
		class UnitObject :public GameObject {
		public: 
			UnitObject(const Texture& RenTexture, Vector2f RenOffset, Vector2f Position,float Size);
		};
	}
}