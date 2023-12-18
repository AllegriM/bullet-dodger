#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class Player
{
private:
    /* data */
    sf::Sprite player;
    sf::Texture playerSkin;
    sf::FloatRect playerCollision;

    float velocity, gravity, movementSpeed;
    int horizontalFrame, verticalFrame;
    float jumpHeight, jumpVelocity;
    bool isJumping;
    int offset_x, offset_y;
    int step;

public:
    Player();
    ~Player();
    sf::FloatRect getPlayer();
    void updateAnimation();
    void updateInput();
    void update(sf::RenderWindow *window);
    void movement(sf::RenderWindow *window);
    void render(sf::RenderTarget &target);
};

Player::Player() : isJumping(false), jumpHeight(100.0f), jumpVelocity(15.0f), velocity(0.0f), movementSpeed(8.0f),
                   gravity(0.5f), offset_x(16), offset_y(15), horizontalFrame(64), verticalFrame(64), step(0)
{
    this->playerCollision.width = 31;
    this->playerCollision.height = 46;
    this->player.setOrigin(this->playerCollision.width / 2, this->playerCollision.height / 2);
    this->player.setPosition(400.f, 500.f);
    if (this->playerSkin.loadFromFile("assets/character.png"))
    {
        this->player.setTexture(this->playerSkin);
    }
    else
    {
        std::cout << "ERROR::PLAYER::COULD_NOT_LOAD_SKIN" << std::endl;
    }

    this->player.setTextureRect(sf::IntRect(0, horizontalFrame * 3, horizontalFrame, verticalFrame));
}

Player::~Player()
{
}

sf::FloatRect Player::getPlayer()
{
    playerCollision.left = this->player.getPosition().x + offset_x;
    playerCollision.top = this->player.getPosition().y + offset_y;
    return this->playerCollision;
}

void Player::updateAnimation()
{
    int xTexture = 0;
    xTexture = (int)this->player.getPosition().x / 3 % 9;
    xTexture = xTexture * this->horizontalFrame;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        this->player.setTextureRect(sf::IntRect(xTexture, this->horizontalFrame, this->horizontalFrame, this->verticalFrame));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        this->player.setTextureRect(sf::IntRect(xTexture, this->horizontalFrame * 3, this->horizontalFrame, this->verticalFrame));
    }
}

void Player::updateInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        this->player.move(-movementSpeed, 0.f);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        this->player.move(movementSpeed, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->isJumping == false)
    {
        this->isJumping = true;
        this->velocity = -this->jumpVelocity;
    }
}

void Player::movement(sf::RenderWindow *window)
{

    // ESCALONES //
    if ((this->player.getPosition().y + 2 == 400 && this->player.getPosition().x > 400) ||
        (this->player.getPosition().y + 5 == 250 && this->player.getPosition().x > 0 && this->player.getPosition().x < 300))
    {
        this->isJumping = false;
        this->velocity = 0;
    }
    else
    {
        this->isJumping = true;
    }

    // LIMITAR MOVIMIENTOS EN X //

    if (this->player.getPosition().x < 0)
    {
        this->player.setPosition(0, this->player.getPosition().y);
    }
    else if (this->player.getPosition().x > window->getSize().x - this->playerCollision.width)
    {
        this->player.setPosition(window->getSize().x - this->playerCollision.width, this->player.getPosition().y);
    }

    if (isJumping)
    {
        velocity += gravity;
        float nextYMovement = player.getPosition().y + velocity;

        if (nextYMovement > window->getSize().y - 100)
        {
            isJumping = false;
            nextYMovement = window->getSize().y - 100;
        }
        player.setPosition(player.getPosition().x, nextYMovement);
    }
    else
    {
        velocity += gravity;
        float nextYMovement = player.getPosition().y + velocity;

        if (nextYMovement > window->getSize().y - 100)
        {
            nextYMovement = window->getSize().y - 100;
        }
    }
}

void Player::update(sf::RenderWindow *window)
{
    this->updateAnimation();
    this->updateInput();
    this->movement(window);
}

void Player::render(sf::RenderTarget &target)
{
    target.draw(this->player);
}