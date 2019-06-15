//
// Created by dclement on 6/15/19.
//

#include "DisplayExceptions.hpp"
#include "SettingsScene.hpp"
#include "SceneException.hpp"

SettingsScene::SettingsScene(std::shared_ptr<IDisplay> display,
    irr::scene::ISceneNode *father, std::string const &name, std::shared_ptr<Events> event) :
    _master(display->getDevice()->getSceneManager()->addEmptySceneNode(father)),
    _manager(display->getDevice()->getSceneManager()),
    _name(name),
    _is_load(false),
    _win_size(display->getDevice()->getVideoDriver()->getScreenSize()),
    _device(display->getDevice()),
    _event(event)
{
}

SceneInfo SettingsScene::runScene()
{
    if (!_is_load)
        throw SceneException("Scene is not load", _name.c_str());
    return SceneInfo(_name);
}

void SettingsScene::loadScene(SceneInfo &info)
{
    std::cout << "load settings" << std::endl;
    _is_load = true;
}

std::string SettingsScene::getName() { return _name; }

void SettingsScene::deLoad()
{
    std::cout << "Deload settings" << std::endl;
    _master->setVisible(false);
    _is_load = false;
}
