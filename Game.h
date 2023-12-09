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

    // Game objects //
    Player *player;
    Bullet *bullet;
    sf::Sprite background;
    sf::Texture backgroundTexture;

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

Game::Game()
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

void Game::initPlayer()
{
    this->player = new Player();
}

void Game::initBullet()
{
    this->bullet = new Bullet();
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

    for (int i = 0; i < this->bullet->bullets.size(); i++)
    {
        if (this->player->getPlayer().intersects(this->bullet->bullets[i].bullet.getGlobalBounds()))
        {
            std::cout << "COLLISION" << std::endl;
        }
    }
}

void Game::updateBullets()
{
    this->bullet->update(*this->window);
}

void Game::update()
{
    this->pollEvents();

    this->player->movement(this->window);

    this->updateBullets();

    this->checkCollision();
}

//============= RENDERS =============//

void Game::renderBullets()
{
    this->bullet->render(*this->window);
}

void Game::render()
{
    // Clear old frame
    this->window->clear();

    // Draw game objects
    window->draw(this->background);

    this->player->render(*this->window);

    this->renderBullets();

    // Render new frame
    this->window->display();
}