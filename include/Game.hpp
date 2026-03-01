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

	// World Objects
	sf::Texture m_player_texture;
	Player m_player;
};