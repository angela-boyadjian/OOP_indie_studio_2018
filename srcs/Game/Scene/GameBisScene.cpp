/*
** EPITECH PROJECT, 2019
** GameScene.cpp 
** File description:
** basile.lamarque@epitech.eu
*/

#include <AGame.hpp>
#include <Bomberman/BombermanGame.hpp>
#include <IrrlichtDisplay/IrrlichtDisplayLoader.hpp>
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
    _display(display),
    _powerUpPath({"../resources/textures/powerup/powerup.png", "../resources/textures/powerup/speedMore.png", "../resources/textures/powerup/morebomb.png"})
{
    _master->setVisible(false);
}

std::size_t GameBisScene::getColiIndex(const int &x, const int &y)
{
    auto count {0};

    for (auto j {0}; j < y; ++j)
        for (std::size_t i {0}; i < _map->getMapData()._mapWall[j].size(); ++i)
            if (_map->getMapData()._mapWall[j][i] == '2')
                ++count;
    for (auto i {0}; i <= x; ++i)
        if (_map->getMapData()._mapWall[y][i] == '2')
            ++count;
    for (auto &r : _rm)
        if (count > r)
            ++count;
    return count;
}

void    GameBisScene::checkPowerUp()
{
    for (std::size_t i {0}; i < _powerUp.size(); ++i) {
        if (_map->getMapData()._mapWall[std::get<1>(_powerUpPos[i])][std::get<0>(_powerUpPos[i])] < '7')
            _powerUp[i]->setVisible(false);
    }
}
void GameBisScene::removeBlock(const int &x, const int &y, bool neg)
{
    auto index = getColiIndex(x, y) - neg;
    auto vec = _display->getColiMap().at(index)->getPosition();
    _display->getColiMap().at(index)->setVisible(false);
    _rm.emplace_back(index);
    _map->getMapData()._mapWall[y][x] = '7';
    setExplosion(x, y);
    auto r = std::rand() % 4;
    if (r == 0)
        _map->getMapData()._mapWall[y][x] = '0';
    else {
        _map->getMapData()._mapWall[y][x] = r + 6 + 48;
        _powerUp.emplace_back(std::unique_ptr<IDisplay::Object >(_dispLoader->createBonus(_powerUpPath[r - 1])));
        _powerUpPos.emplace_back(std::make_tuple(x, y));
        vec.Y -= 5;
        _powerUp.back()->setPosition(vec);
    }
}

void    GameBisScene::setExplosion(const int &x, const int &y)
{
    _display->getExplosionMap()[y][x]->setVisible(true);
    _explosionTime.emplace_back(std::chrono::system_clock::now());
    _explosionPos.emplace_back(std::make_tuple(x, y));
}

void    GameBisScene::exploseBlock(const int &x, const int &y)
{
    if (x > 0 and _map->getMapData()._mapWall[y][x - 1] == '2')
        removeBlock(x - 1, y, true);
    if (x + 1 < _map->getMapData()._mapWall[y].size() and _map->getMapData()._mapWall[y][x + 1] == '2')
        removeBlock(x + 1, y, true);
    if (y > 0 and _map->getMapData()._mapWall[y - 1][x] == '2')
        removeBlock(x, y - 1, true);
    if (y + 1 < _map->getMapData()._mapWall.size() and _map->getMapData()._mapWall[y + 1][x] == '2')
        removeBlock(x, y + 1, true);
    setExplosion(x, y);
    exploseEmpty(x, y);
}

void GameBisScene::exploseEmpty(const int &x, const int &y)
{
    auto tmp_x = x;
    auto tmp_y = y;

    while (--tmp_x >= 0 and _map->getMapData()._mapWall[y][tmp_x] == '3') {
        _map->getMapData()._mapWall[y][tmp_x] = '0';
        setExplosion(tmp_x, y);
    }
    tmp_x = x;
    while (++tmp_x < _map->getMapData()._mapWall[y].size() and _map->getMapData()._mapWall[y][tmp_x] == '3') {
        _map->getMapData()._mapWall[y][tmp_x] = '0';
        setExplosion(tmp_x, y);
    }
    while (--tmp_y >= 0 and _map->getMapData()._mapWall[tmp_y][x] == '3') {
        _map->getMapData()._mapWall[tmp_y][x] = '0';
        setExplosion(x, tmp_y);
    }
    tmp_y = y;
    while (++tmp_y < _map->getMapData()._mapWall.size() and _map->getMapData()._mapWall[tmp_y][x] == '3') {
        _map->getMapData()._mapWall[tmp_y][x] = '0';
        setExplosion(x, tmp_y);
    }
}

