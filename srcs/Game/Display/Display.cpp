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
    setCameraScene();
    setTerrain();
    setSkyDome();
}

void    Display::setTerrain()
{
    initTerrain();
    _selector = std::unique_ptr<irr::scene::ITriangleSelector>
            (_scenes->createTerrainTriangleSelector(_terrain, 0));
    _terrain->setTriangleSelector(_selector.get());
    initAnimTerrain();
    _selector->drop();
    _camera->addAnimator(_animTerrain.get());
    _animTerrain->drop();
}

void    Display::setSkyDome()
{
    _driver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, false);
    _scenes->addSkyDomeSceneNode(_driver->getTexture("../lib/irrLicht/media/skydome.jpg"),16,8,0.95f,2.0f);
    _driver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, true);
}

void    Display::initTerrain()
{
    _terrain = _scenes->addTerrainSceneNode(
            "../lib/irrLicht/media/terrain-heightmap.bmp",
            nullptr, -1, irr::core::vector3df(0.f, 0.f, 0.f),
            irr::core::vector3df(0.f, 0.f, 0.f), irr::core::vector3df(40.f, 4.4f, 40.f),
            irr::video::SColor ( 255, 255, 255, 255 ), 5, irr::scene::ETPS_17, 4
    );
    setTerrainMaterial();
    _terrain->scaleTexture(1.0f, 20.0f);
}

void    Display::initAnimTerrain()
{
    _animTerrain = std::unique_ptr<irr::scene::ISceneNodeAnimator>(_scenes->createCollisionResponseAnimator(
            _selector.get(), _camera.get(), irr::core::vector3df(60,100,60),
            irr::core::vector3df(0,0,0),
            irr::core::vector3df(0,50,0)));
}

void    Display::setTerrainMaterial()
{
    _terrain->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    _terrain->setMaterialTexture(0, _driver->getTexture("../lib/irrLicht/media/terrain-texture.jpg"));
    _terrain->setMaterialTexture(1, _driver->getTexture("../lib/irrLicht/media/detailmap3.jpg"));
    _terrain->setMaterialType(irr::video::EMT_DETAIL_MAP);
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

void    Display::setMeshPosRot(irr::scene::IAnimatedMeshSceneNode *newScene)
{
    newScene->setRotation(irr::core::vector3df(0, 0, 0));
    newScene->setPosition(irr::core::vector3df(5400, 810, 5200));
}

void    Display::setMeshFrames(irr::scene::IAnimatedMeshSceneNode *newScene)
{
    newScene->setAnimationSpeed(30);
    newScene->setLoopMode(true);
    newScene->setFrameLoop(0, 27);
}

void    Display::setMeshAnimation(irr::scene::IAnimatedMeshSceneNode *newScene)
{
    newScene->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    newScene->setMD2Animation(irr::scene::EMAT_STAND);
}

void    Display::addNewMeshScene(const char *scenePath, const irr::core::vector3df &scale)
{
    auto newScene = _scenes->addAnimatedMeshSceneNode(_meshs.back().get());
    if (!newScene)
        throw MeshSceneCreationError();
    setMeshAnimation(newScene);
    newScene->setScale(scale);
    setMeshPosRot(newScene);
    setMeshFrames(newScene);
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
//    _camera = std::unique_ptr<irr::scene::ICameraSceneNode>(_scenes->addCameraSceneNodeFPS(0, 100.0f, 1.2f));
    _camera = std::unique_ptr<irr::scene::ICameraSceneNode>(_scenes->addCameraSceneNode(nullptr));
    _camera->setPosition(irr::core::vector3df(2700*2,255*2,2600*2));
    _camera->setTarget(irr::core::vector3df(2397*2,343*2,2700*2));
    _camera->setFarValue(42000.0f);
    _device->getCursorControl()->setVisible(true);
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
    auto newVec = pos3dToVector(vec);
    newVec.X += 5400;
    newVec.Y += 808;
    newVec.Z += 5200;
    _meshsScene[i]->setPosition(newVec);
}

void    Display::changeModelRot(const std::size_t &i, const pos3d &vec)
{
    _meshsScene[i]->setRotation(pos3dToVector(vec));
}

void    Display::changeModelFrame(const std::size_t &i, const std::size_t &a, const std::size_t &b)
{
    _meshsScene[i]->setFrameLoop(a, b);
}

bool    Display::isCollision(const std::size_t &target)
{
    auto b = _meshsScene[target]->getBoundingBox();
    _meshsScene[target]->getRelativeTransformation().transformBoxEx(b);
    for (std::size_t i {0}; i < _map3d.size(); ++i) {
        auto b2 = _map3d[i]->getBoundingBox();
        _map3d[i]->getRelativeTransformation().transformBoxEx(b2);
        if (b.intersectsWithBox(b2) && _map3d[i]->isVisible())
            return true;
    }
    return false;
}

void    Display::destroyCollision(const std::size_t &target)
{
    auto b = _meshsScene[target]->getBoundingBox();
    _meshsScene[target]->getRelativeTransformation().transformBoxEx(b);
    for (std::size_t i {0}; i < _map3d.size(); ++i) {
        auto b2 = _map3d[i]->getBoundingBox();
        _map3d[i]->getRelativeTransformation().transformBoxEx(b2);
        if (b.intersectsWithBox(b2) && _map3d[i]->isVisible())
            _map3d[i]->setVisible(false);
    }
}