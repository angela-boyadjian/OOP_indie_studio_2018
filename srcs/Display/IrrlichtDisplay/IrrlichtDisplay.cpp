#include <iostream>

#include "DisplayExceptions.hpp"
#include "IrrlichtDisplay.hpp"

IrrlichtDisplay::IrrlichtDisplay()
{
}

void    IrrlichtDisplay::setDisplay(Events *events)
{
    _device = std::unique_ptr<irr::IrrlichtDevice>(irr::createDevice(irr::video::EDT_OPENGL,
                                         irr::core::dimension2d<irr::u32>(1200, 800), 16, false, false, false, events));
    if (!_device)
        throw DeviceCreationError();
    _device->setWindowCaption(L"Bomberman");
    _gui = std::unique_ptr<irr::gui::IGUIEnvironment>(_device->getGUIEnvironment());
    _driver = _device->getVideoDriver();

    _sceneManagers.insert(std::pair<std::string, Scenes>("menu", std::shared_ptr<ISceneManager>(new MenuScene(_device, _driver))));
    _sceneManagers.insert(std::pair<std::string, Scenes>("game", std::shared_ptr<ISceneManager>(new GameScene(_device, _driver))));
    _currentScene = "menu";
//    _currentScene = "game";
}

void    IrrlichtDisplay::setExplosion(const std::size_t &i, const std::size_t &j, const irr::core::vector3df &v)
{
    _explosions.at(j).at(i)->setPosition(v);
    _explosions.at(j).at(i)->setVisible(false);
}

void    IrrlichtDisplay::setBombs(const std::size_t &i, const std::size_t &j, const irr::core::vector3df &v)
{
    _bombs.at(j).at(i)->setPosition(v);
    _bombs.at(j).at(i)->setVisible(false);
}

irr::core::vector3df    IrrlichtDisplay::pos3dToVector(const IDisplay::pos3d &pos)
{
    return irr::core::vector3df(std::get<0>(pos), std::get<1>(pos), std::get<2>(pos));
}

void    IrrlichtDisplay::addNewAnimation(const char *meshPath, const char *scenePath,
    const pos3d &scale)
{
    _sceneManagers.at("game")->addNewMesh(meshPath);
    _sceneManagers.at("game")->addNewMeshScene(scenePath, pos3dToVector(scale));
}

bool    IrrlichtDisplay::isRunning() const
{
    return _device->run();
}

void    IrrlichtDisplay::setGuiMessage(const wchar_t *message)
{
    _gui->addStaticText(message, irr::core::rect<irr::s32>(10, 10, 260, 22), true);
}

void    IrrlichtDisplay::draw()
{
    _driver->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));
    _sceneManagers.at(_currentScene)->getSceneManager()->drawAll();
    auto pos = _sceneManagers.at(_currentScene)->getSceneManager()->getActiveCamera()->getPosition();
    std::cout << pos.X << " " << pos.Y << "  " << pos.Z << std::endl;
//    std::cout << _currentScene << std::endl;
    _gui->drawAll();
    _driver->endScene();
}

IrrlichtDisplay::Gui const &IrrlichtDisplay::getGui()
{
    return _gui;
}

IrrlichtDisplay::Device const &IrrlichtDisplay::getDevice()
{
    return _device;
}

irr::core::dimension2du const &IrrlichtDisplay::getScreenSize()
{
    return _driver->getScreenSize();
}
IDisplay::Map3D &IrrlichtDisplay::getMap()
{
    return _map3d;
}

IDisplay::Map3D &IrrlichtDisplay::getColiMap()
{
    return _coliMap;
}

std::vector<IDisplay::BombsVec> &IrrlichtDisplay::getBombsMap()
{
    return _bombs;
}

std::vector<IDisplay::BombsVec> &IrrlichtDisplay::getExplosionMap()
{
    return _explosions;
}

IDisplay::Map3D &IrrlichtDisplay::getNonColiMap()
{
    return _noncoliMap;
}

void    IrrlichtDisplay::changeModelPos(const std::size_t &i, const pos3d &vec)
{
    auto newVec = pos3dToVector(vec);
    auto meshsScene = _sceneManagers.at("game")->getMeshScenes();

    newVec.X += 5400;
    newVec.Y += 808;
    newVec.Z += 5200;
    meshsScene[i]->setPosition(newVec);
}

