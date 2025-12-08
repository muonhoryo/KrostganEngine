#pragma once

#include <PrimitiveVisualShapes.h>


using namespace sf;

namespace KrostganEngine::Visual {
	class WarFog final : public ICallbackRec_GraphRen{

	public:
		WarFog(Vector2f		min,
			Vector2f		max,
			std::byte		RendLayer = DEFAULT_RENDLAYER,
			sf::Shader*		RenShader = nullptr)
				:ICallbackRec_GraphRen(RendLayer),
				VisualForm(*new QuadVisPrimitive(min, max, Color::Red, RendLayer, PrimitiveType::Quads, RenShader))
		{
			VisualForm.Set_IsShownByWarFog(true);
		}
		virtual ~WarFog(){}

		void RenderGraphicAction(RenderWindow& window) override {}
				
	private:
		QuadVisPrimitive& VisualForm;
	};
}