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
#include "MenuBisScene.hpp"

int main()
{
    irr::IrrlichtDevice* device = irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(800,600), 32);
    irr::video::IVideoDriver* driver = device->getVideoDriver ();
    SceneManager manager(device->getSceneManager());
    manager.addScenes(std::make_unique<MenuScene>(MenuScene(manager.getManager(), manager.getMaster(), "menu")));
    manager.addScenes(std::make_unique<GameScene>(GameScene(manager.getManager(), manager.getMaster(), "game")));

    manager.changeCurrent("menu");
    while (device->run()) {
        driver->beginScene(true, true,  irr::video::SColor(255, 255, 255, 255));
        manager.runCurrentScene();
        driver->endScene();
    }
}
/*

int main(void)
{
    irr::IrrlichtDevice *device = irr::createDevice (
        irr::video::EDT_OPENGL,
        irr::core::dimension2d<irr::u32>(800,600),
        32,false,true,false,0);
    irr::video::IVideoDriver* driver = device->getVideoDriver ();
    irr::scene::ISceneManager *sceneManager = device->getSceneManager ();

    // recuperation GUI et police
    irr::gui::IGUIEnvironment *gui = sceneManager->getGUIEnvironment();
    irr::gui::IGUIFont *font = gui->getFont("fontlucida.png");


    irr::gui::IGUIButton *bouton = gui->addButton(
        irr::core::rect<irr::s32>(100,80,200,120),  // positoin du bouton
        0, -1, L"tagada tsoin tsoin");              // texte
    bouton->setOverrideFont(font);                  // changement de police


    while (device->run ())                          // boucle de rendu
    {
        driver->beginScene (true, true,
                            irr::video::SColor (150,150,255,255));
        sceneManager->drawAll ();
        gui->drawAll();
        driver->endScene ();
    }

    device->drop ();
    return 0;
}
*/


