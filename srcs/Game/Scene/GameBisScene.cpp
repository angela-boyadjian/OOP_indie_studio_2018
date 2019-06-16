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
#include "SaveManager.hpp"
#include "LoadManager.hpp"

GameBisScene::GameBisScene(std::shared_ptr<irr::IrrlichtDevice> device,
                           irr::scene::ISceneNode *father,
                           const std::string &name,
                           std::shared_ptr<Events> event,  std::shared_ptr<IDisplay> display) :
    _isPlaying(false),
    _master(device->getSceneManager()->addEmptySceneNode(father)),
    _manager(device->getSceneManager()),
    _name(name),
    _is_load(false),
    _device(device),
    _event(event),
    _display(display),
    _powerUpPath({"../resources/textures/powerup/powerup.png", "../resources/textures/powerup/speedMore.png", "../resources/textures/powerup/morebomb.png"})
{
    addSfEffect("PUT_BOMB", "./../resources/sounds/Bomb/BombClock.wav");
    addSfEffect("BOMB_EXP", "./../resources/sounds/Bomb/BombExplode.wav");
    addSfEffect("DEATH", "./../resources/sounds/Character/CharacterDeath.wav");
    addSfEffect("MUSIC", "./../resources/sounds/rasputin.wav");
    _sfEffects["MUSIC"]->setVolume(50);
    _master->setVisible(false);
}

GameBisScene::~GameBisScene()
{
    _sfEffects["BOMB_EXP"]->stop();
    _sfEffects["PUT_BOMB"]->stop();
    _sfEffects["DEATH"]->stop();
    _sfEffects["MUSIC"]->stop();
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
    return count;
}

void    GameBisScene::checkPowerUp()
{
    for (std::size_t i {0}; i < _powerUpPos.size(); ++i) {
        if (_map->getMapData()._mapWall[std::get<1>(_powerUpPos[i])][std::get<0>(_powerUpPos[i])] < '7')
            _powerUp[i]->setVisible(false);
    }
}

void GameBisScene::removeBlock(const int &x, const int &y, bool neg)
{
    auto index = getColiIndex(x, y) - neg;
    auto vec = _display->getColiMap().at(index)->getPosition();
    _display->getColiMap().at(index)->setVisible(false);
    _display->getColiMap().at(index).release(); // MODIF DE SES MORT
    _display->getColiMap().erase(_display->getColiMap().begin() + index);
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
    if (x + 1 < static_cast<int>(_map->getMapData()._mapWall[y].size()) and _map->getMapData()._mapWall[y][x + 1] == '2')
        removeBlock(x + 1, y, true);
    if (y > 0 and _map->getMapData()._mapWall[y - 1][x] == '2')
        removeBlock(x, y - 1, true);
    if (y + 1 < static_cast<int>(_map->getMapData()._mapWall.size()) and _map->getMapData()._mapWall[y + 1][x] == '2')
        removeBlock(x, y + 1, true);
    setExplosion(x, y);
    exploseEmpty(x, y);
}

void GameBisScene::killPlayers(const int &x, const int &y)
{
    for (std::size_t i {0}; i < _game->getPlayers().size(); ++i) {
        auto p = _game->getPlayers()[i]->get2dPos();
        if (std::get<0>(p) == x and std::get<1>(p) == y) {
            _game->getPlayers()[i]->setPosZ(1000);
            changeModelPos(_game->getPlayers()[i]->getEntityNb(), _game->getPlayers()[i]->getMapPos());
            _game->getPlayers().erase(_game->getPlayers().begin() + i);
            _sfEffects["DEATH"]->play();
            return killPlayers(x, y);
        }
    }
    for (std::size_t i {0}; i < _game->getBots().size(); ++i) {
        auto p = _game->getBots()[i]->get2dPos();
        if (std::get<0>(p) == x and std::get<1>(p) == y) {
            _game->getBots()[i]->setPosZ(1000);
            changeModelPos(_game->getBots()[i]->getEntityNb(), _game->getBots()[i]->getMapPos());
            _game->getBots().erase(_game->getBots().begin() + i);
            _sfEffects["DEATH"]->play();
            return killPlayers(x, y);
        }
    }
}

