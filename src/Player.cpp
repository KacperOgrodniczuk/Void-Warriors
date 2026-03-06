#include "Player.hpp"
#include <cmath>

Player::Player()
	: m_animationTimer(0.f), m_currentFrame(0), m_row(0)
{
}

void Player::init(const sf::Texture& texture)
{
	m_sprite.emplace(texture);
	m_sprite->setTextureRect(sf::IntRect({ 0,0 }, { 100,100 }));
	m_sprite->setOrigin({ 50, 50});
	m_sprite->setPosition({ 0, 0 });
}

void Player::update(float deltaTime)
{
	// Movement Logic
	float length = std::sqrt(m_moveDirection.x * m_moveDirection.x + m_moveDirection.y * m_moveDirection.y);
	if(length != 0)
		m_moveDirection /= length; // Normalize the movement direction

	m_position += m_moveDirection * speed * deltaTime;
	m_sprite->setPosition(m_position);

	// Animation Logic
	m_animationTimer += deltaTime;
	if (m_animationTimer >= 0.1f) // Change frame every 0.1 seconds
	{
		m_animationTimer = 0.f;
		m_currentFrame = (m_currentFrame + 1) % 6; // 6 frames of animation
		m_sprite->setTextureRect(sf::IntRect({ m_currentFrame * 100, m_row * 100 }, { 100,100 }));
	}
}

void Player::draw(sf::RenderWindow& window)
{
	if (m_sprite)
		window.draw(*m_sprite);
}

void Player::handleInput()
{
	m_moveDirection = { 0.f, 0.f };

	// Input logic
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) m_moveDirection.y -= 1.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) m_moveDirection.y += 1.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) m_moveDirection.x -= 1.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) m_moveDirection.x += 1.f;
}