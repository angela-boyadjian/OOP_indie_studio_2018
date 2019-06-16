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
    _info({})
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

SceneInfo MapChangeScene::runScene()
{
    if (!_is_load)
        throw SceneException("Scene is not load", _name.c_str());
    if (_buttons.back()->isPressed()) {
//        auto ret = SceneInfo("game");
        _info._dest = "game";
        _info._map = std::move(_map);
//        ret._map = std::move(_map);
        return _info;
    }
    if (_buttons[0]->isPressed())
        return SceneInfo("menu");
    return _info;
}

void MapChangeScene::loadScene(SceneInfo &info)
{
    auto _dispLoader = std::make_unique<IrrlichtDisplayLoader>(_display, _master, _manager);
    std::cout << "mapchange load" << std::endl;

    _info = info;
    _camera = _manager->addCameraSceneNode(_master.get());
    _camera->setTarget(irr::core::vector3df(0, -15, 25));
    _camera->setPosition(irr::core::vector3df(0, 120, -20));
/*    camera->bindTargetAndRotation(true);
    camera->setRotation(irr::core::vector3df(0, 90, 0));
    auto animation = _manager->createRotationAnimator(irr::core::vector3df(1, 0, 0));
    camera->addAnimator(animation);*/
    _is_load = true;

     _map->generate3dMap(-1, 80, -1);
    _dispLoader->loadMap(_map->getMapData());
    auto rec = irr::core::rect<irr::s32>(_win_size.Width / 10, _win_size.Height - (_win_size.Height / 5), _win_size.Width / 10 + 300, _win_size.Height - (_win_size.Height / 5) + 42);
    _buttons.emplace_back(_manager->getGUIEnvironment()->addButton(rec, nullptr, 102, L"Back !!"));
    rec = irr::core::rect<irr::s32>(_win_size.Width -  (_win_size.Width / 3), _win_size.Height - (_win_size.Height / 5), _win_size.Width - (_win_size.Width / 3) + 300, _win_size.Height - (_win_size.Height / 5) + 42);
    _buttons.emplace_back(_manager->getGUIEnvironment()->addButton(rec, nullptr, 102, L"GOOOO !!"));
    _manager->addSkyDomeSceneNode
            (_manager->getVideoDriver()->getTexture("./../lib/irrLicht/media/skydome2.jpg"),16,8,0.95f,2.0f);
    _manager->getVideoDriver()->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, true);
}

std::string MapChangeScene::getName()
{
    return _name;
}