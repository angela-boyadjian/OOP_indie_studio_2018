#pragma once

#include <irrlicht.h>
#include "driverChoice.h"

class Events : public irr::IEventReceiver {
public:
    Events() {
        for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
            _keyIsPressed[i] = false;
    }

    bool    OnEvent(const irr::SEvent& event) final {
        if (event.EventType == irr::EET_KEY_INPUT_EVENT)
            _keyIsPressed[event.KeyInput.Key] = event.KeyInput.PressedDown;
        return false;
    }
    bool    IsKeyDown(irr::EKEY_CODE keyCode) const { return _keyIsPressed[keyCode]; }

private:
    bool    _keyIsPressed[irr::KEY_KEY_CODES_COUNT];
};