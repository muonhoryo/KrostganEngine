#pragma once

#include <WorldTransfObj.h>
#include <IPhysicalObject.h>
#include <forward_list>
#include <ICallbackRec_Upd.h>
#include <watch_ptr_predicates.h>

using namespace std;
using namespace KrostganEngine::Physics;

namespace KrostganEngine::GameObjects {

	class TriggerZone : public WorldTransfObj, public virtual ICallbackRec_Upd {

	public:
		virtual ~TriggerZone();

		virtual const ColliderShape& GetCollider() const = 0;

		void Update(CallbackRecArgs_Upd args) override;

		forward_list<watch_ptr_handler_wr<IPhysicalObject>*>::const_iterator GetEnteredObjs_BeforeBegin() const;
		forward_list<watch_ptr_handler_wr<IPhysicalObject>*>::const_iterator GetEnteredObjs_Begin() const;
		forward_list<watch_ptr_handler_wr<IPhysicalObject>*>::const_iterator GetEnteredObjs_End() const;

	protected:
		TriggerZone(Transformable& Owner, WorldTransfObj& Parent);
		TriggerZone(Transformable& Owner);

		virtual vector<IPhysicalObject*>	OverlapAll() const = 0;
		virtual bool						EnterTriggerCondition(const IPhysicalObject& inputObj) const = 0;

		virtual void OnTriggerEnter	(IPhysicalObject& obj){}
		virtual void OnTriggerStay	(IPhysicalObject& obj){}
		virtual void OnTriggerExit	(watch_ptr_handler_wr<IPhysicalObject>& obj){}

	private:
		void Update_DeleteNull();
		void Update_DeleteExited(const vector<IPhysicalObject*>& inputObjs);
		void Update_AddEnteredObjs(const vector<IPhysicalObject*>& inputObjs);

		forward_list<watch_ptr_handler_wr<IPhysicalObject>*> EnteredObjects;

		static inline const w_ptr_han_pred_eqByOwners<watch_ptr_handler_wr<IPhysicalObject>> InstanceEqComparator;
	};
}