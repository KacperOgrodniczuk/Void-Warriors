#include "Game.hpp"

Game::Game()
	: m_window( sf::VideoMode( { 1920, 1080 } ), "Void Warriors" ),
	m_view()
{
	// Load the floor texture.
	loadTexture(m_floorTexture, "assets/Floor Tile.png");

	m_floorTexture.setRepeated(true);
	m_floorTexture.setSmooth(false);

	m_floorSprite.emplace(m_floorTexture);
	m_floorSprite->setTexture(m_floorTexture);
	m_floorSprite->setTextureRect(sf::IntRect({ 0, 0 }, { 10000, 10000 }));

	m_floorSprite->setPosition({ -5000, -5000 });

	// Load and scatter the clutter
	loadTexture(m_clutterTexture, "assets/Clutter.png");

	addRectsToVector(m_clutterRects, { 0, 18 * 32 }, { 4, 4 }, 32);
	addRectsToVector(m_clutterRects, { 5 * 32, 18 * 32 }, { 4, 4 }, 32);
	addRectsToVector(m_clutterRects, { 0, 23 * 32 }, { 8, 6 }, 32);

	for (int i = 0; i < 100; ++i) {
		Clutter clutter;
		clutter.sprite.emplace(m_clutterTexture);
		clutter.sprite->setTextureRect(m_clutterRects[std::rand() % m_clutterRects.size()]);
		clutter.sprite->setPosition({static_cast<float>(std::rand() % 4000 - 2000), static_cast<float>(std::rand() % 4000 - 2000) });
		m_worldClutter.push_back(std::move(clutter));
	}

	// Load the vignette texture.
	loadTexture(m_vignetteTexture, "assets/Vignette.png");

	m_vignetteSprite.emplace(m_vignetteTexture);
	sf::FloatRect vignetteBounds = m_vignetteSprite->getLocalBounds();
	m_vignetteSprite->setOrigin({ vignetteBounds.size.x / 2.f, vignetteBounds.size.y / 2.f });
	m_vignetteSprite->setScale({8, 5});

	// Load the player texture.
	loadTexture(m_playerTexture, "assets/Wizard.png");

	m_player.emplace(m_playerTexture);

	// Initalize the view and centre the camera on the player.
	// Do this after the player has been initialized and optional.emplace has been called, otherwise an exception is thrown.
	m_view.setSize({ 480, 270 });
	m_view.setCenter(m_player->getPosition());
	m_window.setView(m_view);

	// Load and initialize the slime texture and spawn some slimes.
	loadTexture(m_slimeTexture, "assets/Slime.png");

	m_enemyManager.spawn({ 10.f, 10.f }, 25.f, m_slimeTexture, sf::IntRect({ 0,0 }, { 100, 100 }));
}

void Game::run()
{
	while ( m_window.isOpen() )
	{
		sf::Time dt = m_clock.restart();

		processEvents();
		processInputs();
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

void Game::processInputs()
{
	m_player->handleInput();
}

void Game::update(float deltaTime)
{
	m_player->update(deltaTime);
	m_vignetteSprite->setPosition(m_player->getPosition());
	m_view.setCenter(m_player->getPosition());
	m_enemyManager.update(deltaTime, m_player->getPosition());
}

void Game::render()
{
	m_window.clear();

	m_window.setView(m_view);

	m_window.draw(*m_floorSprite);
	
	// Draw the clutter
	for (const auto& clutter : m_worldClutter) {
		if (clutter.sprite.has_value()) {
			m_window.draw(*clutter.sprite);
		}
	}

	// Draw the enemies
	m_enemyManager.draw(m_window);

	m_player->draw(m_window);
	m_window.draw(*m_vignetteSprite);
	
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