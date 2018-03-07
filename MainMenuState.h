#pragma once
#include "SFML/Graphics.hpp"
#include "State.h"
/**
Klasa, ktora przechowuje wlasciwosci i pozycje przyciskow. Przykladem jest przycisk Play oraz New Map w menu glownym gry
*/
class Button
{
public:
	Button(){}
	Button(sf::RectangleShape shape, sf::Text text)
	{
		this->buttonRectangle = shape;
		this->buttonText = text;
		buttonRectangle.setFillColor(sf::Color::Transparent);
		buttonRectangle.setOutlineColor(sf::Color(192, 192, 192));
		buttonRectangle.setOutlineThickness(3.0f);
	}
	sf::RectangleShape buttonRectangle;
	sf::Text buttonText;
};
/**
Jak nazwa wskazuje, jest to menu glowne gry, do ktorego trafiamy na poczatku programu 
i ktore pozwala na wybor miedzy uzywaniem edytora, a wlasciwej gry.
*/
class MainMenuState :public State
{
public:

	MainMenuState(GameEngine &game);

	sf::Vector2i mousePosition;

	sf::Font font;
	std::vector <sf::Text> listOfMaps;

	std::string activePath;
	sf::RectangleShape activeBox;

	Button editorButton;
	Button playButton;


	void Update();
	void Draw();
};

