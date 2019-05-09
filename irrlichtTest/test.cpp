#include <irrlicht.h>

#include "Events.hpp"

int main()
{
    irr::IrrlichtDevice *device =
            irr::createDevice(irr::video::EDT_SOFTWARE, irr::core::dimension2d<irr::u32>(640, 480), 16,
                          false, false, false, 0);
    if (!device)
        return 1;
    device->setWindowCaption(L"Hello World! - Irrlicht Engine Demo");
    irr::video::IVideoDriver* driver = device->getVideoDriver();
    irr::scene::ISceneManager* smgr = device->getSceneManager();
    irr::gui::IGUIEnvironment* guienv = device->getGUIEnvironment();
    guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!",
                          irr::core::rect<irr::s32>(10,10,260,22), true);
    irr::scene::IAnimatedMesh* mesh = smgr->getMesh("./../LibIrrlicht/media/faerie.md2");
    irr::scene::IAnimatedMesh* mesh2 = smgr->getMesh("./../LibIrrlicht/media/sydney.md2");
    if (!mesh)
    {
        device->drop();
        return 1;
    }
    irr::scene::IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode( mesh );
    if (node)
    {
        node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        node->setMD2Animation(irr::scene::EMAT_STAND);
        node->setMaterialTexture( 0, driver->getTexture("./../LibIrrlicht/media/faerie2.bmp") );
    }
    irr::scene::IAnimatedMeshSceneNode* node2 = smgr->addAnimatedMeshSceneNode( mesh2 );
    if (node2)
    {
        node2->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        node2->setMD2Animation(irr::scene::EMAT_STAND);
        node2->setMaterialTexture( 0, driver->getTexture("./../LibIrrlicht/media/sydney.bmp") );
    }
    smgr->addCameraSceneNode(0, irr::core::vector3df(0,30,-40), irr::core::vector3df(0,5,0));
    while(device->run())
    {
        driver->beginScene(true, true, irr::video::SColor(255,100,101,140));

        smgr->drawAll();
        guienv->drawAll();

        driver->endScene();
    }
    device->drop();

    return 0;
}
