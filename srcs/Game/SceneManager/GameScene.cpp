//
// Created by dclement on 5/22/19.
//

#include "GameScene.hpp"
#include "DisplayExceptions.hpp"
#include "irrlicht.h"

GameScene::GameScene(IDisplay::Device &device, IDisplay::VideoDriver &driver) : _device(device), _driver(driver)
{
    _scene = _device->getSceneManager()->createNewSceneManager(false);
    _scene->loadScene("test.irr");

    setCameraScene();
    setTerrain();
    setSkyDome();
}

void GameScene::setCameraScene()
{
    _camera = std::unique_ptr<irr::scene::ICameraSceneNode>(getSceneManager()->addCameraSceneNode(_scene->getRootSceneNode()));
//        _camera = std::unique_ptr<irr::scene::ICameraSceneNode>(getSceneManager()->addCameraSceneNodeFPS(0, 50.0f, 0.2f));
/*    _camera->setPosition(irr::core::vector3df(5444.9 , 915.958, 5170.33));
    _camera->setTarget(irr::core::vector3df(5454.47 , -6597.6, 6044.77));
    _camera->setFarValue(42000.0f);*/
    _camera->setRotation(irr::core::vector3df(2800, 900, 2700));
    _camera->setPosition(irr::core::vector3df(5603.27, 948.51, 5304.03));
    _camera->setTarget(irr::core::vector3df(5464.97, 811.798, 5180.71));
    _camera->setFarValue(42000.0f);
}

void GameScene::setTerrain()
{
    initTerrain();
    _selector = std::unique_ptr<irr::scene::ITriangleSelector>
            (getSceneManager()->createTerrainTriangleSelector(_terrain.get(), 0));
    _terrain->setTriangleSelector(_selector.get());
    initAnimTerrain();
    _selector->drop();
    _camera->addAnimator(_animTerrain.get());
    _animTerrain->drop();
}

void   GameScene::setSkyDome()
{
    _driver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, false);
    getSceneManager()->addSkyDomeSceneNode(_driver->getTexture("../lib/irrLicht/media/skydome.jpg"),16,8,0.95f,2.0f);
    _driver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, true);
}

void   GameScene::initTerrain()
{
    _terrain = std::unique_ptr<irr::scene::ITerrainSceneNode>(getSceneManager()->addTerrainSceneNode(
            "../lib/irrLicht/media/terrain-heightmap.bmp",
            nullptr, -1, irr::core::vector3df(0.f, 0.f, 0.f),
            irr::core::vector3df(0.f, 0.f, 0.f), irr::core::vector3df(40.f, 4.4f, 40.f),
            irr::video::SColor ( 255, 255, 255, 255 ), 5, irr::scene::ETPS_17, 4
    ));
    setTerrainMaterial();
    _terrain->scaleTexture(1.0f, 20.0f);
}

void    GameScene::initAnimTerrain()
{
    _animTerrain = std::unique_ptr<irr::scene::ISceneNodeAnimator>(getSceneManager()->createCollisionResponseAnimator(
            _selector.get(), _camera.get(), irr::core::vector3df(60,100,60),
            irr::core::vector3df(0,0,0),
            irr::core::vector3df(0,50,0)));
}

void    GameScene::setTerrainMaterial()
{
    _terrain->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    _terrain->setMaterialTexture(0, _driver->getTexture("../lib/irrLicht/media/terrain-texture.jpg"));
    _terrain->setMaterialTexture(1, _driver->getTexture("../lib/irrLicht/media/detailmap3.jpg"));
    _terrain->setMaterialType(irr::video::EMT_DETAIL_MAP);
}

void    GameScene::addNewMesh(const char *meshPath)
{
    auto newMesh = getSceneManager()->getMesh(meshPath);
    if (!newMesh)
        throw MeshCreationError();
    _meshs.push_back(std::unique_ptr<irr::scene::IAnimatedMesh>(newMesh));
}

void    GameScene::setMeshPosRot(irr::scene::IAnimatedMeshSceneNode *newScene)
{
    newScene->setRotation(irr::core::vector3df(0, 0, 0));
    newScene->setPosition(irr::core::vector3df(5400, 810, 5200));
}

void    GameScene::setMeshFrames(irr::scene::IAnimatedMeshSceneNode *newScene)
{
    newScene->setAnimationSpeed(30);
    newScene->setLoopMode(true);
    newScene->setFrameLoop(0, 27);
}

void    GameScene::setMeshAnimation(irr::scene::IAnimatedMeshSceneNode *newScene)
{
    newScene->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    newScene->setMD2Animation(irr::scene::EMAT_STAND);
}

void    GameScene::addNewMeshScene(const char *scenePath, const irr::core::vector3df &scale)
{
    auto newScene = getSceneManager()->addAnimatedMeshSceneNode(_meshs.back().get());
    if (!newScene)
        throw MeshSceneCreationError();
    setMeshAnimation(newScene);
    newScene->setScale(scale);
    setMeshPosRot(newScene);
    setMeshFrames(newScene);
    newScene->setMaterialTexture(0, _driver->getTexture(scenePath));
    _meshsScene.push_back(std::unique_ptr<irr::scene::IAnimatedMeshSceneNode>(newScene));
}

ISceneManager::AnimatedMeshsScene GameScene::getMeshScenes()
{
    return _meshsScene;
}

ISceneManager::Scenes GameScene::getSceneManager()
{
//    return _device->getSceneManager();
    return _scene;
}
