#include "Game.hpp"

Game::Game()
	: m_window( sf::VideoMode( { 1920, 1080 } ), "Void Warriors" ),
	m_view()
{
	// Load the floor texture.
	loadTexture(m_floor_texture, "assets/Floor Tile.png");

	m_floor_texture.setRepeated(true);
	m_floor_texture.setSmooth(false);

	m_floor_sprite.emplace(m_floor_texture);
	m_floor_sprite->setTexture(m_floor_texture);
	m_floor_sprite->setTextureRect(sf::IntRect({ 0, 0 }, { 10000, 10000 }));

	m_floor_sprite->setPosition({ -5000, -5000 });

	// Load and scatter the clutter
	loadTexture(m_clutter_texture, "assets/Clutter.png");

	addRectsToVector(m_clutter_rects, { 0, 18 * 32 }, { 4, 4 }, 32);
	addRectsToVector(m_clutter_rects, { 5 * 32, 18 * 32 }, { 4, 4 }, 32);
	addRectsToVector(m_clutter_rects, { 0, 23 * 32 }, { 8, 6 }, 32);

	for (int i = 0; i < 100; ++i) {
		Clutter clutter;
		clutter.sprite.emplace(m_clutter_texture);
		clutter.sprite->setTextureRect(m_clutter_rects[std::rand() % m_clutter_rects.size()]);
		clutter.sprite->setPosition({static_cast<float>(std::rand() % 4000 - 2000), static_cast<float>(std::rand() % 4000 - 2000) });
		m_world_clutter.push_back(std::move(clutter));
	}

	// Load the vignette texture.
	loadTexture(m_vignette_texture, "assets/Vignette.png");

	m_vignette_sprite.emplace(m_vignette_texture);
	sf::FloatRect vignetteBounds = m_vignette_sprite->getLocalBounds();
	m_vignette_sprite->setOrigin({ vignetteBounds.size.x / 2.f, vignetteBounds.size.y / 2.f });
	m_vignette_sprite->setScale({8, 5});

	// Load the player texture.
	loadTexture(m_player_texture, "assets/Wizard.png");

	// Initialize the player sprite
	m_player.init(m_player_texture);

	// Initalize the view and centre the camera on the player.
	// Do this after the player has been initialized and optional.emplace has been called, otherwise an exception is thrown.
	m_view.setSize({ 480, 270 });
	m_view.setCenter(m_player.getPosition());
	m_window.setView(m_view);

	// Load and initialize the slime texture and spawn some slimes.
	loadTexture(m_slime_texture, "assets/Slime.png");

	m_enemy_manager.spawn({ 10.f, 10.f }, 25.f, m_slime_texture, sf::IntRect({ 0,0 }, { 100, 100 }));
}

void Game::run()
{
	while ( m_window.isOpen() )
	{
		sf::Time dt = m_clock.restart();

		processEvents();
		update(dt.asSeconds());
		render();
	}
}

void Game::processEvents()
{
	while ( const std::optional event = m_window.pollEvent() )
	{
		if ( event->is<sf::Event::Closed>() )
			m_window.close();

		if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
		{
			if (keyPressed->scancode == sf::Keyboard::Scan::Escape)
				m_window.close();
		}
	}
}

void Game::update(float deltaTime)
{
	m_player.update(deltaTime);
	m_vignette_sprite->setPosition(m_player.getPosition());
	m_view.setCenter(m_player.getPosition());
	m_enemy_manager.update(deltaTime, m_player.getPosition());
}

void Game::render()
{
	m_window.clear();

	m_window.setView(m_view);

	m_window.draw(*m_floor_sprite);
	
	// Draw the clutter
	for (const auto& clutter : m_world_clutter) {
		if (clutter.sprite.has_value()) {
			m_window.draw(*clutter.sprite);
		}
	}

	// Draw the enemies
	m_enemy_manager.draw(m_window);

	m_player.draw(m_window);
	m_window.draw(*m_vignette_sprite);
	
	m_window.display();
}

void Game::addRectsToVector(std::vector<sf::IntRect>& rectVector, sf::Vector2i start, sf::Vector2i grid, int tileSize)
{
	rectVector.reserve(rectVector.size() + grid.x * grid.y);

	for (int y = 0; y < grid.y; ++y)
	{
		for (int x = 0; x < grid.x; ++x)
		{
			rectVector.emplace_back(sf::IntRect({ start.x + x * tileSize, start.y + y * tileSize }, { tileSize, tileSize }));
		}
	}
}

void Game::loadTexture(sf::Texture &texture, const std::string &texturePath)
{
	if (!texture.loadFromFile(texturePath))
	{
		throw std::runtime_error("Failed to load " + texturePath);
	}
}