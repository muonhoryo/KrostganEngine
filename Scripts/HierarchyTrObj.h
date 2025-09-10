#pragma once

#include <IHierarchyTrObj.h>
#include <TransformableObj.h>

namespace KrostganEngine::Core {
	class HierarchyTrObj : public virtual IHierarchyTrObj,public TransformableObj {

	private:
		IHierarchyTrObj* Parent = nullptr;

	public:
		virtual ~HierarchyTrObj() {

			auto& cCopy = GetChildrenCopy();
			for (auto ch : cCopy) {
				if (ch->GetDesWithParentState())
					delete ch;
				else
					ch->SetParent(nullptr);
			}
			delete& cCopy;
			if (GetParent() != nullptr)
				RemoveOwnerAsChild();
		}

		IHierarchyTrObj* GetParent() const override final {
			return Parent;
		}
		const IHierarchyTrObj* GetParent_c() const override final{
			return Parent;
		}

	protected:
		HierarchyTrObj(Transformable& Owner)
			:TransformableObj(Owner){}

		HierarchyTrObj(Transformable& Owner, IHierarchyTrObj& Parent)
			:TransformableObj(Owner),
			Parent(&Parent)
		{}

		void SetParent_inter(IHierarchyTrObj* parent) override {
			Parent = parent;
		}
	};
}