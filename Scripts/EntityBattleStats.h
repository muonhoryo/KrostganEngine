#pragma once

namespace KrostganEngine::GameObjects {
	struct EntityBattleStats {
	public:
		EntityBattleStats();

		//HitPoint
		size_t GetMaxHP() const;
		size_t GetCurrentHP() const;
		size_t GetHPRegenCount() const {
			return RegenHP_Amount;
		}
		float GetHPRegenTick() const {
			return RegenHP_Tick;
		}
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
		void SetHPRegenAmount(size_t amount) {
			if (amount >= 0) {
				RegenHP_Amount = amount;
			}
		}
		void SetHPRegenTick(float tick) {
			if (tick > 0) {
				RegenHP_Tick = tick;
			}
		}
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
		size_t MaxHP=1;
		size_t CurrentHP=1;
		size_t RegenHP_Amount=1;		//Amount of restored hp in 1 tick
		float RegenHP_Tick=1;		//Cooldown between hp's restoring by regeneration
		//Moving
		float MovingSpeed=1;
		//Attack
		size_t AADamage=0;
		float AASpeed=0;		//Amount of dealt attack in 1 second
		float AARadius=0;
		//View
		float AutoAggrRadius=0;
	};
}