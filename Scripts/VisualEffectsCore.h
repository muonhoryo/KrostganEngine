#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <CollectionsExts.h>
#include <watch_ptr.h>

using namespace sf;
using namespace std;
using namespace KrostganEngine;

namespace KrostganEngine::Visual {

	class EffectObject;

	class VisualEffect {
	public:
		virtual ~VisualEffect(){}

	protected:
		VisualEffect(){}

		virtual void Update() = 0;

		friend class EffectObject;
	};

	class EffectObject : public virtual w_ptr_observable {
	public:
		virtual ~EffectObject(){}

		void AddEffect		(VisualEffect& effect) {
			AddedEffects.push_back(&effect);
		}
		void RemoveEffect	(VisualEffect& effect) {
			CollectionsExts::Remove<vector<VisualEffect*>, VisualEffect*>(AddedEffects, &effect);
		}

	protected:
		EffectObject(){}

		void UpdateEffects() {
			for (auto eff : AddedEffects) {
				eff->Update();
			}
		}

	private:
		vector<VisualEffect*> AddedEffects;

	};
}