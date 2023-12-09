#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>

struct BulletInfo
{
    sf::Sprite bullet;
    float bulletVelocity;
};

class Bullet
{
private:
    /* data */
    sf::Sprite bullet;
    sf::Texture bulletTexture;

    float bulletSpawnTimer, bulletSpawnTimerMax;
    int maxBullets;
    int ground_start = 65;

public:
    Bullet();
    ~Bullet();

    std::vector<BulletInfo> bullets;
    // void initBullets();
    void spawnBullet(sf::RenderWindow &window);
    void update(sf::RenderWindow &window);
    void render(sf::RenderWindow &window);
};

Bullet::Bullet() : bulletSpawnTimer(0.f), bulletSpawnTimerMax(10.f), maxBullets(4)
{
    if (this->bulletTexture.loadFromFile("assets/bomb.png"))
    {
        this->bullet.setTexture(this->bulletTexture);
    }
    else
    {
        std::cout << "ERROR::BULLET::COULD_NOT_LOAD_SKIN" << std::endl;
    }
}

Bullet::~Bullet()
{
}

void Bullet::spawnBullet(sf::RenderWindow &window)
{
    BulletInfo bulletInfo;

    bulletInfo.bullet.setTexture(this->bulletTexture);
    bulletInfo.bullet.setScale(0.1f, 0.1f);
    bulletInfo.bullet.setPosition(
        0.f - bulletInfo.bullet.getGlobalBounds().width,
        static_cast<float>(rand() % static_cast<int>((window.getSize().y - ground_start) - bulletInfo.bullet.getGlobalBounds().height)));

    int bulletType = rand() % 3;

    switch (bulletType)
    {
    case 0:
        bulletInfo.bulletVelocity = 3.f;
        break;
    case 1:
        bulletInfo.bulletVelocity = 4.f;
        break;
    case 2:
        bulletInfo.bulletVelocity = 5.f;
        break;
    default:
        bulletInfo.bulletVelocity = 4.f;
        break;
    }

    bulletInfo.bullet.move(bulletInfo.bulletVelocity, 0.f);
    this->bullets.push_back(bulletInfo);
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
        this->bullets[i].bullet.move(this->bullets[i].bulletVelocity, 0.f);
        if (this->bullets[i].bullet.getPosition().x > window.getSize().x)
        {
            this->bullets.erase(this->bullets.begin() + i);
        }
    }
}

void Bullet::render(sf::RenderWindow &window)
{
    for (auto &e : this->bullets)
    {
        window.draw(e.bullet);
    }
}