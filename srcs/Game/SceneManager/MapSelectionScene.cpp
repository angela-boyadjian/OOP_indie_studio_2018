/*
** EPITECH PROJECT, 2019
** MapSelectionScene.cpp 
** File description:
** basile.lamarque@epitech.eu
*/

#include "MapSelectionScene.hpp"


MapSelectionScene::MapSelectionScene(Device &device, VideoDriver &driver) : _device(device), _driver(driver)
{
    _scene = _device->getSceneManager()->createNewSceneManager(false);

    setCameraScene();
}

void MapSelectionScene::setCameraScene()
{
    _camera = std::unique_ptr<irr::scene::ICameraSceneNode>(getSceneManager()->addCameraSceneNode(nullptr));
    _camera->setPosition(irr::core::vector3df(2700*2,900,2600*2));
    _camera->setTarget(irr::core::vector3df(2397*2,343*2,2700*2));
    _camera->setFarValue(42000.0f);
    _device->getCursorControl()->setVisible(true);
}

void MapSelectionScene::setTerrain()
{
    irr::video::ITexture *images = _driver->getTexture("./../resources/ui/bombermanTitle.png");

    _driver->enableMaterial2D();
    _driver->draw2DImage(images, irr::core::rect<irr::s32>(10, 10, 108, 48),
                         irr::core::rect<irr::s32>(354, 87, 442, 118));
    _driver->enableMaterial2D(false);
}

void   MapSelectionScene::setSkyDome()
{
}

void   MapSelectionScene::initTerrain()
{
}

void    MapSelectionScene::initAnimTerrain()
{
}

void    MapSelectionScene::setTerrainMaterial()
{
}

void    MapSelectionScene::addNewMesh(const char *meshPath)
{
}

void    MapSelectionScene::setMeshPosRot(irr::scene::IAnimatedMeshSceneNode *newScene)
{
}

void    MapSelectionScene::setMeshFrames(irr::scene::IAnimatedMeshSceneNode *newScene)
{
}

void    MapSelectionScene::setMeshAnimation(irr::scene::IAnimatedMeshSceneNode *newScene)
{
}

void    MapSelectionScene::addNewMeshScene(const char *scenePath, const irr::core::vector3df &scale)
{
}

ISceneManager::AnimatedMeshsScene MapSelectionScene::getMeshScenes()
{
    return _meshsScene;
}

ISceneManager::Scenes MapSelectionScene::getSceneManager()
{
    return _scene;
}
