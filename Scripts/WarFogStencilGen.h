#pragma once

#define GLEW_STATIC
#define WIN32_LEAN_AND_MEAN 0

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <VectExts.h>
#include <IWarFogObserver.h>
#include <EngineWorkCycleModule.h>

using namespace sf;
using namespace std;
using namespace KrostganEngine;

namespace KrostganEngine::Core {
	class WarFogStencilGen final : public EngineWorkCycleModule, public EngineCallbackHandler<const IWarFogObserver> {
		
	public:
		WarFogStencilGen
			(Vector2f		leftUp, 
			Vector2f		rightDown,
			const string&	stencShaderPath);
		~WarFogStencilGen() {
			Singleton = nullptr;
		}

		/// <summary>
		/// Recalculate stencil buffer. Before it glEnable(GL_STENCIL_TEST) should be called
		/// </summary>
		void Execute() override;

		void OnAddCallback(const IWarFogObserver& observer) override;
		void OnRemoveCallback() override;

		static inline const unsigned int WARFOG_STENCIL_MASK = 1;

		static WarFogStencilGen* GetInstance() {
			return Singleton;
		}

	private:
		void InitializeBuffer();
		void UpdateBuffer();
		void UpdateObserversInfo();

		VertexArray		StencilMask = VertexArray(PrimitiveType::Quads,5);
		GLuint			StencilBufferIndex = 0;
		RenderStates	StencilCalculatingRenState;
		Shader			StencilCalculatingShader;
		
		/// <summary>
		/// The w-parameter of Vector4 is dummy, cause OpenGL's SSBO read vectors only as Vector4
		/// </summary>
		Vector4f*						WarFogObserversInfo		= new Vector4f[0];

		bool NeedReinitializeBuffer = false;

		static inline WarFogStencilGen* Singleton = nullptr;
	};
}