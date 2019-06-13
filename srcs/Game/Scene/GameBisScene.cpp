/*
** EPITECH PROJECT, 2019
** GameScene.cpp 
** File description:
** basile.lamarque@epitech.eu
*/

#include <AGame.hpp>
#include <Bomberman/BombermanGame.hpp>
#include "SceneException.hpp"
#include "GameBisScene.hpp"
#include "Map.hpp"

GameBisScene::GameBisScene(std::shared_ptr<irr::IrrlichtDevice> device,
                           irr::scene::ISceneNode *father,
                           const std::string &name,
                           std::shared_ptr<Events> event,  std::shared_ptr<IDisplay> display) :
    _master(device->getSceneManager()->addEmptySceneNode(father)),
    _manager(device->getSceneManager()),
    _name(name),
    _is_load(false),
    _device(device),
    _event(event),
    _display(display)
{
    _master->setVisible(false);
}

std::string GameBisScene::runScene()
{
    // TEMPO - REPLACE IT BY GENERIC METHOD
    if (!_is_load)
        throw SceneException("Scene is not load", _name.c_str());
    _master->setVisible(true);
    action();
    return _name;
}

// NOTE LOAD

// NOTE LOAD MAP

void GameBisScene::loadCube(float size, GameBisScene::Map3D &dest)
{
    dest.emplace_back(_manager->addCubeSceneNode(size, _master.get(), -1));
}

void GameBisScene::loadMess(const SpriteInfo &info, float size,
                            GameBisScene::Map3D &dest)
{
    auto mesh = _manager->getMesh(info._messPath.c_str());
    irr::core::vector3df scale(size / info._size.X,
                               size / info._size.Y,
                               size / info._size.Z);

    dest.emplace_back(_manager->addAnimatedMeshSceneNode(mesh));
    dest.back()->setScale(scale);
}

bool GameBisScene::loadTileMap(const SpriteInfo &info, float size,
                               GameBisScene::Map3D &dest)
{
    if (info._messPath == "Cube")
        loadCube(size, dest);
    else
        loadMess(info, size, dest);
    dest.back()->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    dest.back()->setMaterialTexture(0, _device->getVideoDriver()->getTexture(
        info._texPath.c_str()));
    return true;
}

void
GameBisScene::addTileToMap(const irr::core::vector3df &pos,
                           const SpriteInfo &info, float size)
{
    if (info._is_destructible) {
        loadTileMap(info, size, _coliMap);
        _coliMap.back()->setPosition(pos);
    } else {
        loadTileMap(info, size, _noncoliMap);
        _noncoliMap.back()->setPosition(pos);
    }
}

void GameBisScene::loadMapEdgeTop(const MapData &map)
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

void GameBisScene::loadMapEdgeSide(const MapData &map)
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

void GameBisScene::loadMapEdgeLow(const MapData &map)
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

void GameBisScene::preloadMapWall(const MapData &map)
{
    loadMapEdgeTop(map);
    loadMapEdgeSide(map);
    loadMapEdgeLow(map);
}

void GameBisScene::loadMapWall(const MapData &map)
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

void GameBisScene::loadMapGround(const MapData &map)
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

void GameBisScene::loadMapAsset(const MapData &map)
{
    loadMapWall(map);
    loadMapGround(map);
}

std::vector<std::shared_ptr<Player>> GameBisScene::loadPlayer()
{
    auto players = std::vector<std::shared_ptr<Player>>();

    players.push_back(
        std::make_unique<Player>(Player(0, ACharacter::Color::BLACK,
                                        std::make_tuple(std::size_t(0),
                                                        std::size_t(0),
                                                        std::size_t(0)))));

    return players;
}

std::vector<std::shared_ptr<Bot>> GameBisScene::loadBot()
{
    auto bots = std::vector<std::shared_ptr<Bot>>();
    bots.push_back(std::make_unique<Bot>(Bot(1, std::make_tuple(std::size_t(0),
                                                                std::size_t(0),
                                                                std::size_t(
                                                                    0)))));
    return bots;
}