void GameBisScene::explosion(const int &x, const int &y)
{
    exploseBlock(x, y);
    exploseEmpty(x, y);
}

void GameBisScene::exploseBomb()
{
    for (std::size_t i {0}; i < bombs_pos.size(); ++i) {
        std::chrono::duration<double>   elapsedTime = std::chrono::system_clock::now() - bombs_time[i];
        if (elapsedTime.count() >= 1) {
            explosion(bombs_pos[i].x, bombs_pos[i].y);
            _display->visiBomb(bombs_pos[i].x, bombs_pos[i].y, false);
            bombs_player[i]->increaseBombNumber();
            bombs_player.erase(bombs_player.begin() + i);
            bombs_time.erase(bombs_time.begin() + i);
            bombs_pos.erase(bombs_pos.begin() + i);
            return exploseBomb();
        }
    }
}

void GameBisScene::putBomb(const std::vector<ACharacter::move_t> &actions)
{
    for (auto a : actions) {
        if (a.action == ACharacter::Action::BOMB) {
            std::cout << "COUCOU " << a.x << " " << a.y << std::endl;
            _display->visiBomb(a.x, a.y, true);
            bombs_pos.emplace_back(a);
            bombs_time.emplace_back(std::chrono::system_clock::now());
            bombs_player.emplace_back(reinterpret_cast<ABombermanPlayer *>(a.itself));
        }
    }
}

void GameBisScene::stopExplosion()
{
    for (std::size_t i {0}; i < _explosionPos.size(); ++i) {
        std::chrono::duration<double>   elapsedTime = std::chrono::system_clock::now() - _explosionTime[i];
        if (elapsedTime.count() >= 1) {
            _display->getExplosionMap()[std::get<1>(_explosionPos[i])][std::get<0>(_explosionPos[i])]->setVisible(false);
            _explosionTime.erase(_explosionTime.begin() + i);
            _explosionPos.erase(_explosionPos.begin() + i);
            return stopExplosion();
        }
    }
}

std::string GameBisScene::runScene()
{
    // TEMPO - REPLACE IT BY GENERIC METHOD
    if (!_is_load)
        throw SceneException("Scene is not load", _name.c_str());
    exploseBomb();
    auto actions = action();
    putBomb(actions);
    stopExplosion();
    checkPowerUp();
  //  _display->draw();
    return _name;
}

// NOTE LOAD

// NOTE LOAD MAP

std::vector<std::unique_ptr<Player>> GameBisScene::loadPlayer()
{
    auto players = std::vector<std::unique_ptr<Player>>();

    players.push_back(
        std::make_unique<Player>(Player(0, ACharacter::Color::BLACK,
                                        std::make_tuple(std::size_t(0),
                                                        std::size_t(50000),
                                                        std::size_t(0)))));

    return players;
}

std::vector<std::unique_ptr<Bot>> GameBisScene::loadBot()
{
    auto bots = std::vector<std::unique_ptr<Bot>>();
    bots.push_back(std::make_unique<Bot>(Bot(1, std::make_tuple(std::size_t(0),
                                                                std::size_t(0),
                                                                std::size_t(
                                                                    0)))));
    return bots;
}

