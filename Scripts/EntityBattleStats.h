#pragma once

namespace KrostganEngine::GameObjects {
	struct EntityBattleStats {
	public:
		EntityBattleStats();

		//HitPoint
		size_t GetMaxHP() const;
		size_t GetCurrentHP() const;
		//Moving
		float GetMovingSpeed() const;
		//Attack
		size_t GetAADamage() const;
		float GetAASpeed() const;
		float GetAARadius() const;

		//HitPoint
		void SetMaxHP(size_t hp);
		void SetCurrentHP(size_t hp);
		void RestoreHealth();
		//Moving
		void SetMovingSpeed(float speed);
		//Attack
		void SetAADamage(size_t damage);
		void SetAASpeed(float speed);
		void SetAARadius(float radius);

	private:
		//HitPoint
		size_t MaxHP;
		size_t CurrentHP;
		//Moving
		float MovingSpeed;
		//Attack
		size_t AADamage;
		float AASpeed;
		float AARadius;
	};
}