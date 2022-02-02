/// <summary>
//Richard Buturla
///
/// you need to change the above lines or lose marks
/// </summary>

#include "Game.h"
#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ windowWidth, windowHeight, 32U }, "SFML Game" },
	m_exitGame{false} //when true game will exit
{
	setupFontAndText(); // load font 
	setupSprite(); // load texture
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
		if (sf::Event::MouseButtonPressed == newEvent.type)
		{
			processMousePress(newEvent);
		}
		if (sf::Event::MouseButtonReleased == newEvent.type)
		{
			processMouseRelease(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
}

void Game::processMousePress(sf::Event t_event)
{
	m_firstClick.x = t_event.mouseButton.x;
	m_firstClick.y = t_event.mouseButton.y;
}

void Game::processMouseRelease(sf::Event t_event)
{
	m_secondClick.x = t_event.mouseButton.x;
	m_secondClick.y = t_event.mouseButton.y;
	sf::Vector2f velocity = m_secondClick - m_firstClick;
	float headingRadians = std::atan2(velocity.y, velocity.x);
	float headingDegree = 180.0f * headingRadians / static_cast<float>(M_PI);
	headingDegree += 90.0f;

	if (sf::Mouse::Left == t_event.mouseButton.button)
	{
		m_bigPlaneVelocity = velocity / 100.0f;
		m_bigPlaneHeading = headingDegree;
		m_bigPlane.setRotation(headingDegree);
	}
	if (sf::Mouse::Right == t_event.mouseButton.button)
	{
		m_smallPlaneVelocity = velocity / 50.0f;
		m_smallPlaneHeading = headingDegree;
		m_smallPlane.setRotation(headingDegree);
	}
}

void Game::move()
{
	m_bigPlaneLocation += m_bigPlaneVelocity;
	m_bigPlane.setPosition(m_bigPlaneLocation);
	m_smallPlaneLocation += m_smallPlaneVelocity;
	m_smallPlane.setPosition(m_smallPlaneLocation);
}

void Game::keepOnScreen(sf::Vector2f& t_location)
{
	float screenWidth = static_cast<float>(windowWidth); 
	float screenHeight = static_cast<float>(windowHeight);
	if (t_location.x < 0.0f)
	{
		t_location.x = 0.0f;
	}
	if (t_location.x > screenWidth)
	{
		t_location.x = screenWidth;
	}
	if (t_location.y < 0.0f)
	{
		t_location.y = 0.0f;
	}
	if (t_location.y > screenHeight)
	{
		t_location.y = screenHeight;
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	move();
	keepOnScreen(m_bigPlaneLocation);
	keepOnScreen(m_smallPlaneLocation);
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
	m_window.draw(m_sky);
	m_window.draw(m_welcomeMessage);
	m_window.draw(m_bigPlane);
	m_window.draw(m_smallPlane);
	m_window.display();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_welcomeMessage.setFont(m_ArialBlackfont);
	m_welcomeMessage.setString("SFML Game");
	m_welcomeMessage.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_welcomeMessage.setPosition(40.0f, 40.0f);
	m_welcomeMessage.setCharacterSize(80U);
	m_welcomeMessage.setOutlineColor(sf::Color::Red);
	m_welcomeMessage.setFillColor(sf::Color::Black);
	m_welcomeMessage.setOutlineThickness(3.0f);

}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprite()
{
	sf::IntRect bigPlaneRect{ 3, 11, 104, 93 };
	sf::IntRect smallPlaneRect{ 362,115,87,69 };

	if (!m_bigPlaneTexture.loadFromFile("ASSETS\\IMAGES\\planes.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}
	m_bigPlane.setTexture(m_bigPlaneTexture);
	m_bigPlane.setOrigin(bigPlaneRect.width / 2.0f, bigPlaneRect.height / 2.0f);
	m_bigPlane.setPosition(300.0f, 180.0f);
	m_bigPlane.setTextureRect(bigPlaneRect);


	if (!m_smallPlaneTexture.loadFromFile("ASSETS\\IMAGES\\planes.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}
	m_smallPlane.setTexture(m_smallPlaneTexture);
	m_smallPlane.setOrigin(smallPlaneRect.width / 2.0f, smallPlaneRect.height / 2.0f);
	m_smallPlane.setPosition(400.0f, 180.0f);
	m_smallPlane.setTextureRect(smallPlaneRect);

	if (!m_skyTexture.loadFromFile("ASSETS\\IMAGES\\sky.jpg"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}
	m_sky.setTexture(m_skyTexture);
	m_sky.setPosition(0.0f, 0.0f);
	m_sky.setTextureRect(sf::IntRect(0, 0, windowWidth, windowHeight));
	m_skyTexture.setRepeated(true);

}

