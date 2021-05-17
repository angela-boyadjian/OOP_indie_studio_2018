//
// Created by dclement on 6/15/19.
//

#include <BombermanPlayers/Player.hpp>
#include <BombermanPlayers/Bot.hpp>
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
    _event(event),
    _canPlay(false),
    _info({})
{
}

SceneInfo ChoosePlayerScene::runScene()
{
    if (!_is_load)
        throw SceneException("Scene is not load", _name.c_str());
    if (_buttons[1]->isPressed())
        return SceneInfo("menu");
    if (_buttons[0]->isPressed()) {
        auto info = createInfo("map_choose");
        if (_canPlay == true)
            return info;
    }
    return _info;
}

void ChoosePlayerScene::loadScene(SceneInfo &info)
{
    // std::cout << "load Choose player" << std::endl;
    loadImg();
    loadButton();
//    setBackground();
    _info = info;
    _is_load = true;
}

std::string ChoosePlayerScene::getName() { return _name; }

void ChoosePlayerScene::deLoad()
{
    // std::cout << "Deload Choose player" << std::endl;
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
    auto _camera = _manager->addCameraSceneNode(_master.get());
    _camera->setPosition(irr::core::vector3df(0, 0, -4));
    addPlayer("./resources/models/Character/PinkBombermanTextures.png", irr::core::vector3df(-2.2, -0.5, 0), irr::core::vector3df(0, 90, 0));
    addPlayer("./resources/models/Character/RedBombermanTextures.png", irr::core::vector3df(-0.8, -0.5, 0), irr::core::vector3df(0, 50, 0));
    addPlayer("./resources/models/Character/WhiteBombermanTextures.png", irr::core::vector3df(0.8, -0.5, 0), irr::core::vector3df(0, 0, 0));
    addPlayer("./resources/models/Character/BlackBombermanTextures.png", irr::core::vector3df(2.2, -0.5, 0), irr::core::vector3df(0, 180, 0));
}

void ChoosePlayerScene::loadButton()
{
    auto const &gui {_device->getGUIEnvironment()};

    _box.emplace_back(gui->addComboBox(irr::core::rect<irr::s32>(_win_size.Width / 2 - 420, 540, _win_size.Width / 2 - 230, 540 + 20), nullptr));
    _box.emplace_back(gui->addComboBox(irr::core::rect<irr::s32>(_win_size.Width / 2 - 210, 540, _win_size.Width / 2 - 10, 540 + 20), nullptr));
    _box.emplace_back(gui->addComboBox(irr::core::rect<irr::s32>(_win_size.Width / 2 + 10, 540, _win_size.Width / 2 + 210, 540 + 20), nullptr));
    _box.emplace_back(gui->addComboBox(irr::core::rect<irr::s32>(_win_size.Width / 2 + 230, 540, _win_size.Width / 2 + 420, 540 + 20), nullptr));
    for (auto &box : _box) {
        box->addItem(L"Bot");
        box->addItem(L"Player");
    }
    _buttons.emplace_back(gui->addButton(irr::core::rect<irr::s32>(_win_size.Width - 150, 740, _win_size.Width - 50, 740 + 20), nullptr, 102, L"Map select"));
    _buttons.emplace_back(gui->addButton(irr::core::rect<irr::s32>(50, 740, 150, 740 + 20), nullptr, 102, L"Go back"));
}

void ChoosePlayerScene::setBackground()
{
    // TODO C3PM change
    auto _terrain = std::unique_ptr<irr::scene::ITerrainSceneNode>(_device->getSceneManager()->addTerrainSceneNode(
            "./media/terrain-heightmap.bmp",
            nullptr, -1, irr::core::vector3df(0.f, 0.f, 0.f),
            irr::core::vector3df(0.f, 0.f, 0.f), irr::core::vector3df(40.f, 4.4f, 40.f),
            irr::video::SColor ( 255, 255, 255, 255 ), 5, irr::scene::ETPS_17, 4
    ));
    _terrain->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    // TODO C3PM change
    _terrain->setMaterialTexture(0, _device->getVideoDriver()->getTexture("./media/terrain-texture.jpg"));
    _terrain->setMaterialTexture(1, _device->getVideoDriver()->getTexture("./media/detailmap3.jpg"));
    _terrain->setMaterialType(irr::video::EMT_DETAIL_MAP);
    _terrain->scaleTexture(1.0f, 20.0f);
    auto _selector = std::unique_ptr<irr::scene::ITriangleSelector>
            (_device->getSceneManager()->createTerrainTriangleSelector(_terrain.get(), 0));
    _terrain->setTriangleSelector(_selector.get());
}

void ChoosePlayerScene::addPlayer(const std::string &rsc, irr::core::vector3df pos, irr::core::vector3df rotation)
{
    auto newScene = _manager->addAnimatedMeshSceneNode(_manager->getMesh("./resources/models/Character/Bomberman.MD3"), _master.get());
    newScene->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    newScene->setMD2Animation(irr::scene::EMAT_ATTACK);
//    newScene->setScale(irr::core::vector3df(6,6,6));
    irr::core::vector3df random = irr::core::vector3df(0, 1, 0);
    auto animation = _manager->createRotationAnimator(random);
    newScene->addAnimator(animation);
    newScene->setRotation(rotation);
    newScene->setPosition(pos);
    newScene->setAnimationSpeed(30);
    newScene->setLoopMode(true);
    newScene->setFrameLoop(27, 75);
    newScene->setMaterialTexture(0, _device->getVideoDriver()->getTexture(rsc.c_str()));//textures[static_cast<int>(color)].c_str()));
}

SceneInfo ChoosePlayerScene::createInfo(const std::string &scene)
{
    int id = 0;
    int color = 0;
    SceneInfo info = _info;

    for (auto box : _box) {
        // std::cout << "ID  " << box->getSelected() << std::endl;
        if (box->getSelected() == 1) {
            info._players.push_back(std::make_shared<Player>(
                Player(id, static_cast<ACharacter::Color>(color),
                    std::make_tuple(std::size_t(0), std::size_t(50000),
                        std::size_t(0)))));
       } else {
            info._bot.push_back(std::make_shared<Bot>(Bot(id, static_cast<ACharacter::Color>(color),
                std::make_tuple(std::size_t(0), std::size_t(0), std::size_t(0)))));
        }
        id++;
        color++;
    }
    if (info.load)
        info._dest = "game";
    else
        info._dest = scene;
    if (info._players.size() != 0)
        _canPlay = true;
    return info;
}