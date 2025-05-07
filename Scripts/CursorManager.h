#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;

namespace KrostganEngine::UI {
	class CursorManager {
	public:
		CursorManager(RenderWindow& RendWin,Cursor& Curs_Default,Cursor& Curs_AttackOrder);
		
		void SetDefaultSprite();
		void SetAttackOrderSprite();

	private:
		RenderWindow& RendWin;

		Cursor& Curs_Default;
		Cursor& Curs_AttackOrder;

		void SetCursor(Cursor& curs);
	};
}