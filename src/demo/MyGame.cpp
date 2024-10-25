#include "MyGame.h"

MyGame::MyGame() : AbstractGame(), score(0), lives(3), numKeys(getRandom(20, 50)), gameWon(false), box(5, 5, 30, 30) {
	TTF_Font * font = ResourceManager::loadFont("res/fonts/arial.ttf", 72);
	gfx->useFont(font);
	gfx->setVerticalSync(true);

	// Create physic objects
	std::shared_ptr<PhysicsObject> box1 = std::make_shared<PhysicsObject>(Rect(5, 5, 30, 30), true);
	gameObjects.push_back(box1);


    for (int i = 0; i < numKeys; i++) {
        std::shared_ptr<GameKey> k = std::make_shared<GameKey>();
        k->isAlive = true;
        k->pos = Point2(getRandom(0, 750), getRandom(0, 550));
        gameKeys.push_back(k);
    }
}

MyGame::~MyGame() {
	
}

void MyGame::handleKeyEvents() {
	int speed = 5;

	if (eventSystem->isPressed(Key::W)) {
		gameObjects.front()->applyForce(Vector2f(10, 10));
	}

	if (eventSystem->isPressed(Key::S)) {
		velocity.y = speed;
	}

	if (eventSystem->isPressed(Key::A)) {
		velocity.x = -speed;
	}

	if (eventSystem->isPressed(Key::D)) {
		velocity.x = speed;
	}

}

void MyGame::update() {
	for (auto obj : gameObjects) {
		obj->nextPosition();
	}
	box.x += velocity.x;
	box.y += velocity.y;

	for (auto key : gameKeys) {
		if (key->isAlive && box.contains(key->pos)) {
			score += 37;
			key->isAlive = false;
			numKeys--;
		}
	}

	velocity.x = 0;
    velocity.y = 0;

	if (numKeys == 0) {
		gameWon = true;
	}
}

void MyGame::render() {
	gfx->setDrawColor(SDL_COLOR_GREEN);
	//gfx->drawRect(box);

	for (auto obj : gameObjects) {
		gfx->drawRect(obj->getBoxCol());
	}

	gfx->setDrawColor(SDL_COLOR_BLUE);
	for (auto key : gameKeys)
        if (key->isAlive)
		    gfx->drawCircle(key->pos, 5);
}

void MyGame::renderUI() {
	gfx->setDrawColor(SDL_COLOR_ORANGE);
	std::string scoreStr = std::to_string(score);
	gfx->drawText(scoreStr, 780 - scoreStr.length() * 50, 25);

	if (gameWon)
		gfx->drawText("Balls Collected", 175, 500);
}