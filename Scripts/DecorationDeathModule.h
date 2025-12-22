#pragma once

#include <IAttackableObj.h>

namespace KrostganEngine::GameObjects {
	class DecorationDeathModule : public IDeathModule {

	public:
		DecorationDeathModule(IAttackableObj& owner);
		virtual ~DecorationDeathModule(){}

		void Death() override;
	};
}