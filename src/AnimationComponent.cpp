#include "AnimationComponent.hpp"
#include <iostream>

AnimationComponent::AnimationComponent(sf::Sprite& sprite)
	: m_sprite(sprite), m_animationTimer(0.f), m_currentFrame(0), m_currentAnimationName(""), m_currentAnimationSequence(nullptr)
{

}

void AnimationComponent::addAnimation(const std::string& name, const AnimationSequence& sequence)
{
	m_animations[name] = sequence;
}

void AnimationComponent::addAnimation(const std::string& name, sf::Vector2i startPos, sf::Vector2i frameSize, int frameCount, float duration, bool isLooping)
{
	AnimationSequence sequence;
	sequence.frameDuration = duration;
	sequence.isLooping = isLooping;

	for (int i = 0; i < frameCount; ++i)
	{
		sf::IntRect frameRect({ startPos.x + i * frameSize.x, startPos.y }, frameSize);
		sequence.frames.push_back(frameRect);
	}

	this->addAnimation(name, sequence);

	std::cout << "Adding animation: " << name << " with " << frameCount << " frames." << std::endl;
}

void AnimationComponent::playAnimation(const std::string& name)
{
	// Return early if we're already playing this animation.
	if (m_currentAnimationName == name) return;

	auto iterator = m_animations.find(name);
	if (iterator != m_animations.end())
	{
		m_currentAnimationName = name;
		m_currentAnimationSequence = &iterator->second;
		m_currentFrame = 0;
		m_animationTimer = 0.f;
		updateTextureRect();
	}
	else {
		std::cerr << "Error: Animation '" << name << "' not found!" << std::endl;
	}
}

void AnimationComponent::update(float deltaTime)
{
	if (!m_currentAnimationSequence || m_currentAnimationName.empty()) return; // No animation to update

	// Update the animation timer
	m_animationTimer += deltaTime;

	//Check if it's time to advance to the next frame
	if (m_animationTimer >= m_currentAnimationSequence->frameDuration)
	{
		m_animationTimer -= m_currentAnimationSequence->frameDuration; // Subtract the frame duration to handle any excess time
		
		// Advance to the next frame
		m_currentFrame++;
		if (m_currentFrame >= m_currentAnimationSequence->frames.size())
		{
			if (m_currentAnimationSequence->isLooping)
				m_currentFrame = 0; // Loop back to the first frame
			else
				m_currentFrame = static_cast<int>(m_currentAnimationSequence->frames.size()) - 1; // Stay on the last frame
		}

		updateTextureRect();
	}
}

void AnimationComponent::updateTextureRect()
{
	if (m_currentAnimationSequence && m_currentFrame < m_currentAnimationSequence->frames.size()) {
		m_sprite.setTextureRect(m_currentAnimationSequence->frames[m_currentFrame]);
	}
}