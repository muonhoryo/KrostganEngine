
#include <FractionsSystem.h>
#include <FStreamExts.h>

using namespace KrostganEngine::EntitiesControl;

void FractionsDeserializator::DeserializeFractions(const string& fractionsFilePath) {

	FractionsSystem::Unload();

	char* file = FStreamExts::ReadToEnd(fractionsFilePath);
	xml_document<>* doc = new xml_document<>();
	doc->parse<0>(file);
	vector<const Fraction*> fractions;
	FRACTION_INDEX index = 0;
	char* nodeName = nullptr;
	xml_node<>* serObj = doc->first_node()->first_node();
	const Fraction* frac = nullptr;
	while (serObj != nullptr) {

		nodeName = serObj->name();
		if (nodeName == DEF_TYPE_FRACTION) {

			fractions.push_back(&DeserializeFraction(*serObj, index));
		}

		serObj = serObj->next_sibling();
	}


	size_t fractionsCount = fractions.size();
	FractionsSystem::RelationsMatrix.resize(fractionsCount);
	for (auto& vec : FractionsSystem::RelationsMatrix) {
		vec.resize(fractionsCount);
	}
	FractionsSystem::Fractions = vector<Fraction>(fractionsCount);
	for (int i = 0;i < fractionsCount;++i) {
		FractionsSystem::Fractions[i] = *fractions[i];
		delete fractions[i];
	}


	serObj = doc->first_node()->first_node();
	const vector<Relation>* relations = nullptr;
	for (int i = 0;i < FractionsSystem::GetFractionsCount();++i) {

		nodeName = serObj->name();
		if (nodeName == DEF_TYPE_FRACTION) {

			relations = &DeserializeFractionRelations(*serObj);
			FractionsSystem::SetFractionRelation(i, *relations);
			delete relations;
		}

		serObj = serObj->next_sibling();
	}

	delete doc;
}
const Fraction& FractionsDeserializator::DeserializeFraction(xml_node<>& fractionNode, FRACTION_INDEX& index) {

	string name = "";
	Color color = Color::White;
	char* attrName = nullptr;
	xml_attribute<>* attr = fractionNode.first_attribute();
	while (attr != nullptr) {
		attrName = attr->name();
		if (attrName == DEF_FRACTION_NAME) {
			name = attr->value();
		}
		else if (attrName == DEF_FRACTION_COLOR) {
			color = Color(stoul(attr->value(), nullptr, 16));
		}

		attr = attr->next_attribute();
	}

	auto& frac = *new Fraction(index, name, color);
	++index;
	return frac;

}
const vector<Relation>& FractionsDeserializator::DeserializeFractionRelations(xml_node<>& fractionNode) {

	vector<Relation>& relations = *new vector<Relation>(FractionsSystem::GetFractionsCount());
	xml_node<>* serRel = fractionNode.first_node();
	xml_attribute<>* attr = nullptr;
	char* name = nullptr;
	FRACTION_INDEX index = INT_MAX;
	const Fraction* objFrac = nullptr;
	Relation rel = FractionsSystem::DEFAULT_RELATION;
	string* serValue = nullptr;
	while (serRel != nullptr) {

		attr = serRel->first_attribute();

		while (attr != nullptr) {
			name = attr->name();
			if (name == DEF_RELATION_OBJECT) {
				serValue = new string(attr->value());
				objFrac = FractionsSystem::GetFractionByName(*serValue);
				if (objFrac == nullptr)
					throw exception("Unknown fraction");

				delete serValue;
				index = objFrac->Index;
			}
			else if (name == DEF_RELATION_RELATION) {
				serValue = new string(attr->value());
				rel = RelationSerialization::GetRelationByName(*serValue);
				delete serValue;
			}

			attr = attr->next_attribute();
		}

		relations[index] = rel;
		
		serRel = serRel->next_sibling();
	}

	return relations;
}
//FRACTION_INDEX FractionsDeserializator::GetFractionIndex(xml_node<>& fractionNode) {
//	xml_attribute<>* attr = fractionNode.first_attribute();
//	char* name = nullptr;
//	while (attr != nullptr) {
//		name = attr->name();
//		if (name == DEF_FRACTION_NAME) {
//			string fracName = attr->value();
//			return FractionsSystem::
//		}
//	}
//
//	return INT16_MAX;
//}