/*
** EPITECH PROJECT, 2019
** GameScene.cpp 
** File description:
** basile.lamarque@epitech.eu
*/

#include "SceneException.hpp"
#include "GameScene.hpp"

GameScene::GameScene(irr::scene::ISceneManager *manager, irr::scene::ISceneNode *father, const std::string &name) :
    _master(manager->addEmptySceneNode(father)),
    _manager(manager),
    _name(name),
    _is_load(false)
{
    _master->setVisible(false);
}

std::string GameScene::runScene()
{
    if (!_is_load)
        throw SceneException("Scene is not load", _name.c_str());
    _master->setVisible(true);
    return _name;
}

void GameScene::loadScene()
{
    std::cout << "load Game" << std::endl;
    _is_load = true;
    _cubes.emplace_back(_manager->addCubeSceneNode(10.0f, _master.get(), -1, irr::core::vector3df(-10.0f, 0.0f, 20.0f)));
    _cubes.back()->setMaterialFlag(irr::video::EMF_WIREFRAME, true);
     _cubes.emplace_back(_manager->addCubeSceneNode(10.0f, _master.get(), -1, irr::core::vector3df(10.0f, 0.0f, 20.0f)));
    _cubes.back()->setMaterialFlag(irr::video::EMF_WIREFRAME, true);
    _master->setVisible(true);
}

std::string GameScene::getName()
{
    return _name;
}

void GameScene::deLoad()
{
    std::cout << "DeloadGame" << std::endl;
    _master->setVisible(false);
}