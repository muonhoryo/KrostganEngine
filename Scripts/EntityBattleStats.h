#pragma once

namespace KrostganEngine::GameObjects {
	struct EntityBattleStats {
	public:
		EntityBattleStats();

		float GetMovingSpeed() const;

		void SetMovingSpeed(float speed);

	private:
		float MovingSpeed;
	};
}