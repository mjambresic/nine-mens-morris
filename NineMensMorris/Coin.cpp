#include "Coin.h"

Coin::Coin(int playerIndex, sf::Vector2f position)
{
	background.setSize(sf::Vector2f(30.0f, 30.0f));
	background.setOrigin(sf::Vector2f(15.0f, 15.0f));
	textureSelected.setSize(sf::Vector2f(40.f, 40.0f));
	textureSelected.setOrigin(sf::Vector2f(20.0f, 20.0f));
	background.setTexture(&Resources::get().texture(TextureResourceType::COIN_WHITE));
	textureSelected.setTexture(&Resources::get().texture(TextureResourceType::COIN_SELECTED));

	setPlayerIndex(playerIndex);
	setPosition(position);
	homePosition = position;
	selected = false;
	disabled = false;

}

void Coin::update(sf::RenderWindow & window)
{
	// selected check
	if (!disabled) 
	{
		bool newSelectToggler = false;
		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		justPressed = false;
		sf::Vector2f mousePositionFloat(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
		if (background.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePositionFloat))) 
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) 
			{
				newSelectToggler = true;
			}
		}

		if (selectToggler != newSelectToggler)
		{
			selectToggler = newSelectToggler;
			if (selectToggler) 
			{
				selected = !selected;
			}
		}
	}
}

void Coin::draw(sf::RenderWindow & window)
{
	window.draw(background);
	if (selected)
	{
		window.draw(textureSelected);
	}
}

void Coin::setPosition(sf::Vector2f position)
{
	this->position = position;
	background.setPosition(position);
	textureSelected.setPosition(position);
}

bool Coin::isJustPressed()
{
	return justPressed;
}

void Coin::setBackground(sf::Texture & texture)
{
	background.setTexture(&texture);
}

void Coin::enable()
{
	disabled = false;
}

void Coin::disable()
{
	disabled = true;
}

bool Coin::isEnabled()
{
	return !disabled;
}

void Coin::goHome()
{
	setPosition(homePosition);
}

void Coin::setPlayerIndex(int playerIndex)
{
	this->playerIndex = playerIndex;

	switch (playerIndex)
	{
	case 1: // white
		background.setTexture(&Resources::get().texture(TextureResourceType::COIN_WHITE));
		break;
	case 2: // black
		background.setTexture(&Resources::get().texture(TextureResourceType::COIN_BLACK));
		break;
	default:
		break;
	}
}
