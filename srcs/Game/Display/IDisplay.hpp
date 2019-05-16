/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** IDisplay
*/


#pragma once

class IDisplay {
public:
        using SceneManager = irr::scene::ISceneManager *;
        using VideoDriver = irr::video::IVideoDriver *;
        using Object = irr::scene::ISceneNode;
        using Map3D = std::vector<std::unique_ptr<IDisplay::Object>>;
    // NOTE MESH FUNCTIONS
    virtual void    addNewAnimation(const char *meshPath, const char *scenePath,
                                     irr::core::vector3df scale) = 0;
    // NOTE IS ON
    virtual bool    isRunning() const = 0;
    // NOTE GUI FUNCTIONS
    virtual void    setGuiMessage(const wchar_t *) = 0;
    // NOTE CAMERA FUNCTIONS
    virtual void    setCameraScene() = 0;
    //    // NOTE DRAW FUNCTIONS
    virtual void    draw() = 0;

    virtual Map3D   &getMap() = 0;

    // TEMPO
    SceneManager        _scenes;
    VideoDriver         _driver;
};