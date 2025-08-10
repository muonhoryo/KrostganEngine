#pragma once

#include <SquareScaleSprite.h>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <Physics.h>

using namespace sf;
using namespace KrostganEngine::Physics;
using namespace KrostganEngine::Visual;

namespace KrostganEngine::GameObjects {
	class GameObject :public TransformableObj, public DynamicPhysObject, public IColoredObject {
	public:
		virtual ~GameObject();

		static inline const PhysicsLayer SOLID_COLLISION_LAYER = (PhysicsLayer)
			((size_t)PhysicsLayer::Environment |
			(size_t)PhysicsLayer::Decorations |
			(size_t)PhysicsLayer::Buildings |
			(size_t)PhysicsLayer::Units |
			(size_t)PhysicsLayer::Items);

		void SetGlobalPosition(Vector2f position) override;
		void SetLocalPosition(Vector2f position) override;
		void SetGlobalScale(Vector2f scale) override;
		void SetLocalScale(Vector2f scale) override;

		float GetGlobalScale_Sin() const {
			return GetGlobalScale().x;
		}
		float GetLocalScale_Sin() const {
			return GetLocalScale().x;
		}

		float GetScale_Inter(const Vector2f& scale) const;

		Color	GetColor() const override;
		void	SetColor(Color color) override;

	protected:
		GameObject(
			const Texture&	RenTexture,
			Vector2f		GlobalPosition	=	Vector2f(0, 0),
			float			LocalScale		=	1,
			Color			SprColor		=	Color::White,
			Shader*			RenShader		=	nullptr);

		virtual const ColliderShape& GetCollider() const = 0;

		SquareScaleSprite&	BodySprite;
		
	private:
		Transformable& ctor_InitOwner() {
			Transf = new Transformable();
			return *Transf;
		}

		Transformable* Transf;

	};
}