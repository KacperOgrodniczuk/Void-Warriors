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
	sf::Texture m_vignette_texture;
	std::optional<sf::Sprite> m_vignette_sprite;

	// Map
	sf::Texture m_floor_texture;
	std::optional<sf::Sprite> m_floor_sprite;

	// Map Clutter
	struct Clutter {
		std::optional<sf::Sprite> sprite;
	};
	sf::Texture m_clutter_texture;
	std::vector<Clutter> m_world_clutter;
	std::vector<sf::IntRect> m_clutter_rects;

	// World Entities
	sf::Texture m_player_texture;
	Player m_player;

	sf::Texture m_slime_texture;
	EnemyManager m_enemy_manager;

	void processEvents();
	void update(float deltaTime);
	void render();

	// Helper functions
	// Helper function to grab a series of rectangles from a texture and add it to a collection.
	void addRectsToVector(std::vector<sf::IntRect>& rectVector, sf::Vector2i start, sf::Vector2i grid, int tileSize);
	void loadTexture(sf::Texture &texture, const std::string &texturePath);
};