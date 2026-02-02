
#include <ColliderDeserializer.h>
#include <ITransformableObj.h>
#include <_Extensions.h>

using namespace rapidxml;
using namespace KrostganEngine;
using namespace KrostganEngine::Physics;

ColliderShape& ColliderDeserializer::DeserializeCollider(const xml_node<>& serColl) {
	
	xml_attribute<>* attr = serColl.first_attribute();
	
	if (attr->name() != ColliderSerDefNames::TYPE_DEF)
		throw exception("In collider's definition type-attribute should be first");

	char* attrValue = attr->value();

	if (attrValue == ColliderSerDefNames::TYPE_CIRCLE) {

		return DeserializeColl_Circle(serColl, attr);
	}
	else if (attrValue == ColliderSerDefNames::TYPE_AABB) {

		return DeserializeColl_AABB(serColl, attr);
	}
	else if (attrValue == ColliderSerDefNames::TYPE_EMPTY) {
		return *new EmptyShape();
	}
	else
		throw exception("Unknown type of collider");
}

ColliderShape& ColliderDeserializer::DeserializeColl_Circle(const xml_node<>& serColl, xml_attribute<>* attrBuffer) {

	attrBuffer = attrBuffer->next_attribute();
	if (attrBuffer == nullptr)
		return *new CircleCollShape(DEFAULT_POSITION, 1);

	char* attrName = nullptr;

	Vector2f center = DEFAULT_POSITION;
	float radius = 1;

	while (attrBuffer != nullptr) {

		attrName = attrBuffer->name();
		if (attrName == ColliderSerDefNames::CENTER) {
			center = ParseVec2f(string(attrBuffer->value()));
		}
		else if (attrName == ColliderSerDefNames::RADIUS) {
			radius = stof(attrBuffer->value());
		}

		attrBuffer = attrBuffer->next_attribute();
	}

	return *new CircleCollShape(center, radius);
}

ColliderShape& ColliderDeserializer::DeserializeColl_AABB(const xml_node<>& serColl, xml_attribute<>* attrBuffer) {

	attrBuffer = attrBuffer->next_attribute();
	if (attrBuffer == nullptr)
		return *new AABBCollShape(DEFAULT_POSITION, DEFAULT_POSITION);

	char* attrName = nullptr;

	Vector2f center = DEFAULT_POSITION;
	float width = 1;
	float height = 1;

	while (attrBuffer != nullptr) {

		attrName = attrBuffer->name();
		if (attrName == ColliderSerDefNames::CENTER) {
			center = ParseVec2f(string(attrBuffer->value()));
		}
		else if (attrName == ColliderSerDefNames::WIDTH) {
			width = stof(attrBuffer->value());
		}
		else if (attrName == ColliderSerDefNames::HEIGHT) {
			height = stof(attrBuffer->value());
		}

		attrBuffer = attrBuffer->next_attribute();
	}

	return AABBCollShape::InstanceBy_CenterAndSize(center, width, height);
}