void GameBisScene::loadPlayerAsset(const ACharacter::Color &color,
                                   const std::vector<std::string> &textures)
{
    auto mesh = _manager->addAnimatedMeshSceneNode(
        _manager->getMesh("../resources/models/Character/Bomberman.MD3"),
        _master.get());
    mesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    mesh->setMaterialTexture(0, _device->getVideoDriver()->getTexture(
        textures[static_cast<unsigned long>(color)].c_str()));
    mesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    mesh->setMD2Animation(irr::scene::EMAT_STAND);
    mesh->setScale(irr::core::vector3df(6, 6, 6));
    mesh->setRotation(irr::core::vector3df(0, 0, 0));
    mesh->setPosition(irr::core::vector3df(0, posY, 0));
    mesh->setAnimationSpeed(30);
    mesh->setLoopMode(true);
    mesh->setFrameLoop(0, 27);
    _meshs.emplace_back(mesh);
}

void GameBisScene::loadGameAsset()
{
    for (auto &bot : _bots)
        loadPlayerAsset(bot->_color, bot->_textures);
    for (auto &player : _players) {
        loadPlayerAsset(player->_color, player->_textures);
        auto bombs{player->getBombs()};
        /* for (auto &b : bombs)
             loadBomb(b, _d->getBombsMap());*/
    }
    _players[0]->setPosZ(
        std::get<2>(_players[0]->getMapPos()) + 30);
    changeModelPos(_players[0]->getEntityNb(),
                   std::make_tuple(
                       std::get<0>(
                           _players[0]->getMapPos()),
                       std::get<1>(
                           _players[0]->getMapPos()) + 5,
                       std::get<2>(
                           _players[0]->getMapPos())));

    // TEMPO - REPLACE IT BY GENERIC METHOD
    _bots[0]->setPosZ(
        std::get<2>( _players[0]->getMapPos()) - 100);
    changeModelPos(_bots[0]->getEntityNb(),
                   std::make_tuple(
                       std::get<0>(_bots[0]->getMapPos()),
                       std::get<1>(_bots[0]->getMapPos()) + 5,
                       std::get<2>(
                           _bots[0]->getMapPos())));
    _map->getMapData()._mapWall[10][0] = '0';
}

void
GameBisScene::loadGame(const std::string &mapPath)
{
    _map = std::shared_ptr<IMap>(new Map);
    _map->load(mapPath);
    loadGameAsset();
    loadMapAsset(_map->getMapData());
    irr::SKeyMap keyMap[5];                             // re-assigne les commandes
    keyMap[0].Action = irr::EKA_MOVE_FORWARD;           // avancer
    keyMap[0].KeyCode = irr::KEY_KEY_W;                 // w
    keyMap[1].Action = irr::EKA_MOVE_BACKWARD;          // reculer
    keyMap[1].KeyCode = irr::KEY_KEY_S;                 // s
    keyMap[2].Action = irr::EKA_STRAFE_LEFT;            // a gauche
    keyMap[2].KeyCode = irr::KEY_KEY_A;                 // a
    keyMap[3].Action = irr::EKA_STRAFE_RIGHT;           // a droite
    keyMap[3].KeyCode = irr::KEY_KEY_D;                 // d
    keyMap[4].Action = irr::EKA_JUMP_UP;                // saut
    keyMap[4].KeyCode = irr::KEY_SPACE;                 // barre espace

   /* _manager->addCameraSceneNodeFPS(                // ajout de la camera FPS
        0, 100.0f, 0.1f, -1, keyMap, 5);*/
}

void GameBisScene::loadScene()
{
    std::cout << "load Game" << std::endl;
    _is_load = true;
    _players = loadPlayer();
    _bots = loadBot();
   // auto game = std::unique_ptr<AGame>(new BombermanGame(_players, _bots));
    auto toto = _manager->addCameraSceneNode(_master.get());
    _master->setVisible(true);
    loadGame("./../resources/maps/3");
}

std::string GameBisScene::getName()
{
    return _name;
}

void GameBisScene::deLoad()
{
    std::cout << "DeloadGame" << std::endl;
    _master->setVisible(false);
}


// LOGIC

irr::core::vector3df GameBisScene::pos3dToVector(const IDisplay::pos3d &pos)
{
    return irr::core::vector3df(std::get<0>(pos), std::get<1>(pos),
                                std::get<2>(pos));
}

void
GameBisScene::changeModelPos(const std::size_t &i, const IDisplay::pos3d &vec)
{
    auto newVec = pos3dToVector(vec);

    newVec.X += posX;
    newVec.Y += posY;
    newVec.Z += posZ;
    _meshs[i]->setPosition(newVec);
}

