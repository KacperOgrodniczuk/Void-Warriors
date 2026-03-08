#pragma once
#include "Player.hpp"
#include "EnemyManager.hpp"

class Game {
public:
	Game();
	void run();

private:
	sf::Clock m_clock;

	// Window and Camera
	sf::RenderWindow m_window;
	sf::View m_view;

	// Visual effects
	sf::Texture m_vignetteTexture;
	std::optional<sf::Sprite> m_vignetteSprite;

	// Map
	sf::Texture m_floorTexture;
	std::optional<sf::Sprite> m_floorSprite;

	// Map Clutter
	struct Clutter {
		std::optional<sf::Sprite> sprite;
	};
	sf::Texture m_clutterTexture;
	std::vector<Clutter> m_worldClutter;
	std::vector<sf::IntRect> m_clutterRects;

	// World Entities
	sf::Texture m_playerTexture;
	std::optional<Player> m_player;

	sf::Texture m_slimeTexture;
	EnemyManager m_enemyManager;

	void processEvents();	// Events are for system wide events such as window close, 
	void processInputs();	// Input is for player input such as movement and attacking.
	void update(float deltaTime);
	void render();

	// Helper functions
	// Helper function to grab a series of rectangles from a texture and add it to a collection.
	void addRectsToVector(std::vector<sf::IntRect>& rectVector, sf::Vector2i start, sf::Vector2i grid, int tileSize);
	void loadTexture(sf::Texture &texture, const std::string &texturePath);
};