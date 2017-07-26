#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

//The Limbo Namespace 
namespace tl 
{
	class Interactive : public sf::Sprite
	{
	public:
		//standart constructor
		Interactive() {}
		//standart destructor
		~Interactive() {}

		//full constructor
		Interactive(const char texturePath[], float x, float y, float scale)
		{
			sf::Texture texture;
			texture.loadFromFile(texturePath);
			setTexture(texture);
			setPosition(x, y);
			setScale(scale, scale);
		}
		//One more constructur
		Interactive(const char texturePath[], float x, float y)
		{
			sf::Texture texture;
			texture.loadFromFile(texturePath);
			setTexture(texture);
			setPosition(x, y);
		}

		bool isInteract(sf::RenderWindow &window)
		{
			return getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window)));
		}
	};
}

//   ---------------------------------------------
//  | Code by TheLimboDeveloper aka Nick of Limbo |
//   ---------------------------------------------