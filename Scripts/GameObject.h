#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <_Physics.h>
#include <CatalogObject.h>
#include <_ExtGlResources.h>
#include <SpriteRenderer.h>

using namespace sf;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::Physics;
using namespace KrostganEngine::Visual;

namespace KrostganEngine::GameObjects {

	struct GameObjectCtorParams {

		GameObjectCtorParams();

		const ExtGlRes_Sprite*	BodySpriteSource = nullptr;
		Vector2f				GlobalPosition	= DEFAULT_POSITION;
		float					GlobalScale		= DEFAULT_SCALE_SNG;
		float					GlobalRotation	= 0;
		Color					SprColor		= Color::White;
		size_t					CatalogID;
		std::byte				SubcatalogID;

		bool SolidCollision = true;
	};
	class GameObject :public WorldTransfObj, public DynamicPhysObject, public IColoredObject, public CatalogObject{
	public:
		virtual ~GameObject();

		static inline const PhysicsLayer	SOLID_COLLISION_LAYER = (PhysicsLayer)
			((size_t)PhysicsLayer::Environment |
			(size_t)PhysicsLayer::Decorations |
			(size_t)PhysicsLayer::Buildings |
			(size_t)PhysicsLayer::Units |
			(size_t)PhysicsLayer::Items);

		void SetGlobalPosition(Vector2f position) override;
		void SetLocalPosition(Vector2f position) override;
		void SetGlobalScale(Vector2f scale) override;
		void SetLocalScale(Vector2f scale) override;

		float GetScale_Inter(const Vector2f& scale) const;

		Color	GetColor() const override;
		void	SetColor(Color color) override;

	//
	// DynamicPhysObject
	//

		bool IsSolidCollision() const override;

		void Set_IsSolidCollision(bool isSolidColl) override;

	protected:
		GameObject(const GameObjectCtorParams& params);

		SpriteRenderer&	BodySprite;
		bool SolidCollision = true;
		
	};
}