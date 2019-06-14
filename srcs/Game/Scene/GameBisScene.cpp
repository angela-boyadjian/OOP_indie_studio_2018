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
    _display(display)
{
    _master->setVisible(false);
}

std::string GameBisScene::runScene()
{
    // TEMPO - REPLACE IT BY GENERIC METHOD
    if (!_is_load)
        throw SceneException("Scene is not load", _name.c_str());
    action();
    _master->setVisible(true);
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
    _map->load(mapPath);
    _game = std::move(game);
    _dispLoader->loadGame(_game);
    _dispLoader->loadMap(_map->getMapData());

    // NOTE TEMPO
    _event = std::make_unique<Events>(Events(_display->_device, _display));
    _display->_device->setEventReceiver(_event.get());

    // TEMPO - REPLACE IT BY GENERIC METHOD
    _game->getPlayers()[0]->setPosZ(
        std::get<2>(_game->getPlayers()[0]->getMapPos()) + 30);
    /*_game->getPlayers()[0]->setPosY(
        std::get<1>(_game->getPlayers()[0]->getMapPos()) + 3000000000000000);*/
    /*_game->getPlayers()[0]->setPosY(
        std::get<1>(_game->getPlayers()[0]->getMapPos()) + 30);*/
    changeModelPos(_game->getPlayers()[0]->getEntityNb(),
        std::make_tuple(
            std::get<0>(
                _game->getPlayers()[0]->getMapPos()),
                std::get<1>(
                    _game->getPlayers()[0]->getMapPos()),
                    std::get<2>(
                        _game->getPlayers()[0]->getMapPos())));
    // TEMPO - REPLACE IT BY GENERIC METHOD
    /*_game->getBots()[0]->setPosZ(
        std::get<2>(_game->getPlayers()[0]->getMapPos()) - 100);
        changeModelPos(_game->getBots()[0]->getEntityNb(),
                             std::make_tuple(
                                 std::get<0>(_game->getBots()[0]->getMapPos()),
                                 std::get<1>(_game->getBots()[0]->getMapPos()),
                                 std::get<2>(
                                     _game->getBots()[0]->getMapPos())));*/
    _map->getMapData()._mapWall[10][0] = '0';
}

void GameBisScene::loadScene()
{
    std::cout << "load Game" << std::endl;
    auto camera = _manager->addCameraSceneNode(_master.get());
    camera->setTarget(irr::core::vector3df(0, -15, 10));
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
    std::cout << "NEW vector :" <<  newVec.X << std::endl;
    std::cout << "NEW vector :" <<  newVec.Y << std::endl;
    std::cout << "NEW vector :" <<  newVec.Z << std::endl;
    /*newVec.X += posX;
    newVec.Y += posY;
    newVec.Z += posZ;*/
    std::cout << "NEW vector :" <<  newVec.X << std::endl;
    std::cout << "NEW vector :" <<  newVec.Y << std::endl;
    std::cout << "NEW vector :" <<  newVec.Z << std::endl;
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

void GameBisScene::playersAction()
{
    auto playersMove = _game->movePlayers(_event, _map->getMapData()._mapWall,
                                         _display.get());
    auto toto = _game->getPlayers()[0]->getMapPos();
    std::cout << "pos :" <<  std::get<0>(toto) << std::endl;
    std::cout << "pos :" <<   std::get<1>(toto) << std::endl;
    std::cout << "pos :" <<   std::get<2>(toto) << std::endl;
    //exit(0);
    for (std::size_t i{0}; i < _game->getPlayers().size(); ++i) {
        changeFrameAndPos(_game->getPlayers()[i].get(), playersMove[i],
                          _lastActions[_game->getPlayers()[i]->getEntityNb()]);
        changeAnimation(_game->getPlayers()[i]->getEntityNb(), playersMove[i],
                        _lastActions[_game->getPlayers()[i]->getEntityNb()]);
        _lastActions[_game->getPlayers()[i]->getEntityNb()] = playersMove[i];
    }
}

void GameBisScene::botsAction()
{
   auto botsMove = _game->moveBots(_map->getMapData()._mapWall,
                                    _display.get());
    for (std::size_t i{0}; i < _game->getBots().size(); ++i) {
        changeFrameAndPos(_game->getBots()[i].get(), botsMove[i],
                          _lastActions[_game->getBots()[i]->getEntityNb()]);
        changeAnimation(_game->getBots()[i]->getEntityNb(), botsMove[i],
                        _lastActions[_game->getBots()[i]->getEntityNb()]);
        _lastActions[_game->getBots()[i]->getEntityNb()] = botsMove[i];
    }
}

void GameBisScene::action()
{
    playersAction();
    botsAction();
}
