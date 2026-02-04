
#include <FractionsSystem.h>
#include <FStreamExts.h>

using namespace KrostganEngine::EntitiesControl;

Relation RelationSerialization::DeserializeRelation(const string& rel) {

		Relation relation = GetRelationByName(rel);
	
		if (relation == Relation::None) {
			relation = GetRelationByInt(stoi(rel));
		}
	
		return relation;
}
Relation RelationSerialization::GetRelationByName(const string& name) {

	string clName = name;
	FStreamExts::ClearPath(clName);
	Relation rel;

	auto it = RelationNames.find(clName);

	if (it == RelationNames.end())
		rel = Relation::None;
	else
		rel = (*it).second;
	return rel;
}
Relation RelationSerialization::GetRelationByInt(int rel) {
	return (Relation)rel;
}