/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** main
*/

#include "Map.hpp"

#include <irrlicht.h>


using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

int main()
{
    IrrlichtDevice *device =
            createDevice(video::EDT_SOFTWARE, dimension2d<u32>(640, 480), 16,
                          false, false, false, 0);
    if (!device)
        return 1;
    IVideoDriver* driver = device->getVideoDriver();
    ISceneManager* smgr = device->getSceneManager();
    IGUIEnvironment* guienv = device->getGUIEnvironment();
    IAnimatedMesh* mesh = smgr->getMesh("../resources/models/Character/Bomberman.MD3");
    if (!mesh) {
        device->drop();
        return 1;
    }
    IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode(mesh);
    if (node) {
        node->setMaterialFlag(EMF_LIGHTING, false);
        node->setScale(vector3df(6, 6, 6));
        node->setRotation(vector3df(0, 0, 0));
        node->setAnimationSpeed(30);
        node->setLoopMode(true);
        node->setMD2Animation(scene::EMAT_STAND);
        node->setMaterialTexture(0, driver->getTexture("../resources/models/Character/RedBombermanTextures.png"));
        node->setFrameLoop(27, 76);
    }
    smgr->addCameraSceneNode(0, vector3df(0,30,-40), vector3df(0,5,0));
    while(device->run()) {
        driver->beginScene(true, true, SColor(255,100,101,140));
        smgr->drawAll();
        guienv->drawAll();
        driver->endScene();
    }
    device->drop();
    return 0;
}