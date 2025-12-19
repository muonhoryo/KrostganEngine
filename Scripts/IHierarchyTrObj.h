#pragma once


#include <ITransformableObj.h>
#include <vector>
#include <CollectionsExts.h>

using namespace sf;
using namespace std;
using namespace KrostganEngine;

namespace KrostganEngine::Core {

	class IHierarchyTrObj;

	class IHierarchyTrObj : public virtual ITransformableObj {
	private:
		vector<IHierarchyTrObj*>	ChildObjs;
		bool				DesWithPar = true;

		void AddChild(IHierarchyTrObj& child);
		void RemoveChild(IHierarchyTrObj& child);

	public:
		virtual IHierarchyTrObj*		GetParent() const = 0;
		virtual const IHierarchyTrObj*	GetParent_c() const = 0;

		vector<IHierarchyTrObj*>::const_iterator	GetChildrenBegin() const;
		vector<IHierarchyTrObj*>::const_iterator	GetChildrenAfterEnd() const;
		size_t										GetChildrenCount() const;
		/// <summary>
		/// Return is object should be deleted with its parent or not
		/// </summary>
		/// <returns></returns>
		bool						GetDesWithParentState() const;

		void	DestroyChildren();
		/// <summary>
		/// Set is object should be deleted with its parent or not
		/// </summary>
		/// <param name="desWithPar"></param>
		void	SetDesWithParent(bool desWithPar);

		virtual void	SetParent(IHierarchyTrObj* parent) = 0;


		virtual ~IHierarchyTrObj(){}

	protected:
		IHierarchyTrObj(){}

		void AddOwnerAsChild();
		void RemoveOwnerAsChild();
		void SetChildrenPosition();
		void SetChildrenScale();
		void SetChildrenRotation();

		const vector<IHierarchyTrObj*>&	GetChildrenCopy() const;

		virtual void SetPosition_Inherit() = 0;
		virtual void SetScale_Inherit() = 0;
		virtual void SetRotation_Inherit() = 0;
		/// <summary>
		/// Directly set Parent field as the input value
		/// </summary>
		/// <param name="parent"></param>
		virtual void SetParent_inter(IHierarchyTrObj* parent) = 0;
	};
}