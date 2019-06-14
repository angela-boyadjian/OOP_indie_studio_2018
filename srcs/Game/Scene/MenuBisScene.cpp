/*
** EPITECH PROJECT, 2019
** MenuScene.cpp 
** File description:
** basile.lamarque@epitech.eu
*/

#include "SceneException.hpp"
#include "MenuBisScene.hpp"

MenuBisScene::MenuBisScene(std::shared_ptr<irr::IrrlichtDevice> device, irr::scene::ISceneNode *father, const std::string &name, const irr::core::dimension2du& size) :
    _master(device->getSceneManager()->addEmptySceneNode(father)),
    _manager(device->getSceneManager()),
    _name(name),
    _is_load(false),
    _win_size(size),
    _device(device)

{
    _master->setVisible(false);
}

std::string MenuBisScene::runScene()
{
    if (!_is_load)
        throw SceneException("Scene is not load", _name.c_str()); // A CHANGER
    if (_boutons[0]->isPressed())
        return "game";
    return _name;
}

void MenuBisScene::loadBoutons()
{
    _boutons.emplace_back(_manager->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(_win_size.Width / 2 - 300, 440,
                                                                                             _win_size.Width / 2 + 300, 440 + 42), nullptr, 102, L"Start Game"));
    _boutons.emplace_back(_manager->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(_win_size.Width / 2 - 300, 440 + 42 + 10,
                                                                                             _win_size.Width / 2 + 300, 440 + 42 + 10 + 42), nullptr, 103, L"Settings"));
    _boutons.emplace_back(_manager->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(_win_size.Width / 2 - 300, 440 + 84 + 20,
                                                                                             _win_size.Width / 2 + 300, 440 + 84 + 20 + 42), nullptr, 101, L"Exit"));

}

void MenuBisScene::loadScene()
{
    std::cout << "Load menu" << std::endl;
    _is_load = true;
    _cubes.emplace_back(_manager->addCubeSceneNode(10.0f, _master.get(), -1, irr::core::vector3df(0.0f, 0.0f, 20.0f)));
    _cubes.back()->setMaterialFlag(irr::video::EMF_WIREFRAME, true);
    loadBoutons();
    _master->setVisible(true);
}

std::string MenuBisScene::getName()
{
    return _name;
}

void MenuBisScene::deLoad()
{
    std::cout << "Deload Menu" << std::endl;
    _master->setVisible(false);
    for (auto &bouton : _boutons)
        bouton->remove();
}