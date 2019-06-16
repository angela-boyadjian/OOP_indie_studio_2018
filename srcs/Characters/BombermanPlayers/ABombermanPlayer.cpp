/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** ABombermanPlayer
*/

#include "ABombermanPlayer.hpp"

ABombermanPlayer::ABombermanPlayer(const std::size_t &enb, const MapPos &pos,
                       const Color &color) : ACharacter(enb, pos, color),
        _fireRange(1), _bombNumber(1), _maxBombNumber(1), _3dPos(std::make_tuple(0, 0))
{
    _textures = std::vector<std::string>({"../resources/models/Character/BlackBombermanTextures.png",
               "../resources/models/Character/PinkBombermanTextures.png",
               "../resources/models/Character/RedBombermanTextures.png",
               "../resources/models/Character/WhiteBombermanTextures.png"});
    // _bombs.push_back(std::make_unique<Bomb>());
    _bombs.emplace_back(Bomb());
}

// SETTERS
const bool                  &ABombermanPlayer::canShoot() const { return _canShoot; }
const ACharacter::Action    &ABombermanPlayer::getDirection() const { return _action; }
const std::size_t           &ABombermanPlayer::getFireRange() const { return _fireRange; }

// INCREASER
void    ABombermanPlayer::increaseSpeed() { _speed += 1; }
void    ABombermanPlayer::increaseFireRange() { _fireRange += 1; }
void    ABombermanPlayer::increaseBombNumber() { _bombNumber += 1; }

// DECREASER
void    ABombermanPlayer::decreaseBombNumber() { _bombNumber -= 1; }

void    ABombermanPlayer::canShoot() { _canShoot = true; }

void    ABombermanPlayer::moveUp()
{
    if (!_walls[0]) {
        std::get<1>(_pos) += 1;
        std::get<2>(_pos) += 1;
        std::get<1>(_3dPos) -= 1;
        std::get<1>(_2dPos) = static_cast<int>(std::get<1>(_3dPos) / 10);
    }
}

void    ABombermanPlayer::moveDown()
{
    if (!_walls[1]) {
        std::get<1>(_pos) -= 1;
        std::get<1>(_3dPos) += 1;
        std::get<1>(_2dPos) = static_cast<int>(std::get<1>(_3dPos) / 10);
        std::get<2>(_pos) -= 1;
    }
}

void    ABombermanPlayer::moveLeft()
{
    if (!_walls[2]) {
        std::get<0>(_pos) -= 1;
        std::get<0>(_3dPos) -= 1;
        std::get<0>(_2dPos) = static_cast<int>(std::get<0>(_3dPos) / 10);
    }
}


void    ABombermanPlayer::moveRight()
{
    if (!_walls[3]) {
        std::get<0>(_pos) += 1;
        std::get<0>(_3dPos) += 1;
        std::get<0>(_2dPos) = static_cast<int>(std::get<0>(_3dPos) / 10);
    }
}

void    ABombermanPlayer::isWallUp(IDisplay *d)
{
    std::get<2>(_pos) += 2;
    d->changeModelPos(getEntityNb(), std::make_tuple(std::get<0>(_pos), 0, std::get<2>(_pos)));
    _walls[0] = d->isCollision(getEntityNb());
    std::get<2>(_pos) -= 2;
}

void    ABombermanPlayer::isWallDown(IDisplay *d)
{
    std::get<2>(_pos) -= 2;
    d->changeModelPos(getEntityNb(), std::make_tuple(std::get<0>(_pos), 0, std::get<2>(_pos)));
    _walls[1] = d->isCollision(getEntityNb());
    std::get<2>(_pos) += 2;
}

void    ABombermanPlayer::isWallLeft(IDisplay *d)
{
    std::get<0>(_pos) -= 2;
    d->changeModelPos(getEntityNb(), std::make_tuple(std::get<0>(_pos), 0, std::get<2>(_pos)));
    _walls[2] = d->isCollision(getEntityNb());
    std::get<0>(_pos) += 2;
}

void    ABombermanPlayer::isWallRight(IDisplay *d)
{
    std::get<0>(_pos) += 2;
    d->changeModelPos(getEntityNb(), std::make_tuple(std::get<0>(_pos), 0, std::get<2>(_pos)));
    _walls[3] = d->isCollision(getEntityNb());
    std::get<0>(_pos) -= 2;
}

void    ABombermanPlayer::isWalls(IDisplay *d)
{
    isWallUp(d);
    isWallDown(d);
    isWallLeft(d);
    isWallRight(d);
    d->changeModelPos(getEntityNb(), std::make_tuple(std::get<0>(_pos), 0, std::get<2>(_pos)));
}


std::vector<Bomb> const &ABombermanPlayer::getBombs() const
{
    return _bombs;
}

std::size_t ABombermanPlayer::getBombNb() const
{
    return _maxBombNumber;
}

void    ABombermanPlayer::bomb(IDisplay *d)
{
    auto b = _bombs[0];

    // if (!b.isPlaced() and _bombNumber > 0) {
        decreaseBombNumber();
        b.place();
        b.setOn(true);
        d->setBombState(getEntityNb(), true);
        b.explode(d);
    // }
}