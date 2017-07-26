#pragma once
#include "Interactive.h"

namespace tl
{
	class Button : public Interactive
	{
	public:
		//standart constructor
		Button() {}
		//standart destructor
		~Button() {}

		Button(const char texturePath[], float x, float y, float scale) : Interactive(texturePath, x, y, scale) {}

		Button(const char texturePath[], float x, float y) : Interactive(texturePath, x, y) {}


		//Check is user interact with object and start the animation
		bool isInteract(sf::RenderWindow &window)
		{
			if (getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
			{
				//animation
				return 1;
			}
			return 0;
		}
	};
}

