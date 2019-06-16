/*
** EPITECH PROJECT, 2019
** MapChangeScene.cpp 
** File description:
** basile.lamarque@epitech.eu
*/

#include <IDisplayLoader.hpp>
#include <IrrlichtDisplay/IrrlichtDisplayLoader.hpp>
#include <Map.hpp>
#include "MapChangeScene.hpp"
#include "SceneException.hpp"

MapChangeScene::MapChangeScene(std::shared_ptr<IDisplay> display, irr::scene::ISceneNode *father, std::string const &name) :
    _master(display->getDevice()->getSceneManager()->addEmptySceneNode(father)),
    _manager(display->getDevice()->getSceneManager()),
    _name(name),
    _is_load(false),
    _win_size(display->getDevice()->getVideoDriver()->getScreenSize()),
    _device(display->getDevice()),
    _map(new Map()),
    _display(display),
    _info({}),
    _dispLoader(new IrrlichtDisplayLoader(_display, _master, _manager))
{}

void MapChangeScene::deLoad()
{
    std::cout << "Deload map change" << std::endl;
    _master->setVisible(false);
    for (auto &bouton : _buttons)
        bouton->remove();
  /*  for (auto &tile : _display->getColiMap())
        tile->remove();
    for (auto &tile : _display->getNonColiMap())
        tile->remove();*/

    _display->getColiMap() = std::vector<std::unique_ptr<IDisplay::Object>>();
    _display->getNonColiMap() = std::vector<std::unique_ptr<IDisplay::Object>>();
   /* _display->getNonColiMap() = std::vector<std::unique_ptr<IDisplay::Object>>();
    _display->getColiMap() = std::vector<std::unique_ptr<IDisplay::Object>>();
    std::cout << "coucou" << std::endl;*/
    _buttons.clear();
    _is_load = false;
}

void MapChangeScene::reloadMap()
{
    auto i = _display->getColiMap().size() - 1;

    while (i > 0) {
        _display->getColiMap()[i]->getParent()->removeChild(_display->getColiMap()[i].get());
        _display->getColiMap()[i].release();
        _display->getColiMap().erase( _display->getColiMap().begin() + i);
        i--;
    }
    i = _display->getNonColiMap().size() - 1;
    while (i > 0) {
        _display->getNonColiMap()[i]->getParent()->removeChild(_display->getNonColiMap()[i].get());
        _display->getNonColiMap()[i].release();
        _display->getNonColiMap().erase( _display->getNonColiMap().begin() + i);
        i--;
    }
    _map->generate3dMap(-1, 80, -1);
    _dispLoader->loadMap(_map->getMapData());
}

SceneInfo MapChangeScene::runScene()
{
    if (!_is_load)
        throw SceneException("Scene is not load", _name.c_str());
    if (_buttons[static_cast<int>(BUTTON::GO)]->isPressed()) {
        _info._dest = "game";
        _info._map = std::move(_map);
        return _info;
    }
    if (_buttons[static_cast<int>(BUTTON::BACK)]->isPressed())
        return _info._dest = "player_choose";
    if (_buttons[static_cast<int>(BUTTON::RELOAD)]->isPressed())
        reloadMap();
    return _info;
}

void MapChangeScene::loadButton()
{
    auto rec = irr::core::rect<irr::s32>(_win_size.Width / 10, _win_size.Height - (_win_size.Height / 5), _win_size.Width / 10 + 300, _win_size.Height - (_win_size.Height / 5) + 42);
    _buttons.emplace_back(_manager->getGUIEnvironment()->addButton(rec, nullptr, -1, L"Back !!"));
    rec = irr::core::rect<irr::s32>(_win_size.Width -  (_win_size.Width / 3), _win_size.Height - (_win_size.Height / 5), _win_size.Width - (_win_size.Width / 3) + 300, _win_size.Height - (_win_size.Height / 5) + 42);
    _buttons.emplace_back(_manager->getGUIEnvironment()->addButton(rec, nullptr, -1, L"GOOOO !!"));
    rec = irr::core::rect<irr::s32>(_win_size.Width / 2 - 300, _win_size.Height / 10, _win_size.Width / 2 + 300, _win_size.Height / 10 + 42);
    _buttons.emplace_back(_manager->getGUIEnvironment()->addButton(rec, nullptr, -1, L"reload !!"));

}

void MapChangeScene::loadScene(SceneInfo &info)
{
    std::cout << "mapchange load" << std::endl;
    _info = info;
    _info._dest = _name;
    _master->setVisible(true);
    _camera = _manager->addCameraSceneNode(_master.get());
    _camera->setTarget(irr::core::vector3df(0, -15, 25));
    _camera->setPosition(irr::core::vector3df(0, 120, -20));
    loadButton();
/*    camera->bindTargetAndRotation(true);
    camera->setRotation(irr::core::vector3df(0, 90, 0));
    auto animation = _manager->createRotationAnimator(irr::core::vector3df(1, 0, 0));
    camera->addAnimator(animation);*/
    _is_load = true;
     _map->generate3dMap(-1, 80, -1);
    _dispLoader->loadMap(_map->getMapData());
    std::cout << "toto " << _display->getColiMap().size() << std::endl;

}

std::string MapChangeScene::getName()
{
    return _name;
}