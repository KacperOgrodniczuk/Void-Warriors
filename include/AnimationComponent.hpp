#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <map>

struct AnimationSequence {
	std::vector<sf::IntRect> frames; // Frames of the animation
	float frameDuration; // Duration of each frame in seconds
	bool isLooping; // Whether the animation should loop

	// explicit default ctor to satisfy C26495
	AnimationSequence()
		: frameDuration(0.f)
		, isLooping(false)
	{}
};

class AnimationComponent {
public:
	AnimationComponent(sf::Sprite& sprite);
	void addAnimation(const std::string& name, const AnimationSequence& sequence);	// Allows to manually define a sequence of frames and add it to the animation component. (Useful for more complex animations that don't fit a single row.)
	void addAnimation(const std::string& name, sf::Vector2i startPos, sf::Vector2i frameSize, int frameCount, float duration, bool isLooping);	// Helper function to add a simple animation sequence that consists of a single row of frames in a texture. (Useful for simple animations like walking or idle.)
	void playAnimation(const std::string& name);
	void update(float deltaTime);
private:
	sf::Sprite& m_sprite;	//Reference to the sprite being animated (Non-owning)

	// State tracking
	float m_animationTimer; // Timer to track frame changes
	int m_currentFrame; // Current frame index
	std::string m_currentAnimationName; // Name of the current animation
	const AnimationSequence* m_currentAnimationSequence; // Pointer to the current animation sequence (for easy access)

	// Animation storage (e.g. "walk", "idle", "jump")
	std::map<std::string, AnimationSequence> m_animations;

	// Helper function to calculate the currect texture rect based on the current animation and frame
	void updateTextureRect();
};