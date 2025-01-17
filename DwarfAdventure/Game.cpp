#include "Game.h"

Game::Game(sf::RenderWindow& window,int const frameLimit, Player& heros)
{

	//get screen size
	sf::VideoMode vm(sf::VideoMode::getDesktopMode());


	//BASIC FONT
	sf::Font basicFont;
	if (!basicFont.loadFromFile("Ressources/Font/basic.otf"))
	{
		std::cout << "Load error" << std::endl;
	}

	//FPS text
	sf::Text fpsText("FPS : 0", basicFont, 25);
	sf::Clock fpsClock;

	sf::Clock animClock;


	//PLAYER-------------------------------------------------------

	sf::Vector2f lastMousePos(0, 0);

	float speed = 4.f * 60 / frameLimit;

	//END PLAYER----------------------------------------------------


	Level level("mapDefault_0", "Default");
	level.setOrigin(level.getHerosSpawn());
	std::vector<sf::IntRect> levelCollision(level.getCollisionMask());





	while (window.isOpen())
	{

		//FPS
		sf::Time frameTime(fpsClock.restart());
		float fps = 1 / frameTime.asSeconds();
		fpsText.setString("FPS : " + std::to_string((int)floor(fps)));


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
					window.close();
				}
				break;




			default:
				break;
			}

			if (event.type == sf::Event::Resized)
			{
				// on met � jour la vue, avec la nouvelle taille de la fen�tre
				sf::FloatRect visibleArea(0, 0, (float)event.size.width, (float)event.size.height);
				window.setView(sf::View(visibleArea));
			}

		}
		//END EVENT-----------------------------------------------------------------------

		//PERSONNAGE----------------------------------------------------------------------

		sf::Vector2f movement(0.f, 0.f);




		if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) //G�re le clique de la souris pour d�placer le personnage
		{
			sf::Vector2i localPosition = sf::Mouse::getPosition(window);

			lastMousePos = sf::Vector2f(localPosition) - sf::Vector2f((float)(vm.width / 2 - 32), (float)(vm.height / 2 - 32)) + heros.getPos();

		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) //Attaque du personnage
		{
			if (!heros.canAttack() && !heros.isInDelay())
			{
				lastMousePos = heros.getPos();
				heros.setAttack(true); //Fait l'attaque

				std::string dir = heros.getDirectionByMouse(sf::Vector2f(sf::Mouse::getPosition(window)) - sf::Vector2f((float)(vm.width / 2 - 32), (float)(vm.height / 2 - 32)) + heros.getPos());

				//DIRECTION DES ANIMATIONS
				if (dir == "up")
				{
					heros.setDirection("up"); //animation
				}
				else if (dir == "right")
				{
					heros.setDirection("right");//animation
				}
				else if (dir == "down")
				{
					heros.setDirection("down");//animation
				}
				else if (dir == "left")
				{
					heros.setDirection("left");//animation
				}
			}

		}



		heros.attack(frameTime);




		//Fait bouger le personnage selon le dernier clique de souris, tant que la position du h�ros et du clique sont diff�rents
		if ((heros.getPos().x > lastMousePos.x + speed || heros.getPos().x < lastMousePos.x - speed) && (heros.getPos().y > lastMousePos.y - speed || heros.getPos().y < lastMousePos.y + speed))
		{
			heros.setMoving(true);

			sf::Vector2f herosPos = heros.getPos();

			std::string dir = heros.getDirectionByMouse(lastMousePos);

			if (dir == "up")
			{
				heros.setDirection("up"); //animation
				heros.updateAnimation("walk"); //animation
				heros.setAnimated(true);
			}
			else if (dir == "right")
			{
				heros.setDirection("right");//animation
				heros.updateAnimation("walk");//animation
				heros.setAnimated(true);
			}
			else if (dir == "down")
			{
				heros.setDirection("down");//animation
				heros.updateAnimation("walk");//animation
				heros.setAnimated(true);
			}
			else if (dir == "left")
			{
				heros.setDirection("left");//animation
				heros.updateAnimation("walk");//animation
				heros.setAnimated(true);
			}


			

			
			//Mouvement, rep�re 1,y ou x,1
			if (std::abs(lastMousePos.x - herosPos.x) > std::abs(lastMousePos.y - herosPos.y))
			{
				if (lastMousePos.x - herosPos.x > 0)
					movement.x = 1;
				else
					movement.x = -1;

				movement.y = (lastMousePos.y - herosPos.y) / std::abs((lastMousePos.x - herosPos.x));


			}
			else if (std::abs(lastMousePos.x - herosPos.x) < std::abs(lastMousePos.y - herosPos.y))
			{
				movement.x = (lastMousePos.x - herosPos.x) / std::abs((lastMousePos.y - herosPos.y));

				if (lastMousePos.y - herosPos.y > 0)
					movement.y = 1;
				else
					movement.y = -1;
			}
			else
			{
				movement = sf::Vector2f(1, 1);
			}

			movement *= speed; //application de la vitesse de d�placement		
		}
		else
		{
			heros.setMoving(false);
		}
		

		if ((heros.isInDelay() || !heros.canAttack()) && !heros.isMoving())
		{
			heros.setAnimated(false);
		}

		if (!heros.getAnimated()) //Stop l'animation, si aucune ne doit etre joeur
		{
			heros.changeAnimation("stop");
		}


		heros.changeAnimation("play"); //Joue les animations

		heros.changeAnimation("update", frameTime); //Selon le temps



		heros.move(movement); //Change la position du perso

		//Test des collisions avec le d�cor
		sf::FloatRect herosRect(heros.getRect().left + level.getHerosSpawn().x -32 + 19, heros.getRect().top + level.getHerosSpawn().y -32 + 8, heros.getRect().width, heros.getRect().height);

		//Test des collisions apr�s le d�placement
		for (sf::IntRect tileRect : levelCollision)
		{
			if (herosRect.intersects(sf::FloatRect(tileRect)))
			{
				heros.move(-movement); //on annule le d�placement
				heros.changeAnimation("stop");
				break;
			}
		}

		level.setPosition(sf::Vector2f((float)(vm.width / 2 - 32), (float)(vm.height / 2 - 32)) - heros.getPos()); //On d�place le niveau


		//END PERSONNAGE------------------------------------------------------------------

		//DISPLAY-------------------------------------------------------------------------
		window.clear();

		window.draw(level);

		//AFFICHAGE RECTANGLE DE COLLISIONS
		/*
		sf::RectangleShape rect(sf::Vector2f(herosRect.width, herosRect.height));
		rect.setPosition(herosRect.left, herosRect.top );
		window.draw(rect);

		for (sf::IntRect tileRect : levelCollision)
		{
			sf::RectangleShape rect(sf::Vector2f(tileRect.width, tileRect.height));
			rect.setPosition(tileRect.left, tileRect.top);
			rect.setFillColor(sf::Color(255, 0, 0));
			window.draw(rect);

		}*/

		window.draw(heros);


		window.draw(fpsText);
		window.display();
		//END DISPLAY---------------------------------------------------------------------
	}
}

	
