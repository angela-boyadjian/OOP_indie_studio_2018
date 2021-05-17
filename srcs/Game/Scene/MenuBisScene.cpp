/*
** EPITECH PROJECT, 2019
** MenuScene.cpp 
** File description:
** basile.lamarque@epitech.eu
*/

#include "SceneException.hpp"
#include "MenuBisScene.hpp"

MenuBisScene::MenuBisScene(std::shared_ptr<IDisplay> display, irr::scene::ISceneNode *father,
    std::string const &name) :
    _master(display->getDevice()->getSceneManager()->addEmptySceneNode(father)),
    _manager(display->getDevice()->getSceneManager()),
    _name(name),
    _is_load(false),
    _win_size(display->getDevice()->getVideoDriver()->getScreenSize()),
    _device(display->getDevice())
{
}

SceneInfo MenuBisScene::runScene()
{
    SceneInfo info("player_choose");

    info.load = false;
    if (!_is_load)
        throw SceneException("Scene is not load", _name.c_str()); // A CHANGER
    if (_buttons[0]->isPressed())
        return info;
    if (_buttons[1]->isPressed())
        return SceneInfo("settings");
    if (_buttons[2]->isPressed())
        _device->closeDevice();
    return SceneInfo(_name);
}

void MenuBisScene::loadButtons()
{
    _buttons.emplace_back(_manager->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(_win_size.Width / 2 - 300, 440,
                                                                                             _win_size.Width / 2 + 300, 440 + 42), nullptr, 102, L"Start Game"));
    _buttons.emplace_back(_manager->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(_win_size.Width / 2 - 300, 440 + 42 + 10,
                                                                                             _win_size.Width / 2 + 300, 440 + 42 + 10 + 42), nullptr, 103, L"Continue"));
    _buttons.emplace_back(_manager->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(_win_size.Width / 2 - 300, 440 + 84 + 20,
                                                                                             _win_size.Width / 2 + 300, 440 + 84 + 20 + 42), nullptr, 101, L"Exit"));
}

void MenuBisScene::loadScene(SceneInfo &info)
{
    std::cout << "Load menu" << std::endl;
    _is_load = true;
    auto const &gui {_device->getGUIEnvironment()};
    _background = gui->addImage(irr::core::rect<irr::s32>(0, 0,
                                                          _win_size.Width, _win_size.Height));
    _texture = _device->getVideoDriver()->getTexture("./resources/ui/bombermanBackground.jpg");
    _background->setImage(_texture);
    _background->setScaleImage(true);
    _background->setVisible(true);
    _cubes.emplace_back(_manager->addCubeSceneNode(10.0f, _master.get(), -1, irr::core::vector3df(0.0f, 0.0f, 20.0f)));
    _cubes.back()->setMaterialFlag(irr::video::EMF_WIREFRAME, true);
    loadButtons();
    _manager->addSkyDomeSceneNode
            (_manager->getVideoDriver()->getTexture("./media/skydome.jpg"),16,8,0.95f,2.0f);
    _manager->getVideoDriver()->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, true);
}

std::string MenuBisScene::getName() { return _name; }

void MenuBisScene::deLoad()
{
    std::cout << "Deload Menu" << std::endl;
    _master->setVisible(false);
    for (auto &button : _buttons)
        button->remove();
    _buttons.clear();
    _background->remove();
    _is_load = false;
}