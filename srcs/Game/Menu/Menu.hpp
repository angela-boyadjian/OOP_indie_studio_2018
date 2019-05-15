//
// Created by dclement on 5/12/19.
//

#pragma once

#include "Display.hpp"
#include "ACharacter.hpp"
#include "IMenu.hpp"
#include "Events.hpp"

class Menu : public IMenu {
    public:
    Menu();
    ~Menu();

    void load(Display &) override;
    void handleButtons(Display &, const Events &events);

    enum {
        GUI_ID_QUIT_BUTTON = 101,
    };
};
