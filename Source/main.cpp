#include <iostream>
#include <Windows.h>
#include <direct.h>
#include <stdio.h>
#include <stdlib.h>
#include "Initiate.h"
#include <SFML/Graphics.hpp>

using namespace std;


int main() {
	bool init = initEngine();

	if (!init) {
		exit;
	}
	else {
		sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
		sf::CircleShape shape(100.f);
		shape.setFillColor(sf::Color::Green);

		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			window.clear();
			window.draw(shape);
			window.display();
		}
	}
}