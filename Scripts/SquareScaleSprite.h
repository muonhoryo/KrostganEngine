#pragma once

#include <SpriteRenderer.h>
#include <TransformableObj.h>

using namespace KrostganEngine::GameObjects;

namespace KrostganEngine::Visual {
	class SquareScaleSprite :public SpriteRenderer{

	public:
		virtual ~SquareScaleSprite(){}
		SquareScaleSprite(
			const Texture&	RenTexture, 
			float			maxSpriteSize, 
			Vector2f		GlobalPosition	=	Vector2f(0, 0),
			float			GlobalScale	=	1,
			Color			SprColor		=	Color::White,
			Shader*			RendShader		=	nullptr);

		SquareScaleSprite(
			const Texture&		RenTexture,
			WorldTransfObj&		Parent,
			float				maxSpriteSize,
			Vector2f			LocalPosition = Vector2f(0, 0),
			float				LocalScale		= 1,
			Color				SprColor		= Color::White,
			Shader*				RendShader = nullptr);
		
		void SetGlobalScale		(Vector2f scale) override;
		void SetLocalScale		(Vector2f scale) override;

		float GetGlobalScale_Sin() const{
			return GetGlobalScale().x;
		}
		float GetLocalScale_Sin() const {
			return GetLocalScale().x;
		}


		///// <summary>
		///// Return min of normalize by engine coord system global sizes
		///// </summary>
		///// <returns></returns>
		//float GetMinSize_Global();
		///// <summary>
		///// Return min of normalize by engine coord system local sizes
		///// </summary>
		///// <returns></returns>
		//float GetMinSize_Local();
	private:
		float GetScale_Inter(const Vector2f& scale)const;
	};
}