void GameBisScene::exploseEmpty(const int &x, const int &y)
{
    auto tmp_x = x;
    auto tmp_y = y;

    while (--tmp_x >= 0 and _map->getMapData()._mapWall[y][tmp_x] == '3') {
        _map->getMapData()._mapWall[y][tmp_x] = '0';
        killPlayers(tmp_x, y);
        setExplosion(tmp_x, y);
    }
    tmp_x = x;
    while (++tmp_x < static_cast<int>(_map->getMapData()._mapWall[y].size()) and _map->getMapData()._mapWall[y][tmp_x] == '3') {
        _map->getMapData()._mapWall[y][tmp_x] = '0';
        killPlayers(tmp_x, y);
        setExplosion(tmp_x, y);
    }
    while (--tmp_y >= 0 and _map->getMapData()._mapWall[tmp_y][x] == '3') {
        _map->getMapData()._mapWall[tmp_y][x] = '0';
        killPlayers(x, tmp_y);
        setExplosion(x, tmp_y);
    }
    tmp_y = y;
    while (++tmp_y < static_cast<int>(_map->getMapData()._mapWall.size()) and _map->getMapData()._mapWall[tmp_y][x] == '3') {
        _map->getMapData()._mapWall[tmp_y][x] = '0';
        killPlayers(x, tmp_y);
        setExplosion(x, tmp_y);
    }
    _map->getMapData()._mapWall[y][x] = '0';
    killPlayers(x, y);
}

void GameBisScene::explosion(const int &x, const int &y, const bool &b)
{
    if (b)
        _sfEffects["PUT_BOMB"]->stop();
    _sfEffects["BOMB_EXP"]->play();
    exploseBlock(x, y);
    exploseEmpty(x, y);
}

void GameBisScene::exploseBomb()
{
    for (std::size_t i {0}; i < bombs_pos.size(); ++i) {
        std::chrono::duration<double>   elapsedTime = std::chrono::system_clock::now() - bombs_time[i];
        if (elapsedTime.count() >= 2) {
            bombs_pos.size() > 1 ? explosion(bombs_pos[i].x, bombs_pos[i].y, false)
                : explosion(bombs_pos[i].x, bombs_pos[i].y, true);
            _display->visiBomb(bombs_pos[i].x, bombs_pos[i].y, false);
            bombs_player[i]->increaseBombNumber();
            bombs_player.erase(bombs_player.begin() + i);
            bombs_time.erase(bombs_time.begin() + i);
            bombs_pos.erase(bombs_pos.begin() + i);
            return exploseBomb();
        }
    }
}

// FIXME Save
void GameBisScene::putBomb(const std::vector<ACharacter::move_t> &actions)
{
    static bool isRunning = false;

    for (auto a : actions) {
        if (a.action == ACharacter::Action::BOMB and _map->getMapData()._mapWall[a.y][a.x] != '1'
                                                     and _map->getMapData()._mapWall[a.y][a.x] != '2') {
            if (!isRunning)
                _sfEffects["PUT_BOMB"]->play();
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
        std::chrono::duration<double> elapsedTime = std::chrono::system_clock::now() - _explosionTime[i];
        if (elapsedTime.count() >= 1) {
            _display->getExplosionMap()[std::get<1>(_explosionPos[i])][std::get<0>(_explosionPos[i])]->setVisible(false);
            _explosionTime.erase(_explosionTime.begin() + i);
            _explosionPos.erase(_explosionPos.begin() + i);
            return stopExplosion();
        }
    }
}

bool GameBisScene::pauseEvent()
{
    if (_event->IsKeyDown(irr::KEY_ESCAPE))
        _pause->switchStatus();
    if (_pause->getStatus()) {
        _name = _pause->runPause(_name);
        return true;
    }
    return false;
}


// NOTE Run scene
SceneInfo GameBisScene::runScene()
{
    // TEMPO - REPLACE IT BY GENERIC METHOD
    if (pauseEvent())
        return SceneInfo(_name);
    if (!_isPlaying) {
        _isPlaying = true;
        _sfEffects["MUSIC"]->play();
    }
    if (_game->getBots().empty() and _game->getPlayers().size() == 1)
        return SceneInfo("win");
    else if (_game->getPlayers().empty())
        return SceneInfo("lose");
    if (!_is_load)
        throw SceneException("Scene is not load", _name.c_str());
    exploseBomb();
    auto actions = action();
    putBomb(actions);
    stopExplosion();
    checkPowerUp();
    return SceneInfo(_name);
}

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
    bots.push_back(std::make_unique<Bot>(Bot(1, ACharacter::Color::RED, std::make_tuple(std::size_t(0),
                                                                std::size_t(0),
                                                                std::size_t(
                                                                    0)))));
    return bots;
}

