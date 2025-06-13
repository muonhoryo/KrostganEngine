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
		float GetAACooldown() const;
		float GetAARadius() const;
		//View
		float GetAutoAggrRadius() const;

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
		//View
		void SetAutoAggrRadius(float radius);

		static float GetAACooldown(float AASpeed) {
			return (float)1 / AASpeed;
		}

	private:
		//HitPoint
		size_t MaxHP;
		size_t CurrentHP;
		//Moving
		float MovingSpeed;
		//Attack
		size_t AADamage;
		float AASpeed;		//Amount of dealt attack in 1 second
		float AARadius;
		//View
		float AutoAggrRadius;
	};
}