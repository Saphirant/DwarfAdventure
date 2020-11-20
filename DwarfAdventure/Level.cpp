#include "Level.h"
#include <fstream>
#include <iostream>

Level::Level(std::string name, std::string tag) : m_path("Ressources/Map/" + name + ".txt"), m_size(0, 0), m_levelGrid(""), m_herosPos(0, 0), m_levelCollision(0), m_precision(32)
{

	


	//Lecture du fichier du level
	std::ifstream loadedLevel(m_path);


	if (loadedLevel)
	{
		std::string ligne;

		while (std::getline(loadedLevel, ligne)) //parcourt le fichier ligne par ligne
		{

			m_size.y++; //on incrémente la taille en y de notre niveau
			m_size.x = ligne.length(); //on met à jour la taille en x du niveau selon la taille de la ligne


			m_levelGrid += ligne; //on ajoute toutes les lignes du fichier




		}


		m_RTlevel.create(m_size.x *64, m_size.y * 64);

		//On parcourt la grille, et on place chaque texture au bon endroit
		int compteur = 0;
		for (int y = 0; y < m_size.y; y++)
		{
			for (int x = 0; x < m_size.x; x++)
			{

				char c = m_levelGrid[compteur]; //caractère du level a afficher
				sf::Texture text; //texture pour chaque tuiles composant le niveau
				text.create(64, 64);
				sf::Sprite sprite;

				if (c == 'z') //z = SPAWN DU JOUEUR, SOL DE BASE
				{
					m_herosPos = sf::Vector2f((float)x * 64 + 32,(float) y * 64 + 32); //on update les coordonnés de spawn du joueur

					if (!text.loadFromFile("Ressources/Images/Level/" + tag + "/floor_a.png"))
						std::cout << "Error loading texture: LEVEL CREATION" << std::endl;

					sprite.setTexture(text);
					sprite.setPosition(sf::Vector2f((float)x * 64, (float)y * 64));

					m_RTlevel.draw(sprite);
				}
				else if (c == 'a') //a = SOL DE BASE
				{
					if (!text.loadFromFile("Ressources/Images/Level/" + tag + "/floor_a.png"))
						std::cout << "Error loading texture: LEVEL CREATION" << std::endl;

					sprite.setTexture(text);
					sprite.setPosition(sf::Vector2f((float)x * 64, (float)y * 64));

					m_RTlevel.draw(sprite);
				}
				else if (c == '0') //0 = MUR DE BASE (COLLISIONS)
				{
					if (!text.loadFromFile("Ressources/Images/Level/" + tag + "/wall_0.png"))
						std::cout << "Error loading texture: LEVEL CREATION" << std::endl;

					sprite.setTexture(text);
					sprite.setPosition(sf::Vector2f((float)x * 64, (float)y * 64));

					m_RTlevel.draw(sprite);

					//Ajout du bloc dans les collisions
					m_levelCollision.push_back(sf::IntRect(x * 64, y * 64, 64, 64));

				}

				compteur++;
			}
		}



		m_RTlevel.display();



		//On créer la map pour le pathFinding
		int sizeX(m_size.x);
		int sizeY(m_size.y);

		int const nbTile(64 / m_precision); //nombre de tiles à ajoutés par rapport a la taille de la map

		//on applique la précision à la taille
		sizeX *= nbTile;
		sizeY *= nbTile;



		for (int y = 0; y < sizeY; y++) //on ajoute chaque ligne de notre grille, remplis de 0
		{
			m_map.push_back(std::vector<int>(sizeX, 0));
		}


		//Ajout des collisions
		for (int y = 0; y < sizeY; y++)
		{
			for (int x = 0; x < sizeX; x++)
			{
				for (sf::IntRect tileRect : m_levelCollision)
				{
					if (sf::IntRect(x * m_precision, y * m_precision, m_precision, m_precision).intersects(tileRect))
					{
						m_map[y][x] = 1;
					}
				}
			}
		}





		//AFFICHAGE DE LA MAP (DEBUG)
		/*for (int y = 0; y < sizeY; y++)
		{
		for (int x = 0; x < sizeX; x++)
		{
		std::cout << std::to_string(m_map[y][x]);
		}
		std::cout << std::endl;
		}*/

	}
	else
	{
		std::cout << "Error loading: " + m_path << std::endl;
	}

	

}

sf::Vector2i Level::getSize()
{
	return m_size;
}

sf::Vector2f Level::getHerosSpawn()
{
	return m_herosPos;
}

std::vector<sf::IntRect> Level::getCollisionMask()
{
	return m_levelCollision;
}

std::vector<std::vector<int>> Level::getPathfindingMap()
{
	return m_map;
}

int Level::getPathfindingPrecision()
{
	return m_precision;
}

















void Level::draw(sf::RenderTarget & target, sf::RenderStates states) const
{

	// on applique la transformation
	states.transform *= getTransform();

	const sf::Texture& texture = m_RTlevel.getTexture(); //et on affiche la renderTexture
	sf::Sprite sprite(texture);

	target.draw(sprite, states);

}