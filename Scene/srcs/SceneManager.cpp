/*
** EPITECH PROJECT, 2019
** SceneManager.cpp 
** File description:
** basile.lamarque@epitech.eu
*/

#include "SceneManager.hpp"

SceneManager::SceneManager(irr::scene::ISceneManager *scene_manageur) :
_manager(scene_manageur),
_master(_manager->addEmptySceneNode()),
_current(0, "None")
{}

void SceneManager::addScenes(std::unique_ptr<IScene> new_scene)
{
    std::string name = new_scene->getName();
    for (auto &scene : _scenes)
        if (name == scene->getName())
            throw std::exception(); // NOTE A CHANGER
    _scenes.push_back(std::move(new_scene));
}

std::tuple<long, std::string> SceneManager::getCurrent() const
{
    return _current;
}

void SceneManager::setCurrent(const unsigned long current)
{
    if (current >= _scenes.size())
        throw std::exception();
    _current = std::make_tuple(current, _scenes[current]->getName());
}

void SceneManager::setCurrent(const std::string &name)
{
    long i = 0;

    for (auto &scene : _scenes) {
        if (scene->getName() == name) {
            _current = std::make_tuple(i, name);
            return;
        }
        i++;
    }
    throw std::exception(); // A CHANGER
}

void SceneManager::changeCurrent(const unsigned long current)
{
    _scenes[std::get<0>(_current)]->deLoad();
    setCurrent(current);
    _scenes[std::get<0>(_current)]->loadScene();
}

void SceneManager::changeCurrent(const std::string &name)
{
    _scenes[std::get<0>(_current)]->deLoad();
    setCurrent(name);
    _scenes[std::get<0>(_current)]->loadScene();
}

void SceneManager::loadCurrent()
{
    _scenes[std::get<0>(_current)]->loadScene();
}

void SceneManager::runCurrentScene()
{
    if (std::get<1>(_current) == "None")
        throw std::exception(); // A CHANGER
    _scenes[std::get<0>(_current)]->runScene();
    _manager->drawAll();
}



irr::scene::ISceneManager *SceneManager::getManager()
{
    return _manager;
}

irr::scene::ISceneNode *SceneManager::getMaster()
{
    return _master;
}