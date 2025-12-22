#pragma once

#include <SFML/System.hpp>
#include <watch_ptr.h>
#include <SFML/Graphics.hpp>

using namespace sf;

#define DEFAULT_SCALE		Vector2f(1,1)
#define DEFAULT_SCALE_SNG	1
#define DEFAULT_POSITION	Vector2f(0,0)
#define DEFAULT_ORIGIN		Vector2f(0,0)


namespace KrostganEngine::Core {
	class ITransformableObj : public virtual w_ptr_observable {

	public:
		virtual ~ITransformableObj() {}

		virtual Vector2f			GetGlobalPosition() const = 0;
		/// <summary>
	/// Return object's own scale in its coord system
	/// </summary>
	/// <returns></returns>
		virtual Vector2f			GetGlobalScale() const = 0;
		virtual Vector2f			GetOrigin() const = 0;
		virtual const Transform&	GetTransform() const = 0;
		virtual const Transform&	GetInverseTransform() const = 0;
		virtual float				GetGlobalRotation() const = 0;

		virtual Vector2f				GetLocalPosition() const = 0;
		virtual Vector2f				GetLocalScale() const = 0;
		virtual float					GetLocalRotation() const = 0;

		virtual void SetGlobalPosition(Vector2f position) = 0;
		virtual void SetLocalPosition(Vector2f position) = 0;
		/// <summary>
		/// Rescales object in global coords. 
		/// </summary>
		/// <param name="scale"></param>
		virtual void SetGlobalScale(Vector2f scale) = 0;
		virtual void SetLocalScale(Vector2f scale) = 0;
		virtual void SetOrigin(Vector2f origin) = 0;
		virtual void SetGlobalRotation(float rotation) = 0;
		virtual void SetLocalRotation(float rotation) = 0;

		virtual void Move_Global(Vector2f moveValue) final{
			Vector2f nextPos = GetGlobalPosition() + moveValue;
			SetGlobalPosition(nextPos);
		}
		virtual void Move_Local(Vector2f moveValue) final{
			Vector2f nextPos = GetLocalPosition() + moveValue;
			SetLocalPosition(nextPos);
		}
		/// <summary>
		/// Set uniform global scale
		/// </summary>
		/// <param name="scale"></param>
		virtual void SetGlobalScale_Sng(float scale) final{
			SetGlobalScale(Vector2f(scale, scale));
		}
		/// <summary>
		/// Set uniform local scale
		/// </summary>
		/// <param name="scale"></param>
		virtual void SetLocalScale_Sng(float scale) final{
			SetLocalScale(Vector2f(scale, scale));
		}
		virtual void Rotate_Global(float rotation) final{
			SetGlobalRotation(GetGlobalRotation() + rotation);
		}
		virtual void Rotate_Local(float rotation) final{
			SetLocalRotation(GetLocalRotation() + rotation);
		}

		static inline const Vector2i		NULL_POS = Vector2i(-7000000, -7000000);

	protected:
		ITransformableObj() {}

		float ClampRotation(float in) const {
			in = fmod(in, 360);
			if (in < 0)
				in += 360;
			return in;
		}
	};
}