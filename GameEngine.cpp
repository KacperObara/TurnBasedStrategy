//#include <SFML/Graphics.hpp>
#include "GameEngine.h"
#include "State.h"

GameEngine::GameEngine()
{
	screen = sf::VideoMode::getDesktopMode();
	screen.width *= 0.8;
	screen.height *= 0.8;

	window.create(screen, "Gra Strategiczna");
	window.setFramerateLimit(FPS);

	camera.setCenter(screen.width/2, screen.height/2);
	camera.setSize(screen.width, screen.height);
	window.setView(camera);
}

void GameEngine::Update(State *&state)
{
	deltaTime = clock.restart().asSeconds();
    state->Update();
}

void GameEngine::Draw(State *&state)
{
    state->Draw();
	window.setView(camera);
	window.display();
}

void GameEngine::ChangeState(State *state)
{
	states.pop();
	states.push(state);
}
