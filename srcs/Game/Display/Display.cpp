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
    _camera = std::unique_ptr<irr::scene::ICameraSceneNode>(_scenes->addCameraSceneNodeFPS(0, 100.0f, 1.2f));
    _camera->setPosition(irr::core::vector3df(2700*2,255*2,2600*2));
    _camera->setTarget(irr::core::vector3df(2397*2,343*2,2700*2));
    _camera->setFarValue(42000.0f);
    // disable mouse cursor
    _device->getCursorControl()->setVisible(false);
    setTerrain();
    setSkyDome();
}

void    Display::setTerrain()
{
    _terrain = _scenes->addTerrainSceneNode(
            "../lib/irrLicht/media/terrain-heightmap.bmp",
            nullptr,                  // parent node
            -1,                 // node id
            irr::core::vector3df(0.f, 0.f, 0.f),     // position
            irr::core::vector3df(0.f, 0.f, 0.f),     // rotation
            irr::core::vector3df(40.f, 4.4f, 40.f),  // scale
            irr::video::SColor ( 255, 255, 255, 255 ),   // vertexColor
            5,                  // maxLOD
            irr::scene::ETPS_17,             // patchSize
            4                   // smoothFactor
    );
    _terrain->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    _terrain->setMaterialTexture(0, _driver->getTexture("../lib/irrLicht/media/terrain-texture.jpg"));
    _terrain->setMaterialTexture(1, _driver->getTexture("../lib/irrLicht/media/detailmap3.jpg"));
    _terrain->setMaterialType(irr::video::EMT_DETAIL_MAP);
    _terrain->scaleTexture(1.0f, 20.0f);
    irr::scene::ITriangleSelector* selector
            = _scenes->createTerrainTriangleSelector(_terrain, 0);
    _terrain->setTriangleSelector(selector);

    // create collision response animator and attach it to the camera
    irr::scene::ISceneNodeAnimator* anim = _scenes->createCollisionResponseAnimator(
            selector, _camera.get(), irr::core::vector3df(60,100,60),
            irr::core::vector3df(0,0,0),
            irr::core::vector3df(0,50,0));
    selector->drop();
    _camera->addAnimator(anim);
    anim->drop();
}

void    Display::setSkyDome()
{
    _driver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, false);

    irr::scene::ISceneNode* skybox = _scenes->addSkyBoxSceneNode(
            _driver->getTexture("../lib/irrLicht/media/irrlicht2_up.jpg"),
            _driver->getTexture("../lib/irrLicht/media/irrlicht2_dn.jpg"),
            _driver->getTexture("../lib/irrLicht/media/irrlicht2_lf.jpg"),
            _driver->getTexture("../lib/irrLicht/media/irrlicht2_rt.jpg"),
            _driver->getTexture("../lib/irrLicht/media/irrlicht2_ft.jpg"),
            _driver->getTexture("../lib/irrLicht/media/irrlicht2_bk.jpg"));
    irr::scene::ISceneNode* skydome = _scenes->addSkyDomeSceneNode(_driver->getTexture("../lib/irrLicht/media/skydome.jpg"),16,8,0.95f,2.0f);
    _driver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, true);
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
//    _scenes->addCameraSceneNode(nullptr,
//            irr::core::vector3df(0, 0, -120), irr::core::vector3df(0, 0, 0));
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
