/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** IntroScene
*/

#include "IntroScene.hpp"

IntroScene::IntroScene(std::shared_ptr<irr::IrrlichtDevice> device, irr::scene::ISceneNode *father,
    std::string const &name, const irr::core::dimension2du &size, irr::video::IVideoDriver *driver) :
    _master(device->getSceneManager()->addEmptySceneNode(father)),
    _manager(device->getSceneManager()),
    _name(name),
    _is_load(false),
    _win_size(size),
    _device(device)
{
    auto const &gui {device->getGUIEnvironment()};
    for (auto i {0}; i < 2; ++i)
        _images[i] = gui->addImage(irr::core::rect<irr::s32>(0, 0,
            _win_size.Width, _win_size.Height));
    _textures[0] = driver->getTexture("./../resources/ui/MainMenuBackground.jpg");
    _textures[1] = driver->getTexture("./../resources/ui/press_start.png");
    _master->setVisible(false);
}


std::string IntroScene::runScene()
{
    // if (!_is_load)
    //     throw SceneException("Scene is not load", _name.c_str()); // A CHANGER
    // if (_boutons[0]->isPressed())
    //     return "menu";
    return _name;
}

void IntroScene::loadScene()
{
    std::cout << "Load intro" << std::endl;
    _is_load = true;
    _cubes.emplace_back(_manager->addCubeSceneNode(10.0f, _master.get(), -1, irr::core::vector3df(0.0f, 0.0f, 20.0f)));
    _cubes.back()->setMaterialFlag(irr::video::EMF_WIREFRAME, true);
    _images[0]->setImage(_textures[0]);
    _images[0]->setScaleImage(true);
    _images[1]->setImage(_textures[1]);
    _images[1]->setRelativePosition(irr::core::position2di(250, 450));
    _images[1]->setVisible(true);
    _master->setVisible(true);
}

std::string IntroScene::getName() { return _name; }

void IntroScene::deLoad()
{
    std::cout << "Deload Intro" << std::endl;
    _master->setVisible(false);
}