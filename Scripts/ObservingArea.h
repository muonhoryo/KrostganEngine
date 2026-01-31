#pragma once

#include <WarFogObserver.h>
#include <WorldTransfObj.h>

namespace KrostganEngine::GameObjects{
	class ObservingArea final : public WorldTransfObj, public WarFogObserver {

	public:
		ObservingArea(float ObservingRange, WorldTransfObj& Parent);
		ObservingArea(float ObservingRange);
		virtual ~ObservingArea();

		float GetObservingRange() const override;

		FractionWrapper GetFraction() const override;

	private:
		float ObservingRange;
	};
}