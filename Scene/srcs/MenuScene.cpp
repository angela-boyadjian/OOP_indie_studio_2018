/*
** EPITECH PROJECT, 2019
** MenuScene.cpp 
** File description:
** basile.lamarque@epitech.eu
*/

#include "MenuScene.hpp"

MenuScene::MenuScene(irr::scene::ISceneManager *manager, irr::scene::ISceneNode *father, const std::string &name) :
    _master(manager->addEmptySceneNode(father)),
    _manager(manager),
    _name(name),
    _is_load(false)
{
    _master->setVisible(false);
}

void MenuScene::runScene()
{
    if (!_is_load)
        throw std::exception(); // A CHANGER
    std::cout << "Run Menu" << std::endl;
    _master->setVisible(true);
}

void MenuScene::loadScene()
{
    std::cout << "Load menu" << std::endl;
    _is_load = true;
    _cubes.emplace_back(_manager->addCubeSceneNode(10.0f, _master.get(), -1, irr::core::vector3df(0.0f, 0.0f, 20.0f)));
    _cubes.back()->setMaterialFlag(irr::video::EMF_WIREFRAME, true);
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
}