//
// Created by dclement on 5/15/19.
//

#pragma once

#include "IrrlichtDisplay.hpp"
#include "Events.hpp"

class IMenu {
    public:
    virtual void load(IrrlichtDisplay &) = 0;
};
