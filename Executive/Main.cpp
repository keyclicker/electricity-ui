#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
#include "Button.h"
using namespace sf;

int main()
{
	//Initialization
	RenderWindow window(sf::VideoMode(500, 500), "SFML works!");
	tl::Button button("test.png", 0, 0);

	//Main Loop
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		//Render
		window.clear();

		window.draw(button);

		window.display();
	}

	return 0;
}