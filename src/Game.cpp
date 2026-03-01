#include "Game.hpp"

Game::Game()
	: m_window( sf::VideoMode( { 800, 600 } ), "Void Warriors" ),
	m_view()
{
	if (!m_player_texture.loadFromFile("assets/Wizard.png"))
	{
		// If we can't load the texture then we can't see the player so we throw an error.
		throw std::runtime_error("Failed to load assets/combined_sheet.png");
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
}

void Game::render()
{
	m_window.clear();

	m_view.setCenter(m_player.getPosition());
	m_window.setView(m_view);

	m_player.draw(m_window);
	m_window.display();
}