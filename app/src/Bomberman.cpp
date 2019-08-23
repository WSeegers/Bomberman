
#include "./Bomberman.hpp"

#include <stdexcept>
#include <iostream>

const int MAP_WIDTH = 11;
const int MAP_HEIGHT = 11;

static const uint WINDOW_WIDTH = 800;
static const uint WINDOW_HEIGHT = 800;
static const char *WINDOW_TITLE = "Bomberman";

const int depthBits = 32;
const int majorVersion = 3;
const int minorVersion = 3;
const int antialiasingLevel = 4;
const int attributeFlags = sf::ContextSettings::Core;
sf::ContextSettings settings(depthBits, majorVersion, antialiasingLevel, attributeFlags);

Bomberman::Bomberman()
	: window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE, sf::Style::Titlebar, settings),
	  renderTime(0),
	  engineTime(0)
{

	window.setActive();
	renderer.init();

	this->deltaClock.restart();
	this->frameClock.restart();
}

Bomberman::~Bomberman()
{
}

void Bomberman::startGame()
{
	this->start();
};

void Bomberman::updateFunc()
{
	if (!this->window.isOpen())
		this->stop();

	sf::Event event;
	std::vector<EngineEvent> actions;
	InputResponse response = this->input.parseKeys(actions, this->window);
	switch (response)
	{
	case InputResponse::quit:
		this->stop();
		break;
	case InputResponse::pause:
		// Can be used to pause game with 'Esc' key
		this->stop();
		break;
	default:
		break;
	}

	// Record the time elapsed since starting last render
	this->renderTime = this->deltaClock.getElapsedTime().asSeconds();
	this->deltaClock.restart();

	this->engine.update(this->renderTime + this->engineTime, actions, this->gameState);

	// Record the time taken by the engine
	this->engineTime = this->deltaClock.getElapsedTime().asSeconds();
	this->deltaClock.restart();

	// Only render if required to enforce frameRate
	if (this->frameClock.getElapsedTime().asSeconds() >= this->perFrameSeconds)
	{
		this->renderer.render(this->window, this->gameState);
		this->frameClock.restart();
	}
}
