#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <iostream>
#include <cmath>

#include "Player.h"
#include "Animation.h"
#include "Level.h"

#include "Game.h"

int main()
{

	//hide console
	ShowWindow(GetConsoleWindow(), SW_HIDE);

	//get screen size
	sf::VideoMode vm(sf::VideoMode::getDesktopMode());
	
	//create window according to the screen résolution
	sf::RenderWindow window(sf::VideoMode(vm.width - 4 ,vm.height - 75), "Dwarf Adventure");
	window.setPosition(sf::Vector2i(-6, 0));

	const int frameLimit(60);

	window.setFramerateLimit(frameLimit);



	


	

	//PLAYER-------------------------------------------------------
	Player heros("Berserker",5,5,0);
	//END PLAYER----------------------------------------------------


	Game(window,frameLimit, heros);


	while (window.isOpen())
	{



		//EVENT--------------------------------------------------------------------------
		sf::Event event;

		while (window.pollEvent(event))
		{

			switch (event.type)
			{

			case sf::Event::Closed:
				window.close();
				break;



			case sf::Event::KeyReleased:
				//close game
				if (event.key.code == 51)
				{
					//window.close();
					
				}
				break;




			default:
				break;
			}


		}
		//END EVENT-----------------------------------------------------------------------

	}

	return 0;
}