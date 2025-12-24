#pragma once

#include <ColliderShapes.h>

namespace KrostganEngine::Physics {
	class ColliderDeserializer final {

	private:
		ColliderDeserializer(){}
		~ColliderDeserializer(){}

	public:
		static ColliderShape& DeserializeCollider(const string& serColl);
	};

	struct ColliderSerDefNames final {

		static inline const string TYPE_DEF = "CollisionType";
		static inline const string CENTER = "Center";
		static inline const string RADIUS = "Radius";
		//static inline const string COLLISION_MIN		= "Min";
		//static inline const string COLLISION_MAX		= "Max";
		static inline const string HEIGHT = "Height";
		static inline const string WIDTH = "Width";

		static inline const string TYPE_CIRCLE = "Cirle";
		static inline const string TYPE_AABB = "AABB";
		static inline const string TYPE_EMPTY = "Empty";

	private:
		ColliderSerDefNames(){}
		~ColliderSerDefNames(){}
	};
}