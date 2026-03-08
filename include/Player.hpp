#pragma once
#include <SFML/Graphics.hpp>
#include "AnimationComponent.hpp"

class Player {
public:
	Player(const sf::Texture& texture);
	void handleInput();
	void update(float deltaTime);
	void draw(sf::RenderWindow& window);

	sf::Vector2f getPosition() const { return m_sprite.getPosition(); }

private:
	sf::Sprite m_sprite;
	sf::Vector2f m_position;
	sf::Vector2f m_moveDirection;
	AnimationComponent m_animationComponent;
	
	float speed = 200.f; // Player movement speed in pixels per second

};