void
GameBisScene::loadGame(const std::string &mapPath, std::unique_ptr<AGame> &game)
{
    _map = std::shared_ptr<IMap>(new Map);
    std::cout << "rien" << std::endl;
    _map->load(mapPath);
    std::cout << "map" << std::endl;
    _game = std::move(game);
    _dispLoader->loadGame(_game);
    std::cout << "game" << std::endl;
    _dispLoader->loadMap(_map->getMapData());

    // NOTE TEMPO
    _event = std::make_unique<Events>(Events(_display->_device, _display));
    _display->_device->setEventReceiver(_event.get());

    // TEMPO - REPLACE IT BY GENERIC METHOD
    _game->getPlayers()[0]->setPosZ(
        std::get<2>(_game->getPlayers()[0]->getMapPos()) + 30);
    changeModelPos(_game->getPlayers()[0]->getEntityNb(),
        std::make_tuple(
            std::get<0>(
                _game->getPlayers()[0]->getMapPos()),
                std::get<1>(
                    _game->getPlayers()[0]->getMapPos()),
                    std::get<2>(
                        _game->getPlayers()[0]->getMapPos())));
    // TEMPO - REPLACE IT BY GENERIC METHOD
    _game->getBots()[0]->setPosZ(
        std::get<2>(_game->getPlayers()[0]->getMapPos()) - 100);
        changeModelPos(_game->getBots()[0]->getEntityNb(),
                             std::make_tuple(
                                 std::get<0>(_game->getBots()[0]->getMapPos()),
                                 std::get<1>(_game->getBots()[0]->getMapPos()),
                                 std::get<2>(
                                     _game->getBots()[0]->getMapPos())));
    _map->getMapData()._mapWall[10][0] = '0';
}

void GameBisScene::loadScene()
{
    /*std::cout << "load Game" << std::endl;
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

    _manager->addCameraSceneNodeFPS(                // ajout de la camera FPS
        0, 100.0f, 0.1f, -1, keyMap, 5);*/


    auto camera = _manager->addCameraSceneNode(_master.get());
    camera->setTarget(irr::core::vector3df(0, -15, 25));
    camera->setPosition(irr::core::vector3df(0, 0, 20));
    _is_load = true;
    _dispLoader = std::make_unique<IrrlichtDisplayLoader>(_display, _master, _manager);
    auto players = loadPlayer();
    auto bots = loadBot();
    auto game = std::unique_ptr<AGame>(new BombermanGame(players, bots));
    _master->setVisible(true);
    loadGame("./../resources/maps/3", game);
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
    _display->_meshsScene[i]->setPosition(newVec);
}

ACharacter::Action  GameBisScene::pressKeyAction(const AGame::Event &events, const std::size_t &i)
{
    ACharacter::Action  action = ACharacter::Action::WAIT;

    if (events->IsKeyDown(_game->getPlayers()[i]->getKeyMap()["UP"]))
        action = ACharacter::Action::UP;
    else if (events->IsKeyDown(_game->getPlayers()[i]->getKeyMap()["DOWN"]))
        action = ACharacter::Action::DOWN;
    else if (events->IsKeyDown(_game->getPlayers()[i]->getKeyMap()["LEFT"]))
        action = ACharacter::Action::LEFT;
    else if (events->IsKeyDown(_game->getPlayers()[i]->getKeyMap()["RIGHT"]))
        action = ACharacter::Action::RIGHT;
    else if (events->IsKeyDown(_game->getPlayers()[i]->getKeyMap()["BOMB"]))
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

std::vector<ACharacter::move_t> GameBisScene::playersAction()
{
    auto playersMove = _game->movePlayers(_event, _map->getMapData()._mapWall, _display.get());
    for (std::size_t i {0}; i < _game->getPlayers().size(); ++i) {
        changeFrameAndPos(_game->getPlayers()[i].get(), playersMove[i].action, _lastActions[_game->getPlayers()[i]->getEntityNb()]);
        changeAnimation(_game->getPlayers()[i]->getEntityNb(), playersMove[i].action, _lastActions[_game->getPlayers()[i]->getEntityNb()]);
        _lastActions[_game->getPlayers()[i]->getEntityNb()] = playersMove[i].action;
    }
    return playersMove;
}

std::vector<ACharacter::move_t> GameBisScene::botsAction()
{
    auto botsMove = _game->moveBots(_map->getMapData()._mapWall, _display.get());
    for (std::size_t i {0}; i < _game->getBots().size(); ++i) {
        changeFrameAndPos(_game->getBots()[i].get(), botsMove[i].action, _lastActions[_game->getBots()[i]->getEntityNb()]);
        changeAnimation(_game->getBots()[i]->getEntityNb(), botsMove[i].action, _lastActions[_game->getBots()[i]->getEntityNb()]);
        _lastActions[_game->getBots()[i]->getEntityNb()] = botsMove[i].action;
    }
    return botsMove;
}

std::vector<ACharacter::move_t> GameBisScene::action()
{
    auto p = playersAction();
    auto b = botsAction();
    p.insert(p.end(), b.begin(), b.end());
    return p;
}
