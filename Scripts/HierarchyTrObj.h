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
		void ctor_initialize_par(Vector2f localPos=DEFAULT_POSITION,Vector2f localScale=DEFAULT_SCALE,float localRotation=0) {

			AddOwnerAsChild();
			SetLocalScale(localScale);
			SetLocalPosition(localPos);
			SetLocalRotation(localRotation);
		}
		/// <summary>
		/// Default ctor initialization without parent
		/// </summary>
		/// <param name="globalPos"></param>
		/// <param name="globalScale"></param>
		void ctor_initialize_no_par(Vector2f globalPos=DEFAULT_POSITION, Vector2f globalScale=DEFAULT_SCALE,float globalRotation=0) {

			SetGlobalScale(globalScale);
			SetGlobalPosition(globalPos);
			SetGlobalRotation(globalRotation);
		}

		void SetParent_inter(IHierarchyTrObj* parent) override {
			Parent = parent;
		}
	};
}