ACharacter::Action  GameBisScene::pressKeyAction(const AGame::Event &events, const std::size_t &i)
{
    ACharacter::Action  action = ACharacter::Action::WAIT;

    if (events->IsKeyDown(_players[i]->getKeyMap()["UP"]))
        action = ACharacter::Action::UP;
    else if (events->IsKeyDown(_players[i]->getKeyMap()["DOWN"]))
        action = ACharacter::Action::DOWN;
    else if (events->IsKeyDown(_players[i]->getKeyMap()["LEFT"]))
        action = ACharacter::Action::LEFT;
    else if (events->IsKeyDown(_players[i]->getKeyMap()["RIGHT"]))
        action = ACharacter::Action::RIGHT;
    else if (events->IsKeyDown(_players[i]->getKeyMap()["BOMB"]))
        action = ACharacter::Action::BOMB;
    return action;
}

void GameBisScene::changeFrameAndPos(const ACharacter *cha,
                                        const ACharacter::Action &curr,
                                        const ACharacter::Action &last)
{
    if (curr != ACharacter::Action::WAIT) {
        if (last == ACharacter::Action::WAIT)
            _display->changeModelFrame(cha->getEntityNb(), 0, 27);
        _display->changeModelPos(cha->getEntityNb(),
                                 std::make_tuple(std::get<0>(cha->getMapPos()),
                                                 0, std::get<2>(
                                         cha->getMapPos())));
    }
}

void GameBisScene::changeAnimation(const std::size_t &i,
                                      const ACharacter::Action &curr,
                                      const ACharacter::Action &last)
{
    switch (curr) {
        case ACharacter::Action::LEFT:
            _display->changeModelRot(i, std::make_tuple(0, 90, 0));
            break;
        case ACharacter::Action::RIGHT:
            _display->changeModelRot(i, std::make_tuple(0, 270, 0));
            break;
        case ACharacter::Action::UP:
            _display->changeModelRot(i, std::make_tuple(0, 180, 0));
            break;
        case ACharacter::Action::DOWN:
            _display->changeModelRot(i, std::make_tuple(0, 0, 0));
            break;
        case ACharacter::Action::WAIT:
            if (last != ACharacter::Action::WAIT)
                _display->changeModelFrame(i, 27, 76);
            break;
        default:
            break;
    }
}

std::vector<ACharacter::Action> GameBisScene::movePlayers(const std::shared_ptr<Events> &events, std::vector<std::string> &map, IDisplay *d)
{
    std::vector<ACharacter::Action> actionVector;

    std::cout << _players.size() << std::endl;
    for (std::size_t i {0}; i < _players.size(); ++i) {
        std::cout << i << std::endl;
        auto action = pressKeyAction(events, i);
        _players[i]->setAction(action);
        _players[i]->move(map, d);
        _players[i]->setAction(ACharacter::Action::WAIT);
        actionVector.push_back(action);
    }
    return actionVector;
}

void GameBisScene::playersAction()
{
    auto playersMove = movePlayers(_event, _map->getMapData()._mapWall,
                                         _display.get());
    for (std::size_t i{0}; i < _players.size(); ++i) {
        changeFrameAndPos(_players[i].get(), playersMove[i],
                          _lastActions[_players[i]->getEntityNb()]);
        changeAnimation(_players[i]->getEntityNb(), playersMove[i],
                        _lastActions[_players[i]->getEntityNb()]);
        _lastActions[_players[i]->getEntityNb()] = playersMove[i];
    }
}

void GameBisScene::botsAction()
{
   /* auto botsMove = moveBots(_map->getMapData()._mapWall,
                                    _display.get());
    for (std::size_t i{0}; i < _game->getBots().size(); ++i) {
        changeFrameAndPos(_game->getBots()[i].get(), botsMove[i],
                          _lastActions[_game->getBots()[i]->getEntityNb()]);
        changeAnimation(_game->getBots()[i]->getEntityNb(), botsMove[i],
                        _lastActions[_game->getBots()[i]->getEntityNb()]);
        _lastActions[_game->getBots()[i]->getEntityNb()] = botsMove[i];
    }*/
}

void GameBisScene::action()
{
    playersAction();
    botsAction();
}
