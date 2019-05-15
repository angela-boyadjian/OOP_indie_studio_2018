/*
** EPITECH PROJECT, 2019
** main.cpp 
** File description:
** basile.lamarque@epitech.eu
*/

#include <irrlicht.h>
#include <fcntl.h>
#include "CEventReceiver.hpp"

/*
int main(void)
{

    //Device, driver et graphe de scene.
    irr::IrrlichtDevice* device = irr::createDevice(irr::video::EDT_OPENGL,
                                                    irr::core::dimension2d<irr::u32>(800,800),32,false,false,false);
    irr::video::IVideoDriver* driver = device->getVideoDriver ();
    irr::scene::ISceneManager *sceneManager = device->getSceneManager ();

    //On rend invisible le curseur.
    device->getCursorControl ()-> setVisible (false);

    //Sydney
    irr::scene::IAnimatedMeshMD2* modele;
    modele = (irr::scene::IAnimatedMeshMD2*)sceneManager->getMesh("./../LibIrrlicht/media/sydney.md2");
    irr::scene::IAnimatedMeshSceneNode* Nmodele =
        sceneManager->addAnimatedMeshSceneNode(modele);

    //On modifie les proprietes de Sydney
    Nmodele->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    Nmodele->setFrameLoop(0, 0);
    Nmodele->setMaterialTexture( 0, driver->getTexture("./../LibIrrlicht/media/sydney.bmp") );

    //La camera
    irr::scene::ICameraSceneNode *camera;
    camera = sceneManager->addCameraSceneNodeFPS (0,100.0f,300.0f);

    //On cree le capteur d'event et on l'associe au device.
    CEventReceiver receiver(Nmodele);
    device->setEventReceiver(&receiver);

    //La boucle de rendu
    while (device->run())
    {
        driver->beginScene(true, true, irr::video::SColor(0,200,200,200));
        //Met a jour la position du mesh
        receiver.majPosMesh();
        sceneManager->drawAll ();
        driver->endScene ();
    }

    device->drop ();
    return 0;
}*/


int main(void)
{
    //Device, driver et graphe de scene.
    irr::IrrlichtDevice* device = irr::createDevice(irr::video::EDT_OPENGL,
                                                    irr::core::dimension2d<irr::u32>(800,800),32,false,false,false);
    irr::video::IVideoDriver* driver = device->getVideoDriver ();
    irr::scene::ISceneManager *sceneManager = device->getSceneManager ();

    //On rend invisible le curseur.
    device->getCursorControl ()-> setVisible (false);

    //La camera
    irr::SKeyMap keyMap[5];
    keyMap[0].Action = irr::EKA_MOVE_FORWARD;
    keyMap[0].KeyCode = irr::KEY_KEY_Z;
    keyMap[1].Action = irr::EKA_MOVE_BACKWARD;
    keyMap[1].KeyCode = irr::KEY_KEY_S;
    keyMap[2].Action = irr::EKA_STRAFE_LEFT;
    keyMap[2].KeyCode = irr::KEY_KEY_Q;
    keyMap[3].Action = irr::EKA_STRAFE_RIGHT;
    keyMap[3].KeyCode = irr::KEY_KEY_D;
    keyMap[4].Action = irr::EKA_JUMP_UP;
    keyMap[4].KeyCode = irr::KEY_SPACE;
    irr::scene::ICameraSceneNode *camera;
    camera = sceneManager->addCameraSceneNodeFPS (0,100.0f,0.02f, -1, keyMap, 5, false, 0.4);
    camera->setPosition(irr::core::vector3df(0.0f, 0.0f, 0.0f));

    //La chaine pour le titre de la fenetre
    irr::core::vector3df posCam;
    wchar_t titre[100];


    camera->setPosition(irr::core::vector3df(60.0f, 60.0f, 0.0f));
    camera->setTarget(irr::core::vector3df(0.0f, 40.0f, 0.0f));


    irr::scene::IParticleSystemSceneNode* particleSystem =
        sceneManager->addParticleSystemSceneNode(false);

    irr::scene::IParticleEmitter* emitter = particleSystem->createBoxEmitter(
        irr::core::aabbox3d<irr::f32>(100,300,-100,-100,0,100), // coordonnees de la boite
        irr::core::vector3df(0.0f,-0.06f,0.0f),        // direction de diffusion
        180,200,                                       // nb particules emises a la sec min / max
        irr::video::SColor(0,255,255,255),                  // couleur la plus sombre
        irr::video::SColor(0,255,255,255),            // couleur la plus claire
        600, 1000,                                    // duree de vie min / max
        30,                                            // angle max d'ecart / direction prevue
        irr::core::dimension2df(6.0f,6.0f),           // taille minimum
        irr::core::dimension2df(8.0f,8.0f));          // taille maximum

    particleSystem->setEmitter(emitter);                               // on attache l'emetteur
    emitter->drop();                                                   // plus besoin de ca
    particleSystem->setMaterialFlag(irr::video::EMF_LIGHTING, false);          // insensible a la lumiere
    particleSystem->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);     // desactive zbuffer pour surfaces derriere
    particleSystem->setMaterialTexture(0, driver->getTexture("./../LibIrrlicht/media/fire.bmp"));     // on colle une texture
    particleSystem->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR); // application transparence



    //La boucle de rendu
    while (device->run())
    {
        posCam = camera->getPosition();
        swprintf(titre, 100, L"FPS : %d (mode debug) |  PosCam :  "
                             "X : %f Y : %f Z : %f", driver->getFPS(), posCam.X, posCam.Y, posCam.Z);
        device->setWindowCaption(titre);
        //On utilise un fond blanc pour voir les particules
        driver->beginScene(true, true, irr::video::SColor(0,0,0,0));
        sceneManager->drawAll ();
        driver->endScene ();
    }

    device->drop();
    return 0;
}


