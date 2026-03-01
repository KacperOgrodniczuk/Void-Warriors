#pragma once
#include <SFML/Graphics.hpp>
#include <optional>

class Player {
public:
	Player();
	void init(const sf::Texture& texture);
	void update(float deltaTime);
	void draw(sf::RenderWindow& window);

	sf::Vector2f getPosition() const { return m_sprite->getPosition(); }

private:
	std::optional<sf::Sprite> m_sprite;

	float m_animationTimer;
	int m_currentFrame;
	int m_row;
	
	float speed = 200.f; // Player movement speed in pixels per second

};