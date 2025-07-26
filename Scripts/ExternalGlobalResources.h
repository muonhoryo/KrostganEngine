#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

using namespace sf;
using namespace std;

namespace KrostganEngine::Core {

	struct ExtGlResource {
		/*enum class ResType {
			Texture,
			Sprite,
			Font
		};*/

		ExtGlResource(const string& Name)
			:Name(Name) {}

		virtual ~ExtGlResource()
		{
			delete& Name;
		}

		const string Name;

		//virtual ResType GetType() = 0;

	};

	class ExternalGlobalResources {

	public:
		//Core resources
		static inline const size_t CORE_RES_COUNT = 3;

		static inline const string CORE_RES_DEFAULT_FONT			= "Default_Font";
		static inline const string CORE_RES_CURSORTEX_ATTACK		= "CursorTex_Attack";
		static inline const string CORE_RES_UNIT_DEATHEFFECT_TEX	= "UnitDeathEffect_Tex";

		static const Font&		Get_DefaultFont();
		static const Texture&	Get_CursorTex_Attack();
		static const Texture&	Get_UnitDeathEffect_Tex();

		//static inline const string CORE_RES_DEFAULT_CURSOR_TEX	= "Default_CursorTex";

		//static inline const string DEF_UNITS_SELECTIONAREA_SPRITE_PATH = "UnitsSelectionAreaSprPath";
		//static inline const string DEF_HEROES_SELECTIONAREA_SPRITE_PATH = "HeroesSelectionAreaSprPath";
		//static inline const string DEF_CURSOR_ATTACK_SPRITE_PATH = "CursorSprite_Attack";
		//static inline const string DEF_UNIT_DEATHEFFECT_SPRITE_PATH = "UnitDeathEffectSprite";
		//static inline const string DEF_UNITS_HP_BAR_SPRITE_PATH = "UnitsHPBarSprPath";
		//static inline const string DEF_HEROES_HP_BAR_SPRITE_PATH = "HeroesHPBarSprPath";
		//static inline const string DEF_UNITS_HP_BAR_MASK_PATH = "UnitsHPBarMaskPath";
		//static inline const string DEF_HEROES_HP_BAR_MASK_PATH = "HeroesHPBarMaskPath";

		//static inline const string DEF_DEFAULT_FONT_PATH = "DefaultFont";

	private:
		ExternalGlobalResources(){}

		static inline vector<ExtGlResource*> Resources=vector<ExtGlResource*>(CORE_RES_COUNT);

	public:
		static void AddRes(ExtGlResource& res) {

			if (GetRes(res.Name) != nullptr) {
				string s ="Already has resource with name: " + res.Name;
				throw exception(s.c_str());
			}

			Resources.push_back(&res);
		}
		static ExtGlResource* GetRes(const string& name) {

			ExtGlResource* out_r = nullptr;
			for (auto res : Resources) {
				if (res->Name._Equal(name))
				{
					out_r = res;
					break;
				}
			}
			return out_r;
		}
		template <typename T>
		static T* GetRes_t(const string& name) {

			return dynamic_cast<T*>(GetRes(name));
		}
		/// <summary>
		/// Delete resource from list and from memory
		/// </summary>
		/// <param name="name"></param>
		static void Remove(const string& name) {

			auto it = Resources.begin();
			auto endIt = Resources.cbegin();
			for (;it != endIt;++it) {
				if ((*it)->Name._Equal(name)) {
					Resources.erase(it);
					delete (*it);
					return;
				}
			}
		}
		/// <summary>
		/// Delete resource from list and from memory
		/// </summary>
		/// <param name="name"></param>
		static void Remove(const ExtGlResource& res) {
			Remove(res.Name);
		}
		/// <summary>
		/// Delete all external resources from memory
		/// </summary>
		static void Unload() {
			for (auto res : Resources) {
				delete res;
			}
			Resources.clear();
		}

		//Texture* UnitsSelectionAreaSprite=nullptr;
		//Texture* HeroesSelectionAreaSprite=nullptr;
		//Texture* CursorSprite_Attack = nullptr;
		//Texture* UnitDeathEffectSprite=nullptr;
		//Texture* UnitsHPBarSpritePath = nullptr;
		//Texture* HeroesHPBarSpritePath = nullptr;
		//Texture* UnitsHPBarMaskPath = nullptr;
		//Texture* HeroesHPBarMaskPath = nullptr;

		//Font* DefaultFont=nullptr;

	};
}