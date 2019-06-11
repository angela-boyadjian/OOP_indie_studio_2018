//
// Created by dclement on 5/24/19.
//

#include "MenuScene.hpp"
#include "ISceneManager.hpp"
#include "DisplayExceptions.hpp"

#include <iostream>

MenuScene::MenuScene(Device &device, VideoDriver &driver) : _device(device), _driver(driver)
{
    _scene = _device->getSceneManager()->createNewSceneManager(false);

    setCameraScene();
//    setTerrain();
//    setSkyDome();
}

void MenuScene::setCameraScene()
{
    _camera = std::unique_ptr<irr::scene::ICameraSceneNode>(getSceneManager()->addCameraSceneNode(nullptr));
    _camera->setPosition(irr::core::vector3df(2700*2,900,2600*2));
    _camera->setTarget(irr::core::vector3df(2397*2,343*2,2700*2));
    _camera->setFarValue(42000.0f);
    _device->getCursorControl()->setVisible(true);
}

void MenuScene::setTerrain()
{
}

void   MenuScene::setSkyDome()
{
}

void   MenuScene::initTerrain()
{
}

void    MenuScene::initAnimTerrain()
{
}

void    MenuScene::setTerrainMaterial()
{
}

void    MenuScene::addNewMesh(const char *meshPath)
{
}

void    MenuScene::setMeshPosRot(irr::scene::IAnimatedMeshSceneNode *newScene)
{
}

void    MenuScene::setMeshFrames(irr::scene::IAnimatedMeshSceneNode *newScene)
{
}

void    MenuScene::setMeshAnimation(irr::scene::IAnimatedMeshSceneNode *newScene)
{
}

void    MenuScene::addNewMeshScene(const char *scenePath, const irr::core::vector3df &scale)
{
}

ISceneManager::AnimatedMeshsScene MenuScene::getMeshScenes()
{
    return _meshsScene;
}

ISceneManager::Scenes MenuScene::getSceneManager()
{
    return _scene;
}
