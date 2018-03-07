#include <SFML/Graphics.hpp>
#include "GameEngine.h"
#include "State.h"
#include "GameState.h"
#include <stack>
#include "EditorState.h"
#include "MainMenuState.h"

int main()
{
    GameEngine game;
	game.states.push(new MainMenuState(game));

    while(game.window.isOpen() == true)
    {
        game.Update(game.states.top());
        game.Draw(game.states.top());
    }

    return EXIT_SUCCESS;
}
