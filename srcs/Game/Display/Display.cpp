#include <iostream>

#include "DisplayExceptions.hpp"
#include "Display.hpp"

Display::Display()
{
}

void    Display::setDisplay(Events *events)
{
    _device = std::unique_ptr<irr::IrrlichtDevice>(irr::createDevice(irr::video::EDT_OPENGL,
                                         irr::core::dimension2d<irr::u32>(1200, 800), 16, false, false, false, events));
    if (!_device)
        throw DeviceCreationError();
    _device->setWindowCaption(L"Bomberman");
    _gui = std::unique_ptr<irr::gui::IGUIEnvironment>(_device->getGUIEnvironment());
    _driver = _device->getVideoDriver();
    _scenes = _device->getSceneManager();
}

irr::core::vector3df    Display::pos3dToVector(const IDisplay::pos3d &pos)
{
    return irr::core::vector3df(std::get<0>(pos), std::get<1>(pos), std::get<2>(pos));
}

void    Display::addNewMesh(const char *meshPath)
{
    auto newMesh = _scenes->getMesh(meshPath);
    if (!newMesh)
        throw MeshCreationError();
    _meshs.push_back(std::unique_ptr<irr::scene::IAnimatedMesh>(newMesh));
}

void    Display::addNewMeshScene(const char *scenePath, irr::core::vector3df scale)
{
    auto newScene = _scenes->addAnimatedMeshSceneNode(_meshs.back().get());
    if (!newScene)
        throw MeshSceneCreationError();
    newScene->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    newScene->setMD2Animation(irr::scene::EMAT_STAND);
    newScene->setScale(scale);
    newScene->setRotation(irr::core::vector3df(0, 0, 0));
    newScene->setAnimationSpeed(30);
    newScene->setLoopMode(true);
//    newScene->setFrameLoop(27, 76);
    newScene->setFrameLoop(0, 27);
    newScene->setMaterialTexture(0, _driver->getTexture(scenePath));
    _meshsScene.push_back(std::unique_ptr<irr::scene::IAnimatedMeshSceneNode>(newScene));
}

void    Display::addNewAnimation(const char *meshPath, const char *scenePath,
    const pos3d &scale)
{
    addNewMesh(meshPath);
    addNewMeshScene(scenePath, pos3dToVector(scale));
}

bool    Display::isRunning() const
{
    return _device->run();
}

void    Display::setGuiMessage(const wchar_t *message)
{
    _gui->addStaticText(message, irr::core::rect<irr::s32>(10,10,260,22), true);
}

void    Display::setCameraScene()
{
    _scenes->addCameraSceneNode(nullptr,
            irr::core::vector3df(0, 0, -120), irr::core::vector3df(0, 0, 0));
}

void    Display::draw()
{
    _driver->beginScene(true, true, irr::video::SColor(255,100,101,140));
    _scenes->drawAll();
    _gui->drawAll();
    _driver->endScene();
}

Display::Gui const &Display::getGui()
{
    return _gui;
}

Display::Device const &Display::getDevice()
{
    return _device;
}

irr::core::dimension2du const &Display::getScreenSize()
{
    return _driver->getScreenSize();
}
IDisplay::Map3D &Display::getMap()
{
    return _map3d;
}

void    Display::changeModelPos(const std::size_t &i, const pos3d &vec)
{
    _meshsScene[i]->setPosition(pos3dToVector(vec));
}

void    Display::changeModelRot(const std::size_t &i, const pos3d &vec)
{
    _meshsScene[i]->setRotation(pos3dToVector(vec));
}

void    Display::changeModelFrame(const std::size_t &i, const std::size_t &a, const std::size_t &b)
{
    _meshsScene[i]->setFrameLoop(a, b);
}
