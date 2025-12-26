#pragma once

#include <ColliderShapes.h>
#include <rapidxml.hpp>

using namespace rapidxml;

namespace KrostganEngine::Physics {
	class ColliderDeserializer final {

	private:
		ColliderDeserializer(){}
		~ColliderDeserializer(){}

	public:
		static ColliderShape& DeserializeCollider(const xml_node<>& serColl);

	private:
		static ColliderShape& DeserializeColl_Circle(const xml_node<>& serColl, xml_attribute<>* attrBuffer);
		static ColliderShape& DeserializeColl_AABB(const xml_node<>& serColl, xml_attribute<>* attrBuffer);
	};

	struct ColliderSerDefNames final {

		static inline const string TYPE_DEF = "Type";
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