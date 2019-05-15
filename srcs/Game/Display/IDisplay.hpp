/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** IDisplay
*/


#pragma once

class IDisplay {
public:
    // NOTE MESH FUNCTIONS
    // void    addNewAnimation(const char *, const char *, irr::core::vector3df);

    // NOTE IS ON
    virtual bool    isRunning() const = 0;
    // NOTE GUI FUNCTIONS
    virtual void    setGuiMessage(const wchar_t *) = 0;
    // NOTE CAMERA FUNCTIONS
    virtual void    setCameraScene() = 0;
    //    // NOTE DRAW FUNCTIONS
    virtual void    draw() = 0;
};