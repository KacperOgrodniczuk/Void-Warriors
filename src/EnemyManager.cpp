#include "EnemyManager.hpp"

void EnemyManager::spawn(sf::Vector2f position, float speed, const sf::Texture& texture, sf::IntRect rect)
{
	m_positions.push_back(position);
	m_speeds.push_back(speed);
	sf::Sprite sprite(texture);
	sprite.setTextureRect(rect);
	sprite.setOrigin({ rect.size.x / 2.f, rect.size.y / 2.f });
	sprite.setPosition(position);
	m_sprites.push_back(sprite);
}

void EnemyManager::update(float deltaTime, sf::Vector2f playerPosition)
{
	for (size_t i = 0; i < m_positions.size(); ++i)
	{
		// Calculate player direction
		sf::Vector2f direction = playerPosition - m_positions[i];

		// Normalize the direction vector
		float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

		if (distance > 1.f)
		{
			direction /= distance; // Normalize the vector

			m_positions[i] += direction * m_speeds[i] * deltaTime;

			m_sprites[i].setPosition(m_positions[i]);
		}
	}
}

void EnemyManager::draw(sf::RenderWindow& window)
{
	for (const auto& sprite : m_sprites)
	{
		window.draw(sprite);
	}
}