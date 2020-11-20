#include <iostream>
#include "AnimatedCharacter.h"




AnimatedCharacter::AnimatedCharacter() : m_currentAnimation(0), m_animatedSprite(sf::milliseconds(60), false, true), m_bAnimated(false)
{


}

void AnimatedCharacter::updateAnimation(std::string tag)
{
}

void AnimatedCharacter::changeAnimation(std::string tag)
{
	if (tag == "play") 
	{
		m_animatedSprite.play(*m_currentAnimation);
	}
	else if (tag == "stop")
	{
		m_animatedSprite.stop();
	}
	else if (tag == "pause") 
	{
		m_animatedSprite.pause();
	}


}

void AnimatedCharacter::changeAnimation(std::string tag, sf::Time frameTime)
{
	changeAnimation(tag);
	if (tag == "update") 
	{
		m_animatedSprite.update(frameTime);
	}
}

void AnimatedCharacter::setAnimated(bool anim)
{
	m_bAnimated = anim;
}

bool AnimatedCharacter::getAnimated()
{
	return m_bAnimated;
}


