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

		/// <summary>
		/// Default ctor initialization with parent's assigning
		/// </summary>
		/// <param name="localPos"></param>
		/// <param name="localScale"></param>
		void ctor_initialize_par(Vector2f localPos,Vector2f localScale) {

			AddOwnerAsChild();
			SetLocalScale(localScale);
			SetLocalPosition(localPos);
		}
		/// <summary>
		/// Default ctor initialization without parent
		/// </summary>
		/// <param name="globalPos"></param>
		/// <param name="globalScale"></param>
		void ctor_initialize_no_par(Vector2f globalPos, Vector2f globalScale) {

			SetGlobalScale(globalScale);
			SetGlobalPosition(globalPos);
		}

		void SetParent_inter(IHierarchyTrObj* parent) override {
			Parent = parent;
		}
	};
}