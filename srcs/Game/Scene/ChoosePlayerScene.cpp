//
// Created by dclement on 6/15/19.
//

#include "ChoosePlayerScene.hpp"
#include "SceneException.hpp"

ChoosePlayerScene::ChoosePlayerScene(std::shared_ptr<IDisplay> display,
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

std::string ChoosePlayerScene::runScene()
{
    if (!_is_load)
        throw SceneException("Scene is not load", _name.c_str());
    if (_buttons[1]->isPressed())
        return "menu";
    if (_buttons[0]->isPressed())
        return "map_choose";
    return _name;
}

void ChoosePlayerScene::loadScene()
{
    std::cout << "load Choose player" << std::endl;
    loadImg();
    loadButton();
    _is_load = true;
}

std::string ChoosePlayerScene::getName() { return _name; }

void ChoosePlayerScene::deLoad()
{
    std::cout << "Deload Choose player" << std::endl;
        _master->setVisible(false);
    for (auto &button : _buttons)
        button->remove();
    for (auto &box : _box)
        box->remove();
    _buttons.clear();
    _box.clear();
    _is_load = false;
}

void ChoosePlayerScene::loadImg() noexcept
{
 //auto const &gui {_device->getGUIEnvironment()};
//    auto texture = _device->getVideoDriver()->getTexture("./../resources/ui/PinkBombermanIcon.png");
//    _images[0] = gui->addImage(irr::core::rect<irr::s32>(10, 10, 40, 40));
//    _images[0]->setImage(texture);
//    _images[0]->setScaleImage(true);
}

void ChoosePlayerScene::loadButton()
{
    auto const &gui {_device->getGUIEnvironment()};

    _box.emplace_back(gui->addComboBox(irr::core::rect<irr::s32>(_win_size.Width / 2 - 420, 540, _win_size.Width / 2 - 230, 540 + 20), nullptr, 102));
    _box.emplace_back(gui->addComboBox(irr::core::rect<irr::s32>(_win_size.Width / 2 - 210, 540, _win_size.Width / 2 - 10, 540 + 20), nullptr, 102));
    _box.emplace_back(gui->addComboBox(irr::core::rect<irr::s32>(_win_size.Width / 2 + 10, 540, _win_size.Width / 2 + 210, 540 + 20), nullptr, 102));
    _box.emplace_back(gui->addComboBox(irr::core::rect<irr::s32>(_win_size.Width / 2 + 230, 540, _win_size.Width / 2 + 420, 540 + 20), nullptr, 102));
    for (auto &box : _box) {
        box->addItem(L"Bot");
        box->addItem(L"Player");
    }
    _buttons.emplace_back(gui->addButton(irr::core::rect<irr::s32>(_win_size.Width - 150, 740, _win_size.Width - 50, 740 + 20), nullptr, 102, L"Map select"));
    _buttons.emplace_back(gui->addButton(irr::core::rect<irr::s32>(50, 740, 150, 740 + 20), nullptr, 102, L"Go back"));
}