/*

int main(void) {
    irr::IrrlichtDevice *device = irr::createDevice (
        irr::video::EDT_OPENGL,
        irr::core::dimension2d<irr::u32>(800,600),
        32);
    irr::video::IVideoDriver* driver = device->getVideoDriver ();
    irr::scene::ISceneManager *sceneManager = device->getSceneManager ();

    irr::scene::ICameraSceneNode *camera =                        // creation de la camera
        sceneManager->addCameraSceneNodeFPS (0,80.0f,100.0f);
    camera->setPosition(irr::core::vector3df(10.0, 50.0, -50.0)); // positionnement

    irr::scene::IAnimatedMesh *room =                             // chargement du modele
        sceneManager->getMesh("./../LibIrrlicht/media/room.3ds");
    irr::scene::IMeshSceneNode *Nroom =                           // creation du node
        sceneManager->addMeshSceneNode(room->getMesh(0));
    Nroom->setMaterialFlag(irr::video::EMF_LIGHTING, true);            // sensible a la lumiere

    sceneManager->getMeshManipulator()->                          // parametrage de la texture
        makePlanarTextureMapping(room->getMesh(0), 0.004f);
    Nroom->setMaterialTexture(0,                                  // application de la texture
                              driver->getTexture("./../LibIrrlicht/media/rockwall.jpg") );

sceneManager->setAmbientLight(                                // ajout lumiere
        irr::video::SColorf(1.0, 1.0, 1.0,0.0));

irr::scene::ILightSceneNode* lumiere = sceneManager->addLightSceneNode(
        Nroom,
        irr::core::vector3df(100,100,200),
        irr::video::SColorf(0.4f, 0.4f, 0.6f, 0.0f),
        400.0f);

    while (device->run ())                                        // la boucle de rendu
    {
        driver->beginScene (true, true,
                            irr::video::SColor (255,255,255,255));
        sceneManager->drawAll ();
        driver->endScene ();
    }

    device->drop ();
    return 0;
}
*/


/*

int main(void) {

    irr::IrrlichtDevice* device = irr::createDevice(    // creation du device
        irr::video::EDT_OPENGL,                           // API = OpenGL
        irr::core::dimension2d<irr::u32>(640,480),        // taille fenetre 640x480p
        32);                                              // 32 bits par pixel
    irr::video::IVideoDriver* driver =                  // creation du driver video
        device->getVideoDriver ();
    irr::scene::ISceneManager* sceneManager =           // creation du scene manager
        device->getSceneManager ();
    device->getCursorControl ()-> setVisible (false);   // rend le curseur invisible


    */
/* MODELE *//*


    irr::scene::IAnimatedMeshSceneNode *sydney =        // cree un scene node nomme sydney
        sceneManager->addAnimatedMeshSceneNode (          // via le scene manager
            sceneManager->getMesh ("./../LibIrrlicht/media/sydney.md2"));          // en chargeant le mesh "sydney.md2"

    sydney->setMaterialFlag(
        irr::video::EMF_LIGHTING, false);
    sydney->setMaterialTexture(
        0, driver->getTexture("./../LibIrrlicht/media/sydney.bmp"));

    sydney->setMD2Animation(irr::scene::EMAT_STAND);    // joue l'animation STAND en boucle


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
                           irr::video::SColor(0,255,255,255));
        sceneManager->drawAll ();                         // calcule le rendu
        driver->endScene ();                              // affiche le rendu
    }

    device->drop ();                                    // libere la memoire
    return 0;
}*/