void    IrrlichtDisplay::changeModelRot(const std::size_t &i, const pos3d &vec)
{
    auto meshsScene = _sceneManagers.at("game")->getMeshScenes();
    meshsScene[i]->setRotation(pos3dToVector((vec)));
}

void    IrrlichtDisplay::changeModelFrame(const std::size_t &i, const std::size_t &a, const std::size_t &b)
{
    auto meshsScene = _sceneManagers.at("game")->getMeshScenes();
    meshsScene[i]->setFrameLoop(a, b);
}

bool    IrrlichtDisplay::isCollisionFromMap(irr::core::aabbox3d<irr::f32> &b) const
{
    for (std::size_t i {0}; i < _coliMap.size(); ++i) {
        auto b2 = _coliMap[i]->getBoundingBox();
        _coliMap[i]->getRelativeTransformation().transformBoxEx(b2);
        if (b.intersectsWithBox(b2) && _coliMap[i]->isVisible())
            return true;
    }
    return false;
}

bool    IrrlichtDisplay::isCollisionFromObstacles(irr::core::aabbox3d<irr::f32> &b) const
{
    for (std::size_t i {0}; i < _noncoliMap.size(); ++i) {
        auto b2 = _noncoliMap[i]->getBoundingBox();
        _noncoliMap[i]->getRelativeTransformation().transformBoxEx(b2);
        if (b.intersectsWithBox(b2) && _noncoliMap[i]->isVisible())
            return true;
    }
    return false;
}

bool    IrrlichtDisplay::isCollision(const std::size_t &target)
{
    auto meshsScene = _sceneManagers.at("game")->getMeshScenes();
    auto b = meshsScene[target]->getBoundingBox();
    meshsScene[target]->getRelativeTransformation().transformBoxEx(b);
    return isCollisionFromMap(b) || isCollisionFromObstacles(b);
}

void    IrrlichtDisplay::destroyCollision(std::shared_ptr<irr::scene::IAnimatedMeshSceneNode> scene)
{
    // auto meshsScene = _sceneManagers.at("game")->getMeshScenes();
    // auto b = meshsScene[target]->getBoundingBox();
    auto b = scene->getBoundingBox();
    scene->getRelativeTransformation().transformBoxEx(b);
    for (std::size_t i {0}; i < _coliMap.size(); ++i) {
        auto b2 = _coliMap[i]->getBoundingBox();
        _coliMap[i]->getRelativeTransformation().transformBoxEx(b2);
        if (b.intersectsWithBox(b2) && _coliMap[i]->isVisible())
            _coliMap[i]->setVisible(false);
    }
}

void    IrrlichtDisplay::setBombState(const std::size_t &target, bool isVisible)
{
    for (auto &b : _bombsMap)
        b.get()->setVisible(true);
}

void    IrrlichtDisplay::changeScene(std::string const &scene)
{
    static int i;

    if (_currentScene == "menu" && i == 0) {
        _currentScene = "game";
        _device->getCursorControl()->setVisible(false);
        _gui->getRootGUIElement()->setVisible(false);
        i = 1;
        auto camera = _sceneManagers.at(_currentScene)->getSceneManager()->getActiveCamera();
        camera->addAnimator(_sceneManagers.at(_currentScene)->getSceneManager()->createFlyStraightAnimator(camera->getPosition(),
            irr::core::vector3df(5465, 933.016, 5133), 1000, false, false));
//        camera->addAnimator(_sceneManagers.at(_currentScene)->getSceneManager()->createRotationAnimator(irr::core::vector3df(5, 5, 5)));
//        camera->setPosition(irr::core::vector3df(5444.9 , 915.958, 5170.33));
//        camera->setTarget(irr::core::vector3df(5454.47 , -6597.6, 6044.77));
//        camera->setPosition(irr::core::)
    } else {
        _currentScene = "menu";
        _device->getCursorControl()->setVisible(true);
        _gui->getRootGUIElement()->setVisible(true);
    }
}
