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
    _display(display)
{}

void MapChangeScene::deLoad()
{
    std::cout << "Deload map change" << std::endl;
    _master->setVisible(false);
    for (auto &bouton : _buttons)
        bouton->remove();
    _buttons.clear();
    _is_load = false;
}

std::string MapChangeScene::runScene()
{
    if (!_is_load)
        throw SceneException("Scene is not load", _name.c_str());
    if (_buttons.back()->isPressed())
        return "game";
    if (_buttons[0]->isPressed())
        return "menu";
    return _name;
}

void MapChangeScene::loadScene()
{
    auto _dispLoader = std::make_unique<IrrlichtDisplayLoader>(_display, _master, _manager);
    std::cout << "mapchange load" << std::endl;
    auto camera = _manager->addCameraSceneNode(_master.get());
    camera->setTarget(irr::core::vector3df(0, -15, 25));
    camera->setPosition(irr::core::vector3df(0, 60, -20));
    _is_load = true;
     _map->generate3dMap(-1, 80, -1);
    _dispLoader->loadMap(_map->getMapData());
    auto rec = irr::core::rect<irr::s32>(_win_size.Width / 10, _win_size.Height - (_win_size.Height / 5), _win_size.Width / 10 + 300, _win_size.Height - (_win_size.Height / 5) + 42);
    _buttons.emplace_back(_manager->getGUIEnvironment()->addButton(rec, nullptr, 102, L"Back !!"));
    rec = irr::core::rect<irr::s32>(_win_size.Width -  (_win_size.Width / 3), _win_size.Height - (_win_size.Height / 5), _win_size.Width - (_win_size.Width / 3) + 300, _win_size.Height - (_win_size.Height / 5) + 42);
    _buttons.emplace_back(_manager->getGUIEnvironment()->addButton(rec, nullptr, 102, L"GOOOO !!"));
}

std::string MapChangeScene::getName()
{
    return _name;
}