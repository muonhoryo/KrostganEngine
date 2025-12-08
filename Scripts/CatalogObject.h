#pragma once

#include <map>

using namespace std;

namespace KrostganEngine::Core {
	class CatalogObject {

	private:
		size_t		CatalogID;
		std::byte	SubcatalogID;		//SubcatalogID's contating currently doesn't work cause level loading system doesn't indexes object's sub info during loading

	public:
		size_t GetCatalogID() const {
			return CatalogID;
		}
		std::byte GetSubcatalogID() const {
			return SubcatalogID;
		}

	protected:
		CatalogObject(size_t CatalogID, std::byte SubcatalogID)
			:CatalogID(CatalogID), SubcatalogID(SubcatalogID) {}

		CatalogObject();
	};
}