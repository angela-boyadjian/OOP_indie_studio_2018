/*
** EPITECH PROJECT, 2019
** DisplayLoader.cpp 
** File description:
** basile.lamarque@epitech.eu
*/

#include "DisplayLoader.hpp"
#include "Display.hpp"

#define posX 5400
#define posY 800
#define posZ 5200

DisplayLoader::DisplayLoader(const std::shared_ptr<IDisplay> &d) :
    _d(d)
{}

bool DisplayLoader::addTileToMap(const SpriteInfo &info, float size)
{
    if (info._messPath == "Cube")
        _d->getMap().emplace_back(_d->_scenes->addCubeSceneNode(size, 0, -1));
    else {
        irr::core::vector3df scale(size / info._size.X,
                                   size / info._size.Y,
                                   size / info._size.Z);
        _d->getMap().emplace_back(_d->_scenes->addAnimatedMeshSceneNode(
            _d->_scenes->getMesh(info._messPath.c_str())));
        _d->getMap().back()->setScale(scale);
        _d->getMap().back()->setRotation(irr::core::vector3df(-90.0, 0, 0));
    }
    _d->getMap().back()->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    _d->getMap().back()->setMaterialTexture(0, _d->_driver->getTexture(
        info._texPath.c_str()));
    return true;
}

void DisplayLoader::preloadMapWall(const MapData &map)
{
    auto x = 0.0f + posX;
    auto y = 10.0f + posY;
    auto z = 40.0f + posZ;
    auto pos = map._rulesWall.find('/');

    for (__attribute__((unused)) auto tile : map._mapWall[0]) {
        addTileToMap(pos->second, 10.0f);
        _d->getMap().back()->setPosition(irr::core::vector3df(x, 10.0f + posY, z));
        x += 10.0f;
    }
    for (int i = 0; i != map._mapWall.size() + 2; i++) {
        addTileToMap(pos->second, 10.0f);
        _d->getMap().back()->setPosition(irr::core::vector3df(x, y, z));
        addTileToMap(pos->second, 10.0f);
        _d->getMap().back()->setPosition(irr::core::vector3df(0 - 10.0f + posX, y, z));
//        y -= 10.0f;
        z -= 10;
    }
    x = 0.0f + posX;
    for (__attribute__((unused)) auto tile : map._mapWall[0]) {
        addTileToMap(pos->second, 10.0f);
        _d->getMap().back()->setPosition(irr::core::vector3df(x, y, z + 10));
        x += 10.0f;
    }
}

void DisplayLoader::loadMapWall(const MapData &map)
{
    auto x = 0.0f + posX;
    auto y = 10.0f + posY;
    auto z = 30.0f + posZ;

    preloadMapWall(map);
    for (auto &line : map._mapWall) {
        for (auto tile : line) {
            auto pos = map._rulesWall.find(tile);
            if (pos != map._rulesWall.end()) {
                addTileToMap(pos->second, 9.0f);
                _d->getMap().back()->setPosition(irr::core::vector3df(x, y, z));
            }
            x += 10.0f;
        }
        x = 0.0f + posX;
        z -= 10;
//        y -= 10.0f;
    }
}

void DisplayLoader::loadMapGround(const MapData &map)
{
    unsigned int value = 0;
    auto x = 0.0f + posX;
    auto y = 10.0f + posY;
    auto z = 30.0f + posZ;
    auto base = map._rulesGround.begin()->first;

    for (auto &line : map._mapWall) {
        for (__attribute__((unused)) auto tile : line) {
            auto pos = map._rulesGround.find(base - value);
            if (pos != map._rulesGround.end()) {
                addTileToMap(pos->second, 10.0f);
                _d->getMap().back()->setPosition(irr::core::vector3df(x, y - 10, z));
            }
            value += 1;
            if (value > map._rulesGround.size() - 1)
                value = 0;
            x += 10.0f;
        }
        x = 0 + posX;
        z -= 10;
        //        y -= 10.0f;
    }
}

void DisplayLoader::loadMap(const MapData &map)
{
    loadMapWall(map);
    loadMapGround(map);
}

static const char *res = "../resources/models/Character/Bomberman.MD3";

void    DisplayLoader::loadPlayer(const ACharacter::Color &color,
        const std::vector<std::string> &textures)
{
    _d->addNewAnimation(res, textures[static_cast<int>(color)].c_str(),
                        std::make_tuple(6, 6, 6));
}

void    DisplayLoader::loadGame(const std::unique_ptr<AGame> &game)
{
    for (auto &bot : game->getBots())
        loadPlayer(bot->_color, bot->_textures);
    for (auto &player : game->getPlayers())
        loadPlayer(player->_color, player->_textures);
}

void    DisplayLoader::loadMenu(const std::unique_ptr<Menu> &menu)
{
    Display::Gui const &gui = _d->getGui();
    Display::Device const &device = _d->getDevice();
    auto screenSize = _d->getScreenSize();

    gui->addButton(irr::core::rect<irr::s32>(10, 240, 110, 240 + 32), 0,
    101, L"Quit", L"Exits Program");
    gui->addButton(irr::core::rect<irr::s32>(screenSize.Width - 110, 240, screenSize.Width - 10, 240 + 32), 0,
        101, L"Start Game", L"Start Game");
    Events *receiver = new Events(device);
    device->setEventReceiver(receiver);
}