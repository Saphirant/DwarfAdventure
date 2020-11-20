#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include "Animation.h"
#include "AnimatedSprite.h"
#include "AnimatedCharacter.h"
#include "Level.h"



class Player: public sf::Drawable, public sf::Transformable, public AnimatedCharacter
{

public:
	
	Player(std::string name, int health, int armor, int mana);

	void updateAnimation(std::string tag);


	void move(sf::Vector2f movement);

	void setDirection(std::string direction);

	sf::Vector2f getPos();
	void setPos(sf::Vector2f pos);

	void attack(sf::Time frameTime); //gère l'attaque et la recharge du temps d'attaque

	void setAttack(bool attack);
	bool canAttack(); //le personnage peut attaquer si il n'est pas en recharge

	bool isInDelay(); //l'attaque est en recharge


	bool isMoving(); //le personnage bouge
	void setMoving(bool move); //chanegr si le personnage bouge


	std::string getDirectionByMouse(sf::Vector2f mousePos);

	sf::FloatRect getRect();




protected:

	//Stats + nom du personnage
	std::string m_name;
	int m_health;
	int m_armor;
	int m_mana;

	sf::FloatRect m_rect; //Rectangle de collision

	sf::Vector2f m_pos; // position du joueurn (et donc position du niveau)
	std::string m_direction; //direction du jouer (up,left,right,down)
	bool m_bMove; //le joueur bouge


	sf::Time m_lastTime; //temps entre les attaques
	bool m_bAttack; //le joueur est en train d'attaquer
	bool m_bDelay; //le joueur peut attaquer




	//Différente animation
	sf::Texture m_texture;

	Animation m_walkUPAnimation;
	Animation m_walkRIAnimation;
	Animation m_walkDOAnimation;
	Animation m_walkLEAnimation;

	Animation m_attackUPAnimation;
	Animation m_attackRIAnimation;
	Animation m_attackDOAnimation;
	Animation m_attackLEAnimation;






	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};
