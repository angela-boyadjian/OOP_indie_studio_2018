/*
** EPITECH PROJECT, 2019
** main.cpp 
** File description:
** basile.lamarque@epitech.eu
*/

#include <irrlicht.h>
#include <memory>

#include "SceneManager.hpp"
#include "GameScene.hpp"
#include "MenuScene.hpp"

int main()
{
    irr::IrrlichtDevice* device = irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(200,200), 32);
    irr::video::IVideoDriver* driver = device->getVideoDriver ();
    SceneManager manager(device->getSceneManager());
    manager.addScenes(std::make_unique<MenuScene>(MenuScene(manager.getManager(), manager.getMaster(), "menu")));
    manager.addScenes(std::make_unique<GameScene>(GameScene(manager.getManager(), manager.getMaster(), "menu")));
    manager.setCurrent("menu");
    manager.loadCurrent();

    irr::SKeyMap keyMap[5];                    // re-assigne les commandes
    keyMap[0].Action = irr::EKA_MOVE_FORWARD;  // avancer
    keyMap[0].KeyCode = irr::KEY_KEY_W;        // w
    keyMap[1].Action = irr::EKA_MOVE_BACKWARD; // reculer
    keyMap[1].KeyCode = irr::KEY_KEY_S;        // s
    keyMap[2].Action = irr::EKA_STRAFE_LEFT;   // a gauche
    keyMap[2].KeyCode = irr::KEY_KEY_A;        // a
    keyMap[3].Action = irr::EKA_STRAFE_RIGHT;  // a droite
    keyMap[3].KeyCode = irr::KEY_KEY_D;        // d
    keyMap[4].Action = irr::EKA_JUMP_UP;       // saut
    keyMap[4].KeyCode = irr::KEY_SPACE;        // barre espace

    manager.getManager()->addCameraSceneNodeFPS(       // ajout de la camera FPS
        0,                                     // pas de noeud parent
        100.0f,                                // vitesse de rotation
        0.1f,                                  // vitesse de deplacement
        -1,                                    // pas de numero d'ID
        keyMap,                                // on change la keymap
        5);                                    // avec une taille de 5


    while (device->run()) {
        driver->beginScene(true, true,  irr::video::SColor(255, 255, 255, 255));
        manager.runCurrentScene();
        driver->endScene();
    }
}



/*
int main(void) {

    irr::IrrlichtDevice* device = irr::createDevice(  // creation du device
        irr::video::EDT_OPENGL,                       // API = OpenGL
        irr::core::dimension2d<irr::u32>(200,200),    // taille fenetre 640x480p
        32);                                          // 32 bits par pixel

    irr::video::IVideoDriver* driver =                // video driver
        device->getVideoDriver ();
    irr::scene::ISceneManager* sceneManager =         // scene manager
        device->getSceneManager ();

    device->getCursorControl ()-> setVisible (false); // curseur invisible


    irr::scene::IMeshSceneNode* cube =         // pointeur vers le node
        sceneManager->addCubeSceneNode(        // la creation du cube
            10.0f,                             // cote de 10 unites
            0,                                 // parent = racine
            -1,                                // pas d'ID
            irr::core::vector3df(              // le vecteur de position
                0.0f,                          // origine en X
                0.0f,                          // origine en Y
                20.0f));                       // +20 unites en Z

    cube->setMaterialFlag(irr::video::EMF_WIREFRAME, true);


    irr::SKeyMap keyMap[5];                    // re-assigne les commandes
    keyMap[0].Action = irr::EKA_MOVE_FORWARD;  // avancer
    keyMap[0].KeyCode = irr::KEY_KEY_W;        // w
    keyMap[1].Action = irr::EKA_MOVE_BACKWARD; // reculer
    keyMap[1].KeyCode = irr::KEY_KEY_S;        // s
    keyMap[2].Action = irr::EKA_STRAFE_LEFT;   // a gauche
    keyMap[2].KeyCode = irr::KEY_KEY_A;        // a
    keyMap[3].Action = irr::EKA_STRAFE_RIGHT;  // a droite
    keyMap[3].KeyCode = irr::KEY_KEY_D;        // d
    keyMap[4].Action = irr::EKA_JUMP_UP;       // saut
    keyMap[4].KeyCode = irr::KEY_SPACE;        // barre espace

    sceneManager->addCameraSceneNodeFPS(       // ajout de la camera FPS
        0,                                     // pas de noeud parent
        100.0f,                                // vitesse de rotation
        0.1f,                                  // vitesse de deplacement
        -1,                                    // pas de numero d'ID
        keyMap,                                // on change la keymap
        5);                                    // avec une taille de 5



    irr::video::SColor color(                  // contient la couleur blanc
        255,                                   // composante A alpha (transparence)
        255,                                   // composante R rouge
        255,                                   // composante G verte
        255);                                  // composante B bleue

    while (device->run()) {                    // la boucle de rendu
        driver->beginScene(true, true, color); // demarre le rendu
        sceneManager->drawAll ();              // calcule le rendu
        driver->endScene ();                   // affiche le rendu
    }

    device->drop ();                           // libere la memoire
    return 0;
}
*/