void GameBisScene::placeCharacter(std::shared_ptr<ACharacter> character)
{
    switch (character->getEntityNb()) {
    case 0:
        character->setPos2d(std::make_tuple(0, 0));
        character->setPosZ(std::get<2>(character->getMapPos()) + 30);
        changeModelPos(character->getEntityNb(), std::make_tuple(
            std::get<0>(character->getMapPos()),
            std::get<1>(character->getMapPos()),
            std::get<2>(character->getMapPos())));
        character->setPos3d(std::make_tuple(5, 5));
        break;
    case 1:
        character->setPos2d(std::make_tuple(0, 10));
        character->setPosZ(std::get<2>(character->getMapPos()) - 70);
        changeModelPos(character->getEntityNb(),std::make_tuple(
            std::get<0>(character->getMapPos()),
            std::get<1>(character->getMapPos()),
            std::get<2>(character->getMapPos())));
        character->setPos3d(std::make_tuple(0, 105));
        break;
    case 2:
        character->setPos2d(std::make_tuple(12, 0));
        character->setPosZ(std::get<2>(character->getMapPos()) + 30);
        character->setPosX(std::get<2>(character->getMapPos()) + 90);
        changeModelPos(character->getEntityNb(), std::make_tuple(
            std::get<0>(character->getMapPos()),
            std::get<1>(character->getMapPos()),
            std::get<2>(character->getMapPos())));
        character->setPos3d(std::make_tuple(125, 5));
        break;
    case 3:
        character->setPos2d(std::make_tuple(12, 10));
        character->setPosZ(std::get<2>(character->getMapPos()) - 70);
        character->setPosX(std::get<2>(character->getMapPos()) + 190);
        changeModelPos(character->getEntityNb(), std::make_tuple(
            std::get<0>(character->getMapPos()),
            std::get<1>(character->getMapPos()),
            std::get<2>(character->getMapPos())));
        character->setPos3d(std::make_tuple(125, 105));
    default:
        break;
    }
}

void GameBisScene::placePlayer()
{
    auto player = _game->getPlayers();
    auto bot = _game->getBots();
    std::size_t idx = 0;

    while (idx != 4) {
        for (auto &play : player) {
            if (play->getEntityNb() == idx)
                placeCharacter(play);
        }
        for (auto &b : bot) {
            if (b->getEntityNb() == idx)
                placeCharacter(b);
        }
        idx++;
    }
}

