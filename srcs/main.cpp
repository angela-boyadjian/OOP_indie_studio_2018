/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** main
*/

#include "Bomberman.hpp"


#include "Map.hpp"
#include "Display.hpp"

#include <irrlicht.h>

int main()
{
//    Map map("./../resources/maps/1");
//    Display d;
    Menu menu;
    Display d;

    menu.load(d);
    while (d.isRunning()) {
        d.draw();
    }
//    map.load(d);
//    while (d.isRunning())
//        d.draw();
//    return 0;
//   core::Bomberman b;

 //   b.loadGame();
 //   b.run();
    return 0;
}

/*
int main(void)
{

    irr::IrrlichtDevice *device = irr::createDevice(    // creation du device
        irr::video::EDT_OPENGL,                           // API = OpenGL
        irr::core::dimension2d<irr::u32>(640,
                                         480),        // taille fenetre 640x480p
        32);                                              // 32 bits par pixel
    irr::video::IVideoDriver *driver =                  // creation du driver video
        device->getVideoDriver();
    irr::scene::ISceneManager *sceneManager =           // creation du scene manager
        device->getSceneManager();
    device->getCursorControl()->setVisible(
        false);   // rend le curseur invisible


    */
/* MODELE *//*

        //On charge le mesh
    irr::scene::IAnimatedMesh *mesh = sceneManager->getMesh("./../resources/models/Column/Column.obj");
    //On l'associe a un noeud de la scene
    irr::scene::IAnimatedMeshSceneNode *meshNode =
        sceneManager->addAnimatedMeshSceneNode(mesh);
    //On specifie sa texture
    meshNode->setMaterialTexture(0, driver->getTexture("./../resources/models/Column/Column.png"));
    //On rend le mesh insensible a la lumiere
    meshNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);

    */
/* CAMERA *//*


    irr::SKeyMap keyMap[5];                             // re-assigne les commandes
    keyMap[0].Action = irr::EKA_MOVE_FORWARD;           // avancer
    keyMap[0].KeyCode = irr::KEY_KEY_Z;                 // w
    keyMap[1].Action = irr::EKA_MOVE_BACKWARD;          // reculer
    keyMap[1].KeyCode = irr::KEY_KEY_S;                 // s
    keyMap[2].Action = irr::EKA_STRAFE_LEFT;            // a gauche
    keyMap[2].KeyCode = irr::KEY_KEY_Q;                 // a
    keyMap[3].Action = irr::EKA_STRAFE_RIGHT;           // a droite
    keyMap[3].KeyCode = irr::KEY_KEY_D;                 // d
    keyMap[4].Action = irr::EKA_JUMP_UP;                // saut
    keyMap[4].KeyCode = irr::KEY_SPACE;                 // barre espace

    sceneManager->addCameraSceneNodeFPS(                // ajout de la camera FPS
        0, 100.0f, 0.1f, -1, keyMap, 5);


    */
/* RENDU *//*


    while (device->run()) {                             // la boucle de rendu
        driver->beginScene(true, true,                    // demarre le rendu
                           irr::video::SColor(0, 255, 255, 255));
        sceneManager->drawAll();                         // calcule le rendu
        driver->endScene();                              // affiche le rendu
    }

    device->drop();                                    // libere la memoire
    return 0;
}
*/
