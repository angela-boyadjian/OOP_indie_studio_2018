/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** IntroScene
*/

#include "IntroScene.hpp"
#include "SceneException.hpp"

IntroScene::IntroScene(std::shared_ptr<IDisplay> display, irr::scene::ISceneNode *father,
    std::string const &name, std::shared_ptr<Events> event) :
    _master(display->getDevice()->getSceneManager()->addEmptySceneNode(father)),
    _manager(display->getDevice()->getSceneManager()),
    _name(name),
    _is_load(false),
    _win_size(display->getDevice()->getVideoDriver()->getScreenSize()),
    _device(display->getDevice()),
    _event(event)
{
    _master->setVisible(false);
}

void IntroScene::updateImg()
{
    auto update {false};

    if (!_isVisible)
        update = true;
    _images[1]->setVisible(update);
    _clock = std::chrono::steady_clock::now();
    _isVisible = update;
}

SceneInfo IntroScene::runScene()
{
    if (!_is_load)
        throw SceneException("Scene is not load", _name.c_str()); // A CHANGER
    if (_event->IsKeyDown(irr::KEY_SPACE))
        return SceneInfo("menu");
    if (getElapsedTime() >= 0.8)
        updateImg();
    return SceneInfo(_name);
}

void IntroScene::loadImg() noexcept
{
    auto const &gui {_device->getGUIEnvironment()};
    for (auto i{0}; i < 2; ++i)
        _images[i] = gui->addImage(irr::core::rect<irr::s32>(0, 0,
                                                             _win_size.Width, _win_size.Height));
    _textures[0] = _device->getVideoDriver()->getTexture("/resources/ui/MainMenuBackground.jpg");
    _textures[1] = _device->getVideoDriver()->getTexture("./resources/ui/press_start.png");
    _images[0]->setImage(_textures[0]);
    _images[0]->setScaleImage(true);
    _images[1]->setImage(_textures[1]);
    _images[1]->setRelativePosition(irr::core::position2di(420, 470));
    _images[1]->setVisible(false);
    _isVisible = false;
//    _manager->addSkyDomeSceneNode
//            (_manager->getVideoDriver()->getTexture("./../lib/irrLicht/media/skydome.jpg"),16,8,0.95f,2.0f);
    _manager->getVideoDriver()->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, true);
}

std::size_t IntroScene::getElapsedTime() const
{
    auto end {std::chrono::steady_clock::now()};

    return std::chrono::duration_cast<std::chrono::seconds>(end - _clock).count();
}

void IntroScene::loadScene(SceneInfo &info)
{
    std::cout << "Load intro" << std::endl;
    _is_load = true;
    _cubes.emplace_back(_manager->addCubeSceneNode(10.0f, _master.get(), -1,
        irr::core::vector3df(0.0f, 0.0f, 20.0f)));
    _cubes.back()->setMaterialFlag(irr::video::EMF_WIREFRAME, true);
    loadImg();
    _clock = std::chrono::steady_clock::now();
    _master->setVisible(true);
}

std::string IntroScene::getName() { return _name; }

void IntroScene::deLoad()
{
    std::cout << "Deload Intro" << std::endl;
    _images[0]->setVisible(false);
    _images[1]->setVisible(false);
    _master->setVisible(false);
}