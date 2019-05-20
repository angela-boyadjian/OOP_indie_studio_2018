//
// Created by dclement on 5/12/19.
//

#pragma once

#include "IrrlichtDisplay.hpp"
#include "ACharacter.hpp"
#include "IMenu.hpp"
#include "Events.hpp"

class Menu : public IMenu {
    public:
    Menu();
    ~Menu();


    void load(IrrlichtDisplay &) override;
};
