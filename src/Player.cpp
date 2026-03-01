#include "Player.hpp"

Player::Player()
	: m_animationTimer(0.f), m_currentFrame(0), m_row(0)
{
}

void Player::init(const sf::Texture& texture)
{
	m_sprite.emplace(texture);
	m_sprite->setTextureRect(sf::IntRect({ 0,0 }, { 100,100 }));
	m_sprite->setOrigin({ 50, 50});
	m_sprite->setPosition({ 400, 300 });
}

void Player::update(float deltaTime)
{
	// Movement Logic
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) m_sprite->move({ 0.f, -speed * deltaTime });
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) m_sprite->move({ 0.f, speed * deltaTime });
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) m_sprite->move({ -speed * deltaTime, 0.f });
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) m_sprite->move({ speed * deltaTime, 0.f });

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