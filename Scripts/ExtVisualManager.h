#pragma once

#include <map>
#include <_CoreEntitiesControl.h>
#include <OrderTargetsVisualizer.h>
#include <_Events.h>

using namespace std;
using namespace KrostganEngine;
using namespace KrostganEngine::EntitiesControl;

namespace KrostganEngine::Visual {
	class OrderTargsVisManager {
	private:
		class AddEntitySubscriber :public IEventSubscriber<ISelectableEntity> {
		public:
			AddEntitySubscriber(OrderTargsVisManager& Owner);

			void Execute(ISelectableEntity& args) override;

		private:
			OrderTargsVisManager& Owner;
		};
		class RemoveEntitySubscriber :public IEventSubscriber<ISelectableEntity> {
		public:
			RemoveEntitySubscriber(OrderTargsVisManager& Owner);

			void Execute(ISelectableEntity& args) override;

		private:
			OrderTargsVisManager& Owner;
		};
		class ClearListSubscriber :public INoArgsEventSubscriber {
		public:
			ClearListSubscriber(OrderTargsVisManager& Owner);

			void Execute() override;

		private:
			OrderTargsVisManager& Owner;
		};

	public:
		OrderTargsVisManager();
		~OrderTargsVisManager();

	private:
		map<Entity*, OrderTargetsVisualizer*> EntitiesTargetViss;
		IEventSubscriber<ISelectableEntity>* AddSub;
		IEventSubscriber<ISelectableEntity>* RemSub;
		INoArgsEventSubscriber* ClearSub;

		void TryInsertEntity(ISelectableEntity* ent);
		void TryRemoveEntity(ISelectableEntity* ent);
		void Clear();

		void Initialize_EntitiesTargetViss();
	};

	class ExtVisualManager {

	public:
		ExtVisualManager();
		~ExtVisualManager();

	private:
		OrderTargsVisManager OrderTargetsVisual;
	};
}