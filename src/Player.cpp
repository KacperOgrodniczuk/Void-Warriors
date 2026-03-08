#include "Player.hpp"
#include <cmath>

Player::Player(const sf::Texture& texture)
	: m_sprite(texture), m_animationComponent(m_sprite)
{
	m_sprite.setTextureRect(sf::IntRect({ 0,0 }, { 100,100 }));
	m_sprite.setOrigin({ 50, 50 });
	m_sprite.setPosition({ 0, 0 });

	// Setup animations for the player sprite.
	// void addAnimation(const std::string& name, sf::Vector2i startPos, sf::Vector2i frameSize, int frameCount, float duration, bool isLooping);
	m_animationComponent.addAnimation("idle", {0,0}, {100,100}, 6, 0.15f, true);
	m_animationComponent.addAnimation("walk", { 0,100 }, { 100,100 }, 8, 0.1f, true);
}

void Player::update(float deltaTime)
{
	// Movement Logic
	float length = std::sqrt(m_moveDirection.x * m_moveDirection.x + m_moveDirection.y * m_moveDirection.y);
	if(length != 0)
		m_moveDirection /= length; // Normalize the movement direction

	m_position += m_moveDirection * speed * deltaTime;
	m_sprite.setPosition(m_position);

	// Flipping Logic
	if (m_moveDirection.x > 0.1f)
		m_sprite.setScale({ 1.f, 1.f }); // Facing right
	else if (m_moveDirection.x < -0.1f)
		m_sprite.setScale({ -1.f, 1.f }); // Facing left

	// Animation Logic
	if(length > 0.1f)
		m_animationComponent.playAnimation("walk");
	else 
		m_animationComponent.playAnimation("idle");

	m_animationComponent.update(deltaTime);
}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
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