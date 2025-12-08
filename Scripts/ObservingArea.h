#pragma once

#include <IWarFogObserver.h>
#include <WorldTransfObj.h>

namespace KrostganEngine::GameObjects{
	class ObservingArea final : public WorldTransfObj, public IWarFogObserver {

	public:
		ObservingArea(float ObservingRange, WorldTransfObj& Parent);
		ObservingArea(float ObservingRange);
		virtual ~ObservingArea();

		float GetObservingRange() const override;

	private:
		float ObservingRange;
	};
}