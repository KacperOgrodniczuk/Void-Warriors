#include "Game.hpp"

Game::Game()
	: m_window( sf::VideoMode( { 1920, 1080 } ), "Void Warriors" ),
	m_view()
{
	// Load the floor texture.
	if (!m_floor_texture.loadFromFile("assets/Floor Tile.png"))
	{
		throw std::runtime_error("Failed to load assets/Floor Tile.png");
	}

	m_floor_texture.setRepeated(true);
	m_floor_texture.setSmooth(false);

	m_floor_sprite.emplace(m_floor_texture);
	m_floor_sprite->setTexture(m_floor_texture);
	m_floor_sprite->setTextureRect(sf::IntRect({ 0, 0 }, { 10000, 10000 }));

	m_floor_sprite->setPosition({ -5000, -5000 });

	if (!m_vignette_texture.loadFromFile("assets/Vignette.png"))
	{
		throw std::runtime_error("Failed to load assets/Vignette.png");
	}

	m_vignette_sprite.emplace(m_vignette_texture);
	sf::FloatRect vignetteBounds = m_vignette_sprite->getLocalBounds();
	m_vignette_sprite->setOrigin({ vignetteBounds.size.x / 2.f, vignetteBounds.size.y / 2.f });
	m_vignette_sprite->setScale({8, 4.5f});

	// Load the player texture.
	if (!m_player_texture.loadFromFile("assets/Wizard.png"))
	{
		// If we can't load the texture then we can't see the player so we throw an error.
		throw std::runtime_error("Failed to load assets/Wizard.png");
	}

	// Initialize the player sprite
	m_player.init(m_player_texture);

	// Initalize the view and centre the camera on the player.
	// Do this after the player has been initialized and optional.emplace has been called, otherwise an exception is thrown.
	m_view.setSize({ 480, 270 });
	m_view.setCenter(m_player.getPosition());
	m_window.setView(m_view);
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
}

void Game::render()
{
	m_window.clear();

	m_window.setView(m_view);
	m_window.draw(*m_floor_sprite);
	m_player.draw(m_window);
	m_window.draw(*m_vignette_sprite);
	
	m_window.display();
}