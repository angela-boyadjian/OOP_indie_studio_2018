/*
** EPITECH PROJECT, 2019
** IrrlichtDisplayLoader.cpp 
** File description:
** basile.lamarque@epitech.eu
*/

#include "Bomb.hpp"

#include "IrrlichtDisplayLoader.hpp"

#define posX 5400.0f
#define posY 800.0f
#define posZ 5200.0f

IrrlichtDisplayLoader::IrrlichtDisplayLoader(const std::shared_ptr<IDisplay> &d)
    :
    _d(d)
{}

void IrrlichtDisplayLoader::loadCube(float size, IDisplay::Map3D &dest)
{
    dest.emplace_back(_d->_scenes->addCubeSceneNode(size, 0, -1));
}

void IrrlichtDisplayLoader::loadMess(const SpriteInfo &info, float size,
                                     IDisplay::Map3D &dest)
{
    auto mesh = _d->_scenes->getMesh(info._messPath.c_str());
    irr::core::vector3df scale(size / info._size.X,
                               size / info._size.Y,
                               size / info._size.Z);

    dest.emplace_back(_d->_scenes->addAnimatedMeshSceneNode(mesh));
    dest.back()->setScale(scale);
}

bool IrrlichtDisplayLoader::loadTileMap(const SpriteInfo &info, float size,
                                        IDisplay::Map3D &dest)
{
    if (info._messPath == "Cube")
        loadCube(size, dest);
    else
        loadMess(info, size, dest);
    dest.back()->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    dest.back()->setMaterialTexture(0, _d->_driver->getTexture(
        info._texPath.c_str()));
    return true;
}

void IrrlichtDisplayLoader::loadMapEdgeTop(const MapData &map)
{
    auto x = posX - 10.0f;
    auto z = 40.0f + posZ;
    auto pos = map._rulesWall.find('/');

    for (__attribute__((unused)) auto i = 0;
         map._mapWall[0].size() + 2 != i; i++) {
        addTileToMap(irr::core::vector3df(x, 10.0f + posY, z), pos->second,
                     10.0f);
        x += 10.0f;
    }
}

void IrrlichtDisplayLoader::loadMapEdgeSide(const MapData &map)
{
    auto y = 10.0f + posY;
    auto z = 30.0f + posZ;
    auto pos = map._rulesWall.find('/');
    auto toto = map._rulesWall.find('x');
    auto last = map._mapWall[0].size();

    for (int i = 0; i != map._mapWall.size(); i++) {
        auto x = map._mapWall[i].size() * 10.0f + posX;
        addTileToMap(irr::core::vector3df(x, y, z), pos->second, 10.0f);
        addTileToMap(irr::core::vector3df(posX - 10.0f, y, z), pos->second,
                     10.0f);
        z -= 10;
    }
}

void IrrlichtDisplayLoader::loadMapEdgeLow(const MapData &map)
{
    auto x = posX - 10.0f;
    auto y = 10.0f + posY;
    auto z = 30.0f + posZ - (map._mapWall.size() * 10);
    auto pos = map._rulesWall.find('/');

    for (__attribute__((unused)) auto i = 0;
         map._mapWall[0].size() + 2 != i; i++) {
        addTileToMap(irr::core::vector3df(x, y, z), pos->second,
                     10.0f);
        x += 10.0f;
    }
}

void IrrlichtDisplayLoader::preloadMapWall(const MapData &map)
{
    loadMapEdgeTop(map);
    loadMapEdgeSide(map);
    loadMapEdgeLow(map);
}

void IrrlichtDisplayLoader::loadMapWall(const MapData &map)
{
    auto x = 0.0f + posX;
    auto y = 10.0f + posY;
    auto z = 30.0f + posZ;

    preloadMapWall(map);
    for (auto &line : map._mapWall) {
        for (auto tile : line) {
            auto pos = map._rulesWall.find(tile);
            if (pos != map._rulesWall.end())
                addTileToMap(irr::core::vector3df(x, y, z), pos->second, 8.0f);
            x += 10.0f;
        }
        x = 0.0f + posX;
        z -= 10;
    }
}

void
IrrlichtDisplayLoader::addTileToMap(const irr::core::vector3df &pos,
                                    const SpriteInfo &info, float size)
{
    if (info._referTo == "2") {
        loadTileMap(info, size, _d->getColiMap());
        _d->getColiMap().back()->setPosition(pos);
    } else {
        loadTileMap(info, size, _d->getNonColiMap());
        _d->getNonColiMap().back()->setPosition(pos);
    }
}

void IrrlichtDisplayLoader::loadMapGround(const MapData &map)
{
    unsigned int value = 0;
    auto x = 0.0f + posX;
    auto y = 10.0f + posY;
    auto z = 30.0f + posZ;
    auto base = map._rulesGround.begin()->first;

    for (auto &line : map._mapWall) {
        for (__attribute__((unused)) auto tile : line) {
            auto pos = map._rulesGround.find(base - value);
            if (pos != map._rulesGround.end())
                addTileToMap(irr::core::vector3df(x, y - 10, z), pos->second,
                             10.0f);
            value += 1;
            if (value > map._rulesGround.size() - 1)
                value = 0;
            x += 10.0f;
        }
        x = 0 + posX;
        z -= 10;
    }
}

void IrrlichtDisplayLoader::loadMap(const MapData &map)
{
    loadMapWall(map);
    loadMapGround(map);
}

static const char *res = "../resources/models/Character/Bomberman.MD3";

void IrrlichtDisplayLoader::loadPlayer(const ACharacter::Color &color,
                                       const std::vector<std::string> &textures)
{
    _d->addNewAnimation(res, textures[static_cast<int>(color)].c_str(),
                        std::make_tuple(6, 6, 6));
}

void
IrrlichtDisplayLoader::loadBomb(char const *res, std::string const &texture)
{
    _d->addNewAnimation(res, texture.c_str(), std::make_tuple(2, 2, 2));
}

void IrrlichtDisplayLoader::loadGame(const std::unique_ptr<AGame> &game)
{
    Bomb b;

    for (auto &bot : game->getBots())
        loadPlayer(bot->_color, bot->_textures);
    for (auto &player : game->getPlayers()) {
        loadPlayer(player->_color, player->_textures);
        loadBomb(b.getRes().c_str(), b.getTexture());
    }
}