//
// Created by dclement on 6/13/19.
//

#include "SettingScene.hpp"

SettingScene::SettingScene(ISceneManager::Device &device,
    ISceneManager::VideoDriver &driver) : _device(device), _driver(driver)
{
    _scene = _device->getSceneManager()->createNewSceneManager(false);
}

void SettingScene::setCameraScene()
r{
    _camera = std::unique_ptr<irr::scene::ICameraSceneNode>(getSceneManager()->addCameraSceneNode(nullptr));
    _camera->setPosition(irr::core::vector3df(2700*2,900,2600*2));
    _camera->setTarget(irr::core::vector3df(2397*2,343*2,2700*2));
    _camera->setFarValue(42000.0f);
    _device->getCursorControl()->setVisible(true);
}

void SettingScene::setTerrain()
{
}

void SettingScene::setSkyDome()
{
}

void   SettingScene::initTerrain()
{
}

void    SettingScene::initAnimTerrain()
{
}

void    SettingScene::setTerrainMaterial()
{
}

void    SettingScene::addNewMesh(const char *meshPath)
{
}

void    SettingScene::setMeshPosRot(irr::scene::IAnimatedMeshSceneNode *newScene)
{
}

void    SettingScene::setMeshFrames(irr::scene::IAnimatedMeshSceneNode *newScene)
{
}

void    SettingScene::setMeshAnimation(irr::scene::IAnimatedMeshSceneNode *newScene)
{
}

void    SettingScene::addNewMeshScene(const char *scenePath, const irr::core::vector3df &scale)
{
}

ISceneManager::AnimatedMeshsScene SettingScene::getMeshScenes()
{
    return _meshsScene;
}

ISceneManager::Scenes SettingScene::getSceneManager()
{
    return _scene;
}
