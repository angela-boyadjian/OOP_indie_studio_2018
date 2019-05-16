//
// Created by dclement on 5/15/19.
//

#pragma once

#include "Display.hpp"
#include "Events.hpp"

class IMenu {
    public:
    virtual void load(Display &) = 0;
};
