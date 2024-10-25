#ifndef __TEST_GAME_H__
#define __TEST_GAME_H__

#include "../engine/AbstractGame.h"
#include "../engine/PhysicsEngine.h"
#include <list>

struct GameKey {
	Point2 pos;
	bool isAlive;
};

class MyGame : public AbstractGame {
	private:
		Rect box;

		Vector2i velocity;

		std::vector<std::shared_ptr<GameKey>> gameKeys;
		std::list < std::shared_ptr<PhysicsObject>> gameObjects;

		/* GAMEPLAY */
		int score, numKeys, lives;
		bool gameWon;

		void handleKeyEvents();
		void update();
		void render();
		void renderUI();
	public:
        MyGame();
		~MyGame();
};


#endif