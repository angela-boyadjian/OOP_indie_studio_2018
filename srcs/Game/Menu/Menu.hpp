//
// Created by dclement on 5/12/19.
//

#pragma once

#include "Display.hpp"
#include "ACharacter.hpp"

class Menu {
    public:
    Menu(Display &display);

    ~Menu();

    void loadMenu();

    void displayMenu();

    enum class Event{
        GUI_ID_QUIT_BUTTON = 101,
    };

    private:
        Display _display;
};
