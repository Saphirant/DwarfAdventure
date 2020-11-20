#pragma once
#include <SFML\Graphics.hpp>

class Level : public sf::Drawable, public sf::Transformable
{

public:

	Level(std::string name, std::string tag);

	sf::Vector2i getSize(); //renvoie la taille (nombre de tuiles) du niveau
	sf::Vector2f getHerosSpawn(); //Renvoie la position de spawn du joueur, spécifiée dans le fichier du niveau

	std::vector<sf::IntRect> getCollisionMask();

	std::vector<std::vector<int> > getPathfindingMap();
	int getPathfindingPrecision();


protected:


	std::string m_path;
	sf::Vector2i m_size;

	std::string m_levelGrid;

	sf::Vector2f m_herosPos;

	sf::RenderTexture m_RTlevel;

	std::vector<sf::IntRect> m_levelCollision;


	//Attributs pour le pathfinding
	std::vector<std::vector<int> > m_map;
	int const m_precision;  //taille d'une tuile (qui va etre utilisés dans l'algorithme), peut etre changés

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;




};