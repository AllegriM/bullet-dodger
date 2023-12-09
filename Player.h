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

    float velocity, gravity;
    int horizontalFrame, verticalFrame;
    float jumpHeight, jumpVelocity;
    bool isJumping;
    int offset_x, offset_y;

public:
    Player();
    ~Player();
    sf::FloatRect getPlayer();
    void movement(sf::RenderWindow *window);
    void render(sf::RenderTarget &target);
};

Player::Player() : isJumping(false), jumpHeight(100.0f), jumpVelocity(15.0f), velocity(0.0f),
                   gravity(0.5f), offset_x(16), offset_y(15), horizontalFrame(64), verticalFrame(64)
{
    this->player.setPosition(400.f, 475.f);
    if (this->playerSkin.loadFromFile("assets/character.png"))
    {
        this->player.setTexture(this->playerSkin);
    }
    else
    {
        std::cout << "ERROR::PLAYER::COULD_NOT_LOAD_SKIN" << std::endl;
    }
    playerCollision.width = 31;
    playerCollision.height = 46;
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

void Player::movement(sf::RenderWindow *window)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && isJumping == false)
    {
        this->isJumping = true;
        this->velocity = -jumpVelocity;
    }

    if (this->isJumping)
    {
        this->velocity += this->gravity;
        float nextYMovement = this->player.getPosition().y + this->velocity;

        if (nextYMovement > window->getSize().y - 125)
        {
            isJumping = false;
            nextYMovement = window->getSize().y - 125;
        }
        this->player.setPosition(this->player.getPosition().x, nextYMovement);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        int xTexture = 0;
        float nextXMovement = this->player.getPosition().x - 5;

        xTexture = (int)this->player.getPosition().x / 3 % 9;
        xTexture = xTexture * this->horizontalFrame;
        this->player.setTextureRect(sf::IntRect(xTexture, this->horizontalFrame, this->horizontalFrame, this->verticalFrame));

        if (nextXMovement < 0 + this->horizontalFrame / 2)
        {
            this->player.setPosition(0 + this->horizontalFrame / 2, this->player.getPosition().y);
        }
        else
        {
            if (nextXMovement < 0)
            {
                nextXMovement = 0;
            }

            this->player.setPosition(nextXMovement, this->player.getPosition().y);
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        int xTexture = 0;
        xTexture = (int)this->player.getPosition().x / 3 % 9;
        xTexture = xTexture * this->horizontalFrame;
        this->player.setTextureRect(sf::IntRect(xTexture, this->horizontalFrame * 3, this->horizontalFrame, this->verticalFrame));
        if (this->player.getPosition().x > window->getSize().x - this->horizontalFrame)
        {
            this->player.setPosition(window->getSize().x - this->horizontalFrame, this->player.getPosition().y);
        }
        else
        {
            float nextXMovement = this->player.getPosition().x + 5;

            if (nextXMovement > window->getSize().x - this->horizontalFrame)
            {
                nextXMovement = window->getSize().x - this->horizontalFrame;
            }

            this->player.setPosition(nextXMovement, this->player.getPosition().y);
        }
    }
    if (!this->isJumping && (this->player.getPosition().y < window->getSize().y - 125))
    {
        this->velocity += this->gravity;
        this->player.setPosition(this->player.getPosition().x, this->player.getPosition().y + this->velocity);
    }
}

void Player::render(sf::RenderTarget &target)
{
    target.draw(this->player);
}
// (this->player.getPosition().y < window->getSize().y - 125 || this->player.getPosition().y == 400 || this->player.getPosition().y == 250)