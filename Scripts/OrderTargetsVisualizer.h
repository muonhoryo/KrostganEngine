#pragma once

#include <CoreUIUX.h>
#include <CoreGameObjects.h>
#include <Events.h>
#include <list>
#include <watch_ptr.h>

using namespace std;
using namespace KrostganEngine;
using namespace KrostganEngine::GameObjects;

namespace KrostganEngine::UI {
	class OrderTargetsVisualizer {
	private:
		class FollOrdTarHandler:public ICallbackRec_Upd {
		public:
			FollOrdTarHandler(OrderTargetsVisualizer& Owner, watch_ptr_handler_wr_c<ITransfObj> Target, size_t PointIndex);
			~FollOrdTarHandler();

			void Update(CallbackRecArgs_Upd args) override;

			size_t PointIndex;
		private:
			OrderTargetsVisualizer&				Owner;
			watch_ptr_handler_wr_c<ITransfObj>	Target;
		};

		class AddOrderSubscriber :public IEventSubscriber<const IEntityOrder*> {
		public:
			AddOrderSubscriber(OrderTargetsVisualizer& Owner);

			void Execute(const IEntityOrder* const& args) override;

		private:
			OrderTargetsVisualizer& Owner;
		};
		class RemoveOrderSubscriber :public IEventSubscriber<const IEntityOrder*> {
		public:
			RemoveOrderSubscriber(OrderTargetsVisualizer& Owner);

			void Execute(const IEntityOrder* const& args) override;
		private:
			OrderTargetsVisualizer& Owner;
		};
		class ClearOrdsQueueSubscriber : public INoArgsEventSubscriber {
		public:
			ClearOrdsQueueSubscriber(OrderTargetsVisualizer& Owner);

			void Execute() override;
		private:
			OrderTargetsVisualizer& Owner;
		};

	public:
		OrderTargetsVisualizer(Entity& Owner);
		~OrderTargetsVisualizer();

	private:
		Entity& Owner;
		IEventSubscriber<const IEntityOrder*>* AddSub;
		IEventSubscriber<const IEntityOrder*>* RemSub;
		INoArgsEventSubscriber* ClearSub;

		list<FollOrdTarHandler*> DynPointsHandls;
		LinesVisPrimitive Visual;

		vector<Vector2f>& InitializeVisualVector();

		void ReplacePoint(size_t pointIndex, Vector2f newPos);

		void TryAddOrderInList(const IEntityOrder* order);

		void AddPoint_Back(Vector2f point);
		void AddPoint_Back(ITransfObj& target);

		void RemovePoint_Forward();

		void Clear();
	};
}