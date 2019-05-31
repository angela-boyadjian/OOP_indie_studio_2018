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

    _sceneManagers.push_back(std::shared_ptr<ISceneManager>(new MenuScene(_device, _driver)));
    _sceneManagers.push_back(std::shared_ptr<ISceneManager>(new GameScene(_device, _driver)));
    _currentScene = _sceneManagers.at(0);
}

irr::core::vector3df    IrrlichtDisplay::pos3dToVector(const IDisplay::pos3d &pos)
{
    return irr::core::vector3df(std::get<0>(pos), std::get<1>(pos), std::get<2>(pos));
}

void    IrrlichtDisplay::addNewAnimation(const char *meshPath, const char *scenePath,
    const pos3d &scale)
{
    _sceneManagers.at(1)->addNewMesh(meshPath);
    _sceneManagers.at(1)->addNewMeshScene(scenePath, pos3dToVector(scale));
}

bool    IrrlichtDisplay::isRunning() const
{
    return _device->run();
}

void    IrrlichtDisplay::setGuiMessage(const wchar_t *message)
{
    _gui->addStaticText(message, irr::core::rect<irr::s32>(10,10,260,22), true);
}

void    IrrlichtDisplay::draw()
{
    _driver->beginScene(true, true, irr::video::SColor(255,100,101,140));
    _currentScene->getSceneManager()->drawAll();
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

IDisplay::Map3D &IrrlichtDisplay::getNonColiMap()
{
    return _noncoliMap;
}

void    IrrlichtDisplay::changeModelPos(const std::size_t &i, const pos3d &vec)
{
    auto newVec = pos3dToVector(vec);
    auto meshsScene = _sceneManagers.at(1)->getMeshScenes();

    newVec.X += 5400;
    newVec.Y += 808;
    newVec.Z += 5200;
    meshsScene[i]->setPosition(newVec);
}

void    IrrlichtDisplay::changeModelRot(const std::size_t &i, const pos3d &vec)
{
    auto meshsScene = _sceneManagers.at(1)->getMeshScenes();
    meshsScene[i]->setRotation(pos3dToVector((vec)));
}

void    IrrlichtDisplay::changeModelFrame(const std::size_t &i, const std::size_t &a, const std::size_t &b)
{
    auto meshsScene = _sceneManagers.at(1)->getMeshScenes();
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
    auto meshsScene = _sceneManagers.at(1)->getMeshScenes();
    auto b = meshsScene[target]->getBoundingBox();
    meshsScene[target]->getRelativeTransformation().transformBoxEx(b);
    return isCollisionFromMap(b) || isCollisionFromObstacles(b);
}

void    IrrlichtDisplay::destroyCollision(const std::size_t &target)
{
    auto meshsScene = _sceneManagers.at(1)->getMeshScenes();
    auto b = meshsScene[target]->getBoundingBox();
    meshsScene[target]->getRelativeTransformation().transformBoxEx(b);
    for (std::size_t i {0}; i < _coliMap.size(); ++i) {
        auto b2 = _coliMap[i]->getBoundingBox();
        _coliMap[i]->getRelativeTransformation().transformBoxEx(b2);
        if (b.intersectsWithBox(b2) && _coliMap[i]->isVisible())
            _coliMap[i]->setVisible(false);
    }
}

void    IrrlichtDisplay::changeScene()
{
    if (_currentScene == _sceneManagers.at(0)) {
        _currentScene = _sceneManagers.at(1);
        _device->getCursorControl()->setVisible(false);
        _gui->clear();
    } else {
        _currentScene = _sceneManagers.at(0);
        _device->getCursorControl()->setVisible(true);
    }
}
