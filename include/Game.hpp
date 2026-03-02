#pragma once
#include "Player.hpp"

class Game {
public:
	Game();
	void run();

private:
	void processEvents();
	void update(float deltaTime);
	void render();

	sf::Clock m_clock;

	// Window and Camera
	sf::RenderWindow m_window;
	sf::View m_view;

	sf::Texture m_vignette_texture;
	std::optional<sf::Sprite> m_vignette_sprite;

	// Map
	sf::Texture m_floor_texture;
	std::optional<sf::Sprite> m_floor_sprite;

	// World Objects
	sf::Texture m_player_texture;
	Player m_player;
};