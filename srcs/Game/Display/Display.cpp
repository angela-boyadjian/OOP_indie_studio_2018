#include <iostream>

#include "DisplayExceptions.hpp"
#include "Display.hpp"

Display::Display()
{
    _device = irr::createDevice(irr::video::EDT_OPENGL,
    irr::core::dimension2d<irr::u32>(640, 480));
    if (!_device)
        throw DeviceCreationError();
    _device->setWindowCaption(L"Bomberman");
    _gui = _device->getGUIEnvironment();
    _driver = _device->getVideoDriver();
    _scenes = _device->getSceneManager();
}

void    Display::addNewMesh(const char *meshPath)
{
    auto newMesh = _scenes->getMesh(meshPath);
    if (!newMesh)
        throw MeshCreationError();
    _meshs.push_back(newMesh);
}

void    Display::addNewMeshScene(const char *scenePath, irr::core::vector3df scale)
{
    auto newScene = _scenes->addAnimatedMeshSceneNode(_meshs.back());
    if (!newScene)
        throw MeshSceneCreationError();
    newScene->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    newScene->setMD2Animation(irr::scene::EMAT_STAND);
    newScene->setScale(scale);
    newScene->setRotation(irr::core::vector3df(0, 0, 0));
    newScene->setAnimationSpeed(30);
    newScene->setLoopMode(true);
    newScene->setFrameLoop(27, 76);
    newScene->setMaterialTexture(0, _driver->getTexture(scenePath));
    _meshsScene.push_back(newScene);
}

void    Display::addNewAnimation(const char *meshPath, const char *scenePath,
    irr::core::vector3df scale)
{
    addNewMesh(meshPath);
    addNewMeshScene(scenePath, scale);
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
    _scenes->addCameraSceneNode(0, irr::core::vector3df(0,30,-40), irr::core::vector3df(0,5,0));
}

void    Display::draw()
{
    _driver->beginScene(true, true, irr::video::SColor(255,100,101,140));
    _scenes->drawAll();
    _gui->drawAll();
    _driver->endScene();
}

IDisplay::Map3D &Display::getMap()
{
    return _map3d;
}