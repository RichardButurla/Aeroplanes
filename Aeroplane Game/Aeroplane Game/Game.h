/// <summary>
//Richard Buturla
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>

#include <SFML/Graphics.hpp>
#define _USE_MATH_DEFINES
#include <math.h>

const int windowHeight = 800;
const int windowWidth = 1000;


class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void processMousePress(sf::Event t_event);
	void processMouseRelease(sf::Event t_event);
	void move();
	void keepOnScreen(sf::Vector2f &t_location);

	void update(sf::Time t_deltaTime);
	void render();
	
	void setupFontAndText();
	void setupSprite();

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen

	sf::Sprite m_bigPlane;
	sf::Sprite m_smallPlane;
	sf::Texture m_bigPlaneTexture;
	sf::Texture m_smallPlaneTexture;
	sf::Sprite m_sky;
	sf::Texture m_skyTexture;

	sf::Vector2f m_firstClick;
	sf::Vector2f m_secondClick;

	sf::Vector2f m_bigPlaneVelocity{ 1.0f,-1.0f };
	float m_bigPlaneHeading = 45.0f; //degrees
	sf::Vector2f m_bigPlaneLocation;
	sf::Vector2f m_smallPlaneVelocity{ -2.0f,2.0f };
	float m_smallPlaneHeading = 225.0f;
	sf::Vector2f m_smallPlaneLocation;

	bool m_exitGame; // control exiting game

};

#endif // !GAME_HPP

