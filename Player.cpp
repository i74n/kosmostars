#include "Player.h"
#include <sstream>

Player::Player(Image& image)
{
    scores = 100;
    shot_cooldown = 0;
    makeTexture(image);
    setPosition(0, 270);
    buffTime = 0;
    buff = nobuff;
}

Status Player::update(float time)
{
    if (scores <= 0)
        return status = dead;
    shot_cooldown += time;

    if (getBuff() == demolisher) {
        setBuff(nobuff);
        return DEMOLISH;
    }
    if (getBuff() != nobuff)
        buffTime += time;
    if (buffTime >= 1) {
        setBuff(nobuff);
        buffTime = 0;
    }

    if (position.y > 0 && Keyboard::isKeyPressed(Keyboard::Up))
        position.y -= 0.5 * time * 10000;
    else if (position.y + size.y < 540 && Keyboard::isKeyPressed(Keyboard::Down))
        position.y += 0.5 * time * 10000;
    else if (Keyboard::isKeyPressed(Keyboard::Space) && shot_cooldown > 0.01) {
        shot_cooldown = 0;
        return status = shoot;
    }
    sprite.setPosition(position);
    return status = alive;
}

void Player::setBuff(Buff buff)
{
    this->buff = buff;
    buffTime = 0;
}

std::string toStr(float f)
{
    std::stringstream ss;
    ss << f;
    return ss.str();
}

std::string Player::getScores()
{
    return toStr(scores);
}

std::string Player::getBuffTimeLeft()
{
    return toStr(1 - buffTime);
}

void Player::setScores(int crement)
{
    switch (buff) {
    case x2:
        scores += 2 * crement;
        break;
    case shield:
        if (crement > 0)
            scores += crement;
        break;
    default:
        scores += crement;
    }
}

Status Player::getStatus()
{
    return status;
}

Buff Player::getBuff()
{
    return buff;
}
