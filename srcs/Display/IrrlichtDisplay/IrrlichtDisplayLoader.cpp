/*
** EPITECH PROJECT, 2019
** IrrlichtDisplayLoader.cpp 
** File description:
** basile.lamarque@epitech.eu
*/

#include "Bomb.hpp"

#include <irrlicht.h>
#include "IrrlichtDisplayLoader.hpp"
#include "IDisplay.hpp"

#define posX -60
#define posY -90
#define posZ 75

IrrlichtDisplayLoader::IrrlichtDisplayLoader(const std::shared_ptr<IDisplay> &d, std::shared_ptr<irr::scene::ISceneNode> &father, irr::scene::ISceneManager *manager)
    :
    _d(d),
    _father(father),
    _manager(manager)
{}

void IrrlichtDisplayLoader::loadCube(float size, IDisplay::Map3D &dest)
{
    dest.emplace_back(_manager->addCubeSceneNode(size, _father.get(), -1));
}

void IrrlichtDisplayLoader::loadMess(const SpriteInfo &info, float size,
                                     IDisplay::Map3D &dest)
{
    auto mesh = _manager->getMesh(info._messPath.c_str());
    irr::core::vector3df scale(size / info._size.X,
                               size / info._size.Y,
                               size / info._size.Z);

    dest.emplace_back(_manager->addAnimatedMeshSceneNode(mesh, _father.get()));
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

void IrrlichtDisplayLoader::loadEdge(const MapData &map)
{
    int start = 0;

    while (map._mapWall[start][0] == ' ') {
        std::cout << map._mapWall[start][0] << std::endl;
        start++;
    }
}

void IrrlichtDisplayLoader::loadMapEdgeTop(const MapData &map)
{
    auto x = posX - 10.0f;
    auto z = 40.0f + posZ;
    auto pos = map._rulesWall.find('/');

    for (__attribute__((unused)) std::size_t i = 0;
         map._mapWall[0].size() + 2 != i; ++i) {
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

    for (std::size_t i = 0; i != map._mapWall.size(); i++) {
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

    for (__attribute__((unused)) std::size_t i = 0;
         map._mapWall[0].size() + 2 != i; i++) {
        addTileToMap(irr::core::vector3df(x, y, z), pos->second,
                     10.0f);
        x += 10.0f;
    }
}

void IrrlichtDisplayLoader::preloadMapWall(const MapData &map)
{
    //loadEdge(map);
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

void IrrlichtDisplayLoader::addTileToMap(const irr::core::vector3df &pos,
                                    const SpriteInfo &info, float size)
{
    irr::core::vector3df toto = pos;
    toto.Y -= 7;
    if (info._is_destructible) {
        loadTileMap(info, size, _d->getColiMap());
        _d->getColiMap().back()->setPosition(toto);
    } else {
        loadTileMap(info, size, _d->getNonColiMap());
        _d->getNonColiMap().back()->setPosition(toto);
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
    setBombsPos();
    setExplosionPos();
}

static const char *res = "../resources/models/Character/Bomberman.MD3";

void IrrlichtDisplayLoader::loadPlayer(const ACharacter::Color &color,
                                       const std::vector<std::string> &textures)
{

    auto newScene = _manager->addAnimatedMeshSceneNode(_manager->getMesh("../resources/models/Character/Bomberman.MD3"), _father.get());
    newScene->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    newScene->setMD2Animation(irr::scene::EMAT_STAND);
    newScene->setScale(irr::core::vector3df(6,6,6));
    newScene->setRotation(irr::core::vector3df(0, 0, 0));
    newScene->setPosition(irr::core::vector3df(5400, 810, 5200));
    newScene->setAnimationSpeed(30);
    newScene->setLoopMode(true);
    newScene->setFrameLoop(0, 27);
    newScene->setMaterialTexture(0, _d->getDevice()->getVideoDriver()->getTexture(textures[static_cast<int>(color)].c_str()));
    _d->_meshsScene.push_back(std::unique_ptr<irr::scene::IAnimatedMeshSceneNode>(newScene));
    /*_d->addNewAnimation(res, textures[static_cast<int>(color)].c_str(),
                        std::make_tuple(6, 6, 6));*/
}

void    IrrlichtDisplayLoader::setExplosionPos()
{
    auto x = -60;
    auto y = -90;
    auto z = 105;

    for (auto j {0}; j < _d->getExplosionMap().size(); ++j) {
        auto x_tmp = x;
        for (auto i {0}; i < _d->getExplosionMap()[j].size(); ++i) {
            _d->setExplosion(i, j, irr::core::vector3df(x_tmp, y, z));
            x_tmp += 10;
        }
        z -= 10;
    }
}

void    IrrlichtDisplayLoader::loadExplosion(std::size_t y, std::size_t x)
{
    for (auto j {0}; j < y; ++j) {
        auto line = IDisplay::BombsVec();
        for (auto i {0}; i < x; ++i) {
            auto newScene = _manager->addCubeSceneNode(10.0f, _father.get());
            newScene->setMaterialFlag(irr::video::EMF_LIGHTING, false);
            newScene->setScale(irr::core::vector3df(1,1,1));
            newScene->setRotation(irr::core::vector3df(0, 0, 0));
            newScene->setPosition(irr::core::vector3df(5400, 810, 5200));
            newScene->setMaterialTexture(0, _d->getDevice()->getVideoDriver()->getTexture("../resources/textures/explosion.jpg"));


          /*  _d->addNewAnimation("../resources/models/Bomb/Bomb.obj",
                                "../resources/models/Bomb/Bomb.png", std::make_tuple(1, 1, 1));
            auto tmp = _d->_sceneManagers.at("game")->getMeshScenes();*/
            line.emplace_back(newScene);
        }
        _d->addExplosion(line);
    }
}

void    IrrlichtDisplayLoader::setBombsPos()
{
    auto x = -60;
    auto y = -90;
    auto z = 105;

    for (auto j {0}; j < _d->getBombsMap().size(); ++j) {
        auto x_tmp = x;
        for (auto i {0}; i < _d->getBombsMap()[j].size(); ++i) {
            _d->setBombs(i, j, irr::core::vector3df(x_tmp, y, z));
            x_tmp += 10;
        }
        z -= 10;
    }
   // exit(0);
}

void    IrrlichtDisplayLoader::loadBomb_b2(std::size_t y, std::size_t x)
{
    for (auto j {0}; j < y; ++j) {
        auto line = IDisplay::BombsVec();
        for (auto i {0}; i < x; ++i) {

            auto newScene = _manager->addAnimatedMeshSceneNode(_manager->getMesh("../resources/models/Bomb/Bomb.obj"), _father.get());
            newScene->setMaterialFlag(irr::video::EMF_LIGHTING, false);
            newScene->setMD2Animation(irr::scene::EMAT_STAND);
            newScene->setScale(irr::core::vector3df(1,1,1));
            newScene->setRotation(irr::core::vector3df(0, 0, 0));
            newScene->setPosition(irr::core::vector3df(0, 0, 0));
            newScene->setAnimationSpeed(30);
            newScene->setLoopMode(true);
            newScene->setFrameLoop(0, 27);
            newScene->setMaterialTexture(0, _d->getDevice()->getVideoDriver()->getTexture("../resources/models/Bomb/Bomb.png"));
          /*  _d->addNewAnimation("../resources/models/Bomb/Bomb.obj",
            "../resources/models/Bomb/Bomb.png", std::make_tuple(1, 1, 1));

            auto tmp = _d->_sceneManagers.at("game")->getMeshScenes();*/
            line.emplace_back(newScene);
        }
        _d->addBombs(line);
    }
}

void IrrlichtDisplayLoader::loadBomb(Bomb &bomb, IDisplay::BombsVec &dest)
{
    auto mesh = _manager->getMesh(bomb.getRes().c_str());
    auto scene = _manager->addAnimatedMeshSceneNode(mesh);

    dest.emplace_back(scene);
    irr::core::vector3df scale(2 / 2,
                               2 / 2,
                               2/ 2);
    dest.back()->setScale(scale);
    irr::core::vector3df pos(5400, 815, 5200);
    dest.back()->setPosition(pos);
    dest.back()->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    dest.back()->setMaterialTexture(0, _d->_driver->getTexture(
        bomb.getTexture().c_str()));
    dest.back()->setVisible(false);
    // bomb.addMesh(scene);
}

void IrrlichtDisplayLoader::loadGame(const std::unique_ptr<AGame> &game)
{
    for (auto &bot : game->getBots())
        loadPlayer(bot->_color, bot->_textures);
    for (auto &player : game->getPlayers()) {
        loadPlayer(player->_color, player->_textures);
        loadBomb_b2(11, 13);
        loadExplosion(11, 13);
    }
}

void    IrrlichtDisplayLoader::loadMenu(const std::unique_ptr<Menu> &menu)
{
    IDisplay::Gui const &gui = _d->getGui();
    IDisplay::Device const &device = _d->getDevice();
    auto screenSize = _d->getScreenSize();
    auto image = _d->_driver->getTexture("./../resources/ui/bombermanBackground.png");

    auto img = gui->addImage(irr::core::rect<irr::s32>(0, 0, screenSize.Width, screenSize.Height));
    img->setImage(image);
    img->setScaleImage(true);
    gui->addButton(irr::core::rect<irr::s32>(screenSize.Width / 2 - 300, 440,
        screenSize.Width / 2 + 300, 440 + 42), 0, 102, L"Start Game",
        L"Start Game");
    gui->addButton(
        irr::core::rect<irr::s32>(screenSize.Width / 2 - 300, 440 + 42 + 10,
           screenSize.Width / 2 + 300, 440 + 42 + 10 + 42), 0, 104
           , L"Load Game", L"Load Game");
    gui->addButton(
        irr::core::rect<irr::s32>(screenSize.Width / 2 - 300, 440 + 82 + 20,
            screenSize.Width / 2 + 300, 440 + 84 + 20 + 42), 0, 103,
        L"Settings", L"Settings");
    gui->addButton(
        irr::core::rect<irr::s32>(screenSize.Width / 2 - 300, 440 + 126 + 30,
            screenSize.Width / 2 + 300, 440 + 126 + 30 + 42), 0, 101, L"Quit",
        L"Exits Program");
}

IDisplay::Object    *IrrlichtDisplayLoader::createBonus(const std::string &path)
{
    // CHANGE WITH POWERUP MODEL
    auto newScene = _manager->addCubeSceneNode(8.0f, _father.get());
    newScene->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    //_manager->getMesh("../resources/models/Bomb/Bomb.obj"), _father.get());
    newScene->setScale(irr::core::vector3df(1, 0.1,1));
    newScene->setRotation(irr::core::vector3df(0, -90, 0));
    newScene->setPosition(irr::core::vector3df(0, 0, 0));
    std::cout << path << std::endl;
    newScene->setMaterialTexture(0, _d->getDevice()->getVideoDriver()->getTexture(path.c_str()));
    return newScene;
}