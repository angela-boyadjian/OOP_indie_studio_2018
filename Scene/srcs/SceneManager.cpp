/*
** EPITECH PROJECT, 2019
** SceneManager.cpp 
** File description:
** basile.lamarque@epitech.eu
*/

#include "SceneManager.hpp"

ScenSceneManager::SceneManager(std::shared_ptr<irr::scene::ISceneManager> scene_manageur) : _master(scene_manageur)
{}

void SceneManager::addScenes(std::unique_ptr<IScene> scene)
{
    _scenes.push_back(std::move(scene));
}

std::tuple<long, std::string> SceneManager::getCurrent() const
{
    return _current;
}

void SceneManager::setCurrent(const std::string &name)
{
    long i = 0;

    for (auto &scene : _scenes) {
        if (scene->getName() == name) {
            _current = std::make_tuple(name, i);
            return;
        }
        i++;
    }
    throw std::exception(); // A CHANGER
}

void SceneManager::setCurrent(const long current)
{
    if (current >= _scenes.size())
        throw std::exception();
    _current = std::make_tuple(_scenes[current], current);
}

std::shared_ptr<irr::scene::ISceneManager> &SceneManager::getMaster()
{
    return _master;
}