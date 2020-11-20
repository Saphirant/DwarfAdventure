#pragma once
#include <SFML\Graphics.hpp>
#include "Animation.h"
#include "AnimatedSprite.h"


class AnimatedCharacter
{


public:

	AnimatedCharacter();

	void updateAnimation(std::string tag);

	void changeAnimation(std::string tag);
	void changeAnimation(std::string tag, sf::Time frameTime);

	void setAnimated(bool anim);
	bool getAnimated();

	

protected:

	Animation *m_currentAnimation;
	AnimatedSprite m_animatedSprite;
	bool m_bAnimated;

	

};