#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class EnemyManager{
public:
	void spawn(sf::Vector2f position, float speed, const sf::Texture& texture, sf::IntRect rect);
	void update(float deltaTime, sf::Vector2f playerPosition);
	void draw(sf::RenderWindow& window);
private:
	std::vector<sf::Vector2f> m_positions;
	std::vector<float> m_speeds;
	std::vector<sf::Sprite> m_sprites;
};