#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>

class Bullet
{
private:
    /* data */
    sf::Sprite bulletSprite;
    float bulletVelocity;
    sf::Texture bulletTexture;
    sf::FloatRect bulletRectangle;
    std::vector<Bullet> bullets;

    float bulletSpawnTimer, bulletSpawnTimerMax;
    int maxBullets;
    int ground_start, offset_x, offset_y;

public:
    Bullet();
    ~Bullet();

    sf::Sprite getBullet();
    std::vector<Bullet> getBullets();
    void spawnBullet(sf::RenderWindow &window);
    void update(sf::RenderWindow &window);
    void render(sf::RenderWindow &window);
};

Bullet::Bullet() : bulletSpawnTimer(0.f), bulletSpawnTimerMax(10.f), maxBullets(3),
                   ground_start(65), offset_x(112), offset_y(100) {}

Bullet::~Bullet()
{
}

std::vector<Bullet> Bullet::getBullets()
{
    return this->bullets;
}

sf::Sprite Bullet::getBullet()
{
    return this->bulletSprite;
}

void Bullet::spawnBullet(sf::RenderWindow &window)
{
    Bullet newBullet;

    if (this->bulletTexture.loadFromFile("assets/bomb.png"))
    {
        newBullet.bulletSprite.setTexture(this->bulletTexture);
    }
    else
    {
        std::cout << "ERROR::BULLET::COULD_NOT_LOAD_SKIN" << std::endl;
    }

    newBullet.bulletSprite.setScale(0.1f, 0.1f);
    newBullet.bulletSprite.setPosition(
        0.f - newBullet.bulletSprite.getGlobalBounds().width / 2,
        static_cast<float>(rand() % static_cast<int>((window.getSize().y - ground_start) - newBullet.bulletSprite.getGlobalBounds().height)));

    int bulletType = rand() % 3;

    switch (bulletType)
    {
    case 0:
        newBullet.bulletVelocity = 3.f;
        break;
    case 1:
        newBullet.bulletVelocity = 4.f;
        break;
    case 2:
        newBullet.bulletVelocity = 5.f;
        break;
    default:
        newBullet.bulletVelocity = 4.f;
        break;
    }

    newBullet.bulletSprite.move(newBullet.bulletVelocity, 0.f);

    this->bullets.push_back(newBullet);
}

void Bullet::update(sf::RenderWindow &window)
{

    if (this->bullets.size() < this->maxBullets)
    {
        if (this->bulletSpawnTimer >= this->bulletSpawnTimerMax)
        {
            this->spawnBullet(window);
            this->bulletSpawnTimer = 0.f;
        }
        else
        {
            this->bulletSpawnTimer += 1.f;
        }
    }

    for (int i = 0; i < this->bullets.size(); i++)
    {
        this->bullets[i].bulletSprite.move(this->bullets[i].bulletVelocity, 0.f);

        if (this->bullets[i].bulletSprite.getPosition().x > window.getSize().x)
        {
            this->bullets.erase(this->bullets.begin() + i);
        }
    }
}

void Bullet::render(sf::RenderWindow &window)
{
    for (auto &e : this->bullets)
    {
        window.draw(e.bulletSprite);
    }
}