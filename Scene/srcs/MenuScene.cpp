/*
** EPITECH PROJECT, 2019
** MenuScene.cpp 
** File description:
** basile.lamarque@epitech.eu
*/

#include "SceneException.hpp"
#include "MenuScene.hpp"

MenuScene::MenuScene(irr::scene::ISceneManager *manager, irr::scene::ISceneNode *father, const std::string &name) :
    _master(manager->addEmptySceneNode(father)),
    _manager(manager),
    _name(name),
    _is_load(false)
{
    _master->setVisible(false);
}

std::string MenuScene::runScene()
{
    if (!_is_load)
        throw SceneException("Scene is not load", _name.c_str()); // A CHANGER
    if (_bouton->isPressed())
        return "game";
    return _name;
}

void MenuScene::loadScene()
{
    std::cout << "Load menu" << std::endl;
    _is_load = true;
    _cubes.emplace_back(_manager->addCubeSceneNode(10.0f, _master.get(), -1, irr::core::vector3df(0.0f, 0.0f, 20.0f)));
    _cubes.back()->setMaterialFlag(irr::video::EMF_WIREFRAME, true);
    _cubes.emplace_back(_manager->addCameraSceneNode(_master.get(), irr::core::vector3df(0.0f, 0.0f, 0.0f)));
    _bouton = _manager->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(100,80,200,120), nullptr, -1, L"PLAY");
    _master->setVisible(true);
}

std::string MenuScene::getName()
{
    return _name;
}

void MenuScene::deLoad()
{
    std::cout << "Deload Menu" << std::endl;
    _master->setVisible(false);
    _bouton->remove();
}