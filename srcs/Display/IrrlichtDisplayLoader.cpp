/*
** EPITECH PROJECT, 2019
** IrrlichtDisplayLoader.cpp 
** File description:
** basile.lamarque@epitech.eu
*/

#include "IrrlichtDisplayLoader.hpp"
#include "IDisplay.hpp"

#define posX 5400
#define posY 800
#define posZ 5200

IrrlichtDisplayLoader::IrrlichtDisplayLoader(const std::shared_ptr<IDisplay> &d) :
    _d(d)
{}

void IrrlichtDisplayLoader::loadCube(float size)
{
    _d->getMap().emplace_back(_d->_scenes->addCubeSceneNode(size, 0, -1));
}

void IrrlichtDisplayLoader::loadMess(const SpriteInfo &info, float size)
{
    auto mesh = _d->_scenes->getMesh(info._messPath.c_str());
    irr::core::vector3df scale(size / info._size.X,
                               size / info._size.Y,
                               size / info._size.Z);

    _d->getMap().emplace_back(_d->_scenes->addAnimatedMeshSceneNode(mesh));
    _d->getMap().back()->setScale(scale);
}

bool IrrlichtDisplayLoader::loadTileMap(const SpriteInfo &info, float size)
{
    if (info._messPath == "Cube")
        loadCube(size);
    else
        loadMess(info, size);
    _d->getMap().back()->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    _d->getMap().back()->setMaterialTexture(0, _d->_driver->getTexture(
        info._texPath.c_str()));
    return true;
}

void IrrlichtDisplayLoader::preloadMapWall(const MapData &map)
{
    auto x = 0.0f + posX;
    auto y = 10.0f + posY;
    auto z = 40.0f + posZ;
    auto pos = map._rulesWall.find('/');

    for (__attribute__((unused)) auto tile : map._mapWall[0]) {
        addTileToMap(irr::core::vector3df(x, 10.0f + posY, z), pos->second);
        x += 10.0f;
    }
    for (int i = 0; i != map._mapWall.size() + 2; i++) {
        addTileToMap(irr::core::vector3df(x, y, z), pos->second);
        addTileToMap(irr::core::vector3df(0 - 10.0f + posX, y, z), pos->second);
        z -= 10;
    }
    x = 0.0f + posX;
    for (__attribute__((unused)) auto tile : map._mapWall[0]) {
        addTileToMap(irr::core::vector3df(x, y, z + 10), pos->second);
        x += 10.0f;
    }
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
                addTileToMap(irr::core::vector3df(x, y, z), pos->second);
            x += 10.0f;
        }
        x = 0.0f + posX;
        z -= 10;
    }
}

void
IrrlichtDisplayLoader::addTileToMap(const irr::core::vector3df &pos, const SpriteInfo &info)
{
    loadTileMap(info, 10.0f);
    _d->getMap().back()->setPosition(pos);
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
                addTileToMap(irr::core::vector3df(x, y - 10, z), pos->second);
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

void IrrlichtDisplayLoader::loadGame(const std::unique_ptr<AGame> &game)
{
    for (auto &bot : game->getBots())
        loadPlayer(bot->_color, bot->_textures);
    for (auto &player : game->getPlayers())
        loadPlayer(player->_color, player->_textures);
}

void    IrrlichtDisplayLoader::loadMenu(const std::unique_ptr<Menu> &menu)
{
    IDisplay::Gui const &gui = _d->getGui();
    IDisplay::Device const &device = _d->getDevice();
    auto screenSize = _d->getScreenSize();

    gui->addButton(irr::core::rect<irr::s32>(10, 240, 110, 240 + 32), 0,
    101, L"Quit", L"Exits Program");
    gui->addButton(irr::core::rect<irr::s32>(screenSize.Width - 110, 240, screenSize.Width - 10, 240 + 32), 0,
        102, L"Start Game", L"Start Game");
    Events *receiver = new Events(device);
    device->setEventReceiver(receiver);
}
