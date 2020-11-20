#include "Player.h"

Player::Player(std::string name, int health, int armor, int mana) : m_name(name), m_health(health), m_armor(armor), m_mana(mana), m_direction("up"), m_pos(0, 0), m_lastTime(sf::seconds(0)), m_bAttack(false), AnimatedCharacter(), m_rect(0,0,24,50)
{



	//CHARGEMENT ANIMATION ATTAQUE
	if(!m_texture.loadFromFile("Ressources/Images/" + m_name + "/berserker.png"))
		std::cout << "Error loading character (spritesheet)" << std::endl;

	m_attackUPAnimation.setSpriteSheet(m_texture);
	for (int i = 0; i < 6; i++)
	{
		m_attackUPAnimation.addFrame(sf::IntRect(192*i, 1355, 192, 189));
	}

	m_attackLEAnimation.setSpriteSheet(m_texture);
	for (int i = 0; i < 6; i++)
	{
		m_attackLEAnimation.addFrame(sf::IntRect(192 * i, 1544, 192, 189));
	}

	m_attackDOAnimation.setSpriteSheet(m_texture);
	for (int i = 0; i < 6; i++)
	{
		m_attackDOAnimation.addFrame(sf::IntRect(192 * i, 1733, 192, 189));
	}

	m_attackRIAnimation.setSpriteSheet(m_texture);
	for (int i = 0; i < 6; i++)
	{
		m_attackRIAnimation.addFrame(sf::IntRect(192 * i, 1922, 192, 189));
	}



	m_walkUPAnimation.setSpriteSheet(m_texture);
	for (int i = 0; i < 9; i++)
	{
		m_walkUPAnimation.addFrame(sf::IntRect(64*i, 515, 64, 64));
	}

	m_walkLEAnimation.setSpriteSheet(m_texture);
	for (int i = 0; i < 9; i++)
	{
		m_walkLEAnimation.addFrame(sf::IntRect(64 * i, 579, 64, 64));
	}

	m_walkDOAnimation.setSpriteSheet(m_texture);
	for (int i = 0; i < 9; i++)
	{
		m_walkDOAnimation.addFrame(sf::IntRect(64 * i, 643, 64, 64));
	}

	m_walkRIAnimation.setSpriteSheet(m_texture);
	for (int i = 0; i < 9; i++)
	{
		m_walkRIAnimation.addFrame(sf::IntRect(64 * i, 707, 64, 64));
	}




	m_currentAnimation = &m_walkDOAnimation;
	
	sf::VideoMode vm(sf::VideoMode::getDesktopMode());
	m_animatedSprite.setPosition(sf::Vector2f((float)(vm.width / 2 - 32),(float) (vm.height / 2 - 32)));
	//m_pos = sf::Vector2f((float)(vm.width / 2 - 32), (float)(vm.height / 2 - 32));

	m_animatedSprite.setOrigin(sf::Vector2f(32, 32));

}

void Player::updateAnimation(std::string tag)
{
	if (tag == "walk") 
	{
		m_animatedSprite.setOrigin(sf::Vector2f(32, 32));
		if (m_direction == "up") 
		{
			m_currentAnimation = &m_walkUPAnimation;
		}
		else if (m_direction == "right") 
		{
			m_currentAnimation = &m_walkRIAnimation;
		}
		else if(m_direction == "down") 
		{
			m_currentAnimation = &m_walkDOAnimation;
		}
		else if(m_direction == "left") 
		{
			m_currentAnimation = &m_walkLEAnimation;
		}
	}
	else if (tag == "attack")
	{

		

		if (m_direction == "up") 
		{
			m_currentAnimation = &m_attackUPAnimation;
			m_animatedSprite.setOrigin(sf::Vector2f(95, 89));
		}
		else if (m_direction == "right") 
		{
			m_currentAnimation = &m_attackRIAnimation;
			m_animatedSprite.setOrigin(sf::Vector2f(95, 97));
		}
		else if(m_direction == "down") 
		{
			m_currentAnimation = &m_attackDOAnimation;
			m_animatedSprite.setOrigin(sf::Vector2f(95, 95));
		}
		else if(m_direction == "left") 
		{
			m_currentAnimation = &m_attackLEAnimation;
			m_animatedSprite.setOrigin(sf::Vector2f(94, 92));
		}
	}
}


void Player::move(sf::Vector2f movement)//déplace le personnage selon une impulsion
{

	m_pos += movement;

	m_rect = sf::FloatRect(m_pos.x, m_pos.y, 26, 48);

}


void Player::setDirection(std::string direction)//change la direction
{
	if(direction == "up" || direction =="right" || direction == "down" || direction == "left")
		m_direction = direction;
}

sf::Vector2f Player::getPos() //renvoie la position
{
	return m_pos;
}

void Player::setPos(sf::Vector2f pos) //change la position
{
	m_pos = pos;
}

void Player::setAttack(bool attack) //change si le perso attaque, plus reset le temps d'attaque
{
	m_bAttack = attack;
	if (attack)
	{
		if (m_bDelay)
		{
			m_lastTime = sf::seconds(0);
		}
	}
}

bool Player::canAttack() //renvoie si le joueur est en train d'attaquer
{
	return m_bAttack;
}

bool Player::isInDelay() //renvoie si le perso eest en recharge
{
	return !m_bDelay;
}

bool Player::isMoving()//renvoie si le personnage bouge
{
	return m_bMove;
}

void Player::setMoving(bool move) //change si le personnage bouge
{
	m_bMove = move;
}

std::string Player::getDirectionByMouse(sf::Vector2f mousePos)
{
	//Choix de la bonne animation	
	if (-(mousePos.y - m_pos.y) >= std::abs(mousePos.x - m_pos.x)) //Vers le haut
	{
		return "up";
	}
	else if (mousePos.x - m_pos.x >= std::abs(mousePos.y - m_pos.y)) //Vers la droite
	{
		return "right";
	}
	else if (mousePos.y - m_pos.y >= std::abs(mousePos.x - m_pos.x)) //Vers le bas
	{
		return "down";
	}
	else if (-(mousePos.x - m_pos.x) >= std::abs(mousePos.y - m_pos.y)) //Vers la gauche
	{
		return "left";
	}
	else
	{
		return "up";
	}
}

sf::FloatRect Player::getRect()
{
	return m_rect;
}



void Player::attack(sf::Time frameTime)
{
	if ((frameTime + m_lastTime).asMilliseconds() >= 500) //délai entre deux attaques
	{

		m_bDelay = true;


		m_lastTime = sf::seconds(0);
		
	}
	if (m_bDelay && m_bAttack) //si pas de délai + le joueur a cliqué
	{
		if ((m_lastTime + frameTime).asMilliseconds() <= 360) //joue les animations en 360ms
		{
			updateAnimation("attack");
			m_bAnimated = true;
		}
		else //puis reset
		{
			m_bDelay = false;
			m_bAnimated = false;
			m_bAttack = false;
			m_lastTime = sf::seconds(0);
		}
	}
	m_lastTime += frameTime;
	
	



}





void Player::draw(sf::RenderTarget & target, sf::RenderStates states) const
{

	// on applique la transformation
	states.transform *= getTransform();

	// et on dessine enfin le tableau de vertex
	target.draw(m_animatedSprite, states);

}