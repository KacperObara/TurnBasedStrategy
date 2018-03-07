#include <SFML/Graphics.hpp>
#include <sstream>
#include "GameGui.h"
#include "GameState.h"
#include "GSMouseManager.h"
#include "Unit.h"
#include "TilesetManager.h"

GameGui::GameGui(GameState *gameState)
{
	this->tilesetManager = &gameState->tilesetManager;
	this->mouseManager = gameState->mouseManager;
	this->window = &gameState->game->window;
	this->screen = &gameState->game->screen;

	this->tilesetManager->loadTexture("GUIBackground", "images/GUI/GUIBackground.png");

	background.setTexture(tilesetManager->getTexture("GUIBackground"));
	background.setPosition(sf::Vector2f(screen->width - background.getTexture()->getSize().x, 0));

	activeUnit.sprite.setPosition(screen->width - (background.getTexture()->getSize().x / 1.5), tilesetManager->tileSize);

	font.loadFromFile("fonts/Aller_Bd.ttf");

	this->tilesetManager->loadTexture("EndTurn", "images/GUI/EndTurn.png");
	this->tilesetManager->loadTexture("EndTurnHover", "images/GUI/EndTurnHover.png");
	endTurnButton.setTexture(tilesetManager->getTexture("EndTurn"));

	endTurnButton.setPosition(sf::Vector2f(background.getPosition().x+11, background.getPosition().y + 500));
}

void GameGui::Update(sf::Event &event)
{
	position = sf::Vector2i(screen->width - background.getTexture()->getSize().x, 0);
	position = (sf::Vector2i)window->mapPixelToCoords(position);
	background.setPosition((sf::Vector2f)position);

	int x = (background.getPosition().x);
	int y = (background.getPosition().y + background.getTexture()->getSize().y);
	position = sf::Vector2i(x, y);
	endTurnButton.setPosition((sf::Vector2f)position);

	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (mouseManager->activeUnit == nullptr)
		{
			activeUnit.sprite.setColor(sf::Color::Transparent);
		}
		else
		{
			activeUnit.sprite.setColor(sf::Color::White);
			activeUnit = *mouseManager->activeUnit;
		}	
	}
	UpdateText();
}

void GameGui::Draw()
{
	window->draw(background);
	window->draw(activeUnit.sprite);
	window->draw(unitName);
	window->draw(unitHP);
	window->draw(endTurnButton);
}

/**
	Funkcja aktualizuje tekst gui, czyli informacje po prawej stronie ekranu, takie jak nazwe i zycie zaznaczonej jednostki
*/
void GameGui::UpdateText()
{
	if (activeUnit.sprite.getColor() == sf::Color::Transparent)
	{
		unitName.setString("");
		unitHP.setString("");
	}
	else
	{
		position = sf::Vector2i(screen->width - (background.getTexture()->getSize().x / 1.5), tilesetManager->tileSize);
		position = (sf::Vector2i)window->mapPixelToCoords(position);
		activeUnit.sprite.setPosition((sf::Vector2f)position);

		position.x += tilesetManager->tileSize / 2;
		position.y += 60;

		std::stringstream HP;
		HP << activeUnit.HP << " / " << activeUnit.maxHP << " HP";

		std::string name = activeUnit.name;

		unitName = sf::Text(name, font, 15);
		unitName.setPosition((sf::Vector2f)position);

		sf::FloatRect textRect = unitName.getLocalBounds();
		unitName.setOrigin(textRect.left + textRect.width / 2.0f,
			textRect.top + textRect.height / 2.0f);


		position.y += 20;

		unitHP = sf::Text(HP.str(), font, 15);
		unitHP.setPosition((sf::Vector2f)position);

		textRect = unitHP.getLocalBounds();
		unitHP.setOrigin(textRect.left + textRect.width / 2.0f,
			textRect.top + textRect.height / 2.0f);
	}
}

/// funkcja zwraca prostokat, w ktorym znajduje sie przycisk End Turn
sf::IntRect GameGui::GetEndTurnRect()
{
	sf::Vector2i position(endTurnButton.getPosition());
	sf::Vector2i size(sf::Vector2i(endTurnButton.getTexture()->getSize().x, endTurnButton.getTexture()->getSize().y));

	return sf::IntRect(position, size);
}
