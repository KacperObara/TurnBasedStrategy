#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include <SFML/Graphics.hpp>
#include <stack>

class State;

/**
	Najwazniejsza klasa w programie, ktora odpowiada m.in. za atrybuty okna, kamery oraz zarzadzanie rozgrywka i edytorem.
*/
class GameEngine
{
    public:
        GameEngine();

        void Update(State *&state);
        void Draw(State *&state);
		void ChangeState(State *state);

		std::stack <State*> states;
        sf::RenderWindow window;

		sf::View camera;
		sf::VideoMode screen;

		sf::Clock clock;
		float deltaTime;

		std::string mapName;

    protected:
    private:
		const int FPS = 60;

};

#endif // GAMEENGINE_H
