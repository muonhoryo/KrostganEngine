#pragma once

#include <TriggerZone.h>
#include <iostream>
#include <Engine.h>

using namespace std;
using namespace KrostganEngine::Physics;

namespace KrostganEngine::GameObjects {

	class TestTrigger : public TriggerZone {

	public:
		TestTrigger(Vector2f Pos) 
			:TriggerZone(*new Transformable()),
			COLLIDER(CircleCollShape(Pos,300)){

			SetGlobalPosition(Pos);
		}

		const ColliderShape& GetCollider() const override {

			return COLLIDER;
		}

		CircleCollShape COLLIDER;

	protected:
		vector<IPhysicalObject*>	OverlapAll() const override {

			return Engine::GetPhysicsEngine().OverlapCircle_All(COLLIDER.Center, COLLIDER.Radius, PhysicsLayer::Units);
		}
		bool						EnterTriggerCondition(const IPhysicalObject& inputObj) const override {
			return true;
		}

		void OnTriggerEnter(IPhysicalObject& obj) override {
			cout << "Enter trigger" << endl;
		}
		void OnTriggerExit(watch_ptr_handler_wr<IPhysicalObject>& obj) override{
			cout << "Exit trigger" << endl;
		}
	};
}