void GameBisScene::loadGame(const std::string &mapPath, std::unique_ptr<AGame> &game, SceneInfo info)
{
    //_map = std::shared_ptr<IMap>(new Map);
    _map = info._map;
    //_map->load(mapPath);
    _game = std::move(game);
    _display->_driver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, false);
    _manager->addSkyDomeSceneNode
    (_display->_driver->getTexture("./../resources/textures/skyboxes/skybox1.jpg"),16,8,0.95f,2.0f);
    _display->_driver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, true);
    _dispLoader->loadGame(_game);
    _dispLoader->loadMap(_map->getMapData());
    _dispLoader->setExplosionPos();
    _dispLoader->setBombsPos();
    //    _dispLoader->loadMap(_map->getMapData());
    // NOTE TEMPO
    _event = std::make_unique<Events>(Events(_display->_device, _display));
    _display->_device->setEventReceiver(_event.get());

    _map->getMapData()._mapWall[0][0] = '0';
    _map->getMapData()._mapWall[10][0] = '0';
    _map->getMapData()._mapWall[0][12] = '0';
    _map->getMapData()._mapWall[10][12] = '0';
    placePlayer();
}

void GameBisScene::loadScene(SceneInfo &info)
{

/*    //La camera
    irr::SKeyMap keyMap[5];
    keyMap[0].Action = irr::EKA_MOVE_FORWARD;
    keyMap[0].KeyCode = irr::KEY_KEY_Z;
    keyMap[1].Action = irr::EKA_MOVE_BACKWARD;
    keyMap[1].KeyCode = irr::KEY_KEY_S;
    keyMap[2].Action = irr::EKA_STRAFE_LEFT;
    keyMap[2].KeyCode = irr::KEY_KEY_Q;
    keyMap[3].Action = irr::EKA_STRAFE_RIGHT;
    keyMap[3].KeyCode = irr::KEY_KEY_D;
    keyMap[4].Action = irr::EKA_JUMP_UP;
    keyMap[4].KeyCode = irr::KEY_SPACE;
    irr::scene::ICameraSceneNode *ccamera;
    ccamera = _manager->addCameraSceneNodeFPS (0,100.0f,0.02f, -1, keyMap, 15, false, 0.4);
    ccamera->setPosition(irr::core::vector3df(0.0f, 0.0f, 0.0f));*/


    auto camera = _manager->addCameraSceneNode(_master.get());
    camera->setPosition(irr::core::vector3df(192.264, 53.8758, 112.409));
    camera->setTarget(irr::core::vector3df(-3, -15, 15));

    _is_load = true;
    _dispLoader = std::make_unique<IrrlichtDisplayLoader>(_display, _master, _manager);
    _pause = std::make_unique<PauseMenu>(_master.get(), _manager, _device->getVideoDriver()->getScreenSize(), _event, _device);
    // auto l = LoadManager();
    // auto game = l.loadGame();
    // info._map = l.getMap();

    // for (auto &i : info._map->getMapData()._mapWall)
    //     std::cout << i << std::endl;
    auto game = std::unique_ptr<AGame>(new BombermanGame(info._players, info._bot));
    // std::cout << "Player pos IN SCENE\n";
    // for (auto &i : game->getPlayers()) {
    //     auto pos = i->getMapPos();
    //     std::cout << "Pos = " << std::get<0>(pos) << " "
    //     << std::get<1>(pos) << " " << std::get<2>(pos) << "\n";
    // }
    // std::cout << "BOT pos IN SCENE\n";
    // for (auto &i : game->getBots()) {
    //     auto pos = i->getMapPos();
    //     std::cout << "Pos = " << std::get<0>(pos) << " "
    //     << std::get<1>(pos) << " " << std::get<2>(pos) << "\n";
    // }
    _master->setVisible(true);
    loadGame("./../resources/maps/3", game, info);
    camera->addAnimator(_manager->createFlyStraightAnimator(
            camera->getPosition(), irr::core::vector3df(-3.18643, 10.1158, 4.47983),
            1000, false, false));
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

void GameBisScene::addSfEffect(const std::string &key, const std::string &path)
{
    _sfBuf.emplace_back(std::make_unique<sf::SoundBuffer>(sf::SoundBuffer()));
    _sfBuf.back()->loadFromFile(path);
    _sfEffects[key] = std::make_unique<sf::Sound>(sf::Sound());
    _sfEffects[key]->setBuffer(*_sfBuf.back().get());
}
