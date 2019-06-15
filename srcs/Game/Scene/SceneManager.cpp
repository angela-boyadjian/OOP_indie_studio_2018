/*
** EPITECH PROJECT, 2019
** SceneManager.cpp 
** File description:
** basile.lamarque@epitech.eu
*/

#include "SceneManagerException.hpp"
#include "SceneManager.hpp"

SceneManager::SceneManager() : _current(0, "None"), _info("None")
{}

void SceneManager::initManager(irr::scene::ISceneManager *scene_manageur)
{
    _manager = scene_manageur;
    _master = _manager->addEmptySceneNode();
    _gui = scene_manageur->getGUIEnvironment();
}

void SceneManager::addScenes(std::unique_ptr<IScene> new_scene)
{
    std::string name = new_scene->getName();
    for (auto &scene : _scenes)
        if (name == scene->getName())
            throw SceneManagerException("Name already exist", name.c_str());
    _scenes.push_back(std::move(new_scene));
}

std::tuple<long, std::string> SceneManager::getCurrent() const
{
    return _current;
}

void SceneManager::setCurrent(const unsigned long current)
{
    if (current >= _scenes.size())
        throw SceneManagerException("Id is to high","None");
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
    throw SceneManagerException("No scene name", name.c_str());
}

void SceneManager::changeCurrent(const unsigned long current)
{
    if (std::get<1>(_current) != "None")
        _scenes[std::get<0>(_current)]->deLoad();
    setCurrent(current);
    _scenes[std::get<0>(_current)]->loadScene(_info);
}

void SceneManager::changeCurrent(const std::string &name)
{
    if (std::get<1>(_current) != "None")
        _scenes[std::get<0>(_current)]->deLoad();
    setCurrent(name);
    _scenes[std::get<0>(_current)]->loadScene(_info);
}

void SceneManager::loadCurrent()
{
    _scenes[std::get<0>(_current)]->loadScene(_info);
}

void SceneManager::runCurrentScene()
{
    if (std::get<1>(_current) == "None")
        throw SceneManagerException("Current is not set","None");
    _info = _scenes[std::get<0>(_current)]->runScene();
    if (_info._dest != std::get<1>(_current))
        changeCurrent(_info._dest);
    _manager->drawAll();
    _manager->getGUIEnvironment()->drawAll();
}



irr::scene::ISceneManager *SceneManager::getManager()
{
    return _manager;
}

irr::scene::ISceneNode *SceneManager::getMaster()
{
    return _master;
}