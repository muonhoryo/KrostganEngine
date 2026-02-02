#pragma once

#include <_VisualEffectsCore.h>

using namespace sf;

namespace KrostganEngine::Visual {

	enum class TransparencyEffectType : unsigned int {

		ProgressTypeMask = 1,
		FuncTypeMask = (unsigned int)~1,

		Fading = 0,
		Highlight = 1,
		Linear = (1 << 1)
	};

	class TransparencyVisEff : public VisualEffect {
	public:
		virtual ~TransparencyVisEff() {}

		static TransparencyEffectType GetEffectType(TransparencyEffectType progressType, TransparencyEffectType funcType) {
			return (TransparencyEffectType)((unsigned int)progressType | (unsigned int)funcType);
		}

	protected:
		TransparencyVisEff(TransparencyEffectType effectType, float EffTime, IColoredObject& Owner);

		/// <summary>
		/// Return true if effect updating is done
		/// </summary>
		/// <returns></returns>
		bool UpdateEff();
		/// <summary>
		/// Set owner color's transparency as default
		/// </summary>
		void Reset();
		void SetDefaultAlpha(float alpha);
		/// <summary>
		/// Return false and destroy the effect if owner doesn't exist
		/// </summary>
		/// <returns></returns>
		bool CheckOwnerExistane();

		Clock									EffTimer;
		float									EffTime;
		watch_ptr_handler_wr<IColoredObject>*	Owner;
		float									DefaultAlpha;

		float (TransparencyVisEff::* const GetTransparencyFunc)(float) const;

		void SetOwnerColor(Uint8 alpha);

	private:
		float(TransparencyVisEff::* GetTranspFuncByEnum(TransparencyEffectType type))(float) const;

		float GetTransparency_Fading_Linear(float time) const;
		
		float GetTransparency_Highlight_Linear(float time) const;
	};
}