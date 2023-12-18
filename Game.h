#pragma once

#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include "Player.h"
#include "Bullet.h"

class Game
{
private:
    /* Window */
    sf::RenderWindow *window;
    sf::Event ev;
    sf::VideoMode videoMode;

    // private functions //
    void initVariables();
    void initWindow();
    void initPlayer();
    void initBullet();
    void initBackground();
    void initFont();

    // Game objects //
    Player *player;
    Bullet *bulletData;
    sf::Sprite background;
    sf::Texture backgroundTexture;
    sf::Text livesText;
    sf::Font font;
    int lives;

public:
    Game();
    ~Game();

    void pollEvents();
    const bool running() const;

    // UPDATE
    void checkCollision();
    void updateBullets();
    void update();

    // RENDER
    void renderBullets();
    void render();
};

Game::Game() : lives(3)
{
    this->initVariables();
    this->initWindow();
    this->initPlayer();
    this->initBullet();
    this->initBackground();
}

Game::~Game()
{
}

//====================== INITIATORS ======================//

void Game::initVariables()
{
    this->window = nullptr;
}

void Game::initWindow()
{
    this->videoMode.height = 600;
    this->videoMode.width = 800;
    this->window = new sf::RenderWindow(this->videoMode, "Dodge Bullets", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
}

void Game::initFont()
{
    if (!this->font.loadFromFile("assets/dogica.ttf"))
    {
        std::cout << "ERROR::GAME::COULD_NOT_LOAD_FONT" << std::endl;
    }
    this->livesText.setFont(this->font);
    this->livesText.setCharacterSize(24);
    this->livesText.setFillColor(sf::Color::White);
    this->livesText.setPosition(10.f, 10.f);
    this->livesText.setString("Lives: " + std::to_string(this->lives));
}

void Game::initPlayer()
{
    this->player = new Player();
}

void Game::initBullet()
{
    this->bulletData = new Bullet();
}

void Game::initBackground()
{
    if (backgroundTexture.loadFromFile("assets/background.png"))
    {
        background.setTexture(backgroundTexture);
    }
    else
    {
        std::cout << "ERROR::BACKGROUND::COULD_NOT_LOAD_IMAGE" << std::endl;
    }
}

//============= Poll Events =============//

void Game::pollEvents()
{
    while (this->window->pollEvent(this->ev))
    {
        switch (this->ev.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if (this->ev.key.code == sf::Keyboard::Escape)
                this->window->close();
            break;
        }
    }
}

const bool Game::running() const
{
    return this->window->isOpen();
}

//============= UPDATES =============//

void Game::checkCollision()
{
    for (int i = 0; i < this->bulletData->getBullets().size(); i++)
    {
        if (this->player->getPlayer().intersects(this->bulletData->getBullets()[i].getBullet().getGlobalBounds()))
        {
            this->lives--;
            this->livesText.setString("Lives: " + std::to_string(this->lives));
        }
    }
}

void Game::updateBullets()
{
    this->bulletData->update(*this->window);
}

void Game::update()
{
    this->pollEvents();

    this->player->update(this->window);

    this->updateBullets();

    this->checkCollision();
}

//============= RENDERS =============//

void Game::renderBullets()
{
    this->bulletData->render(*this->window);
}

void Game::render()
{
    // Clear old frame
    this->window->clear();

    // Draw game objects
    window->draw(this->background);

    this->player->render(*this->window);

    this->renderBullets();

    window->draw(this->livesText);
    // Render new frame
    this->window->display();
}