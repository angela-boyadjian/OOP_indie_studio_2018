#pragma once

#include <irrlicht.h>
#include "driverChoice.h"
#include "Display.hpp"

class Events : public irr::IEventReceiver {
    public:
    Events(Display::Device device) : _device(device) {
        for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
            _keyIsPressed[i] = false;
    }

    bool    OnEvent(const irr::SEvent& event) final {
        if (event.EventType == irr::EET_KEY_INPUT_EVENT)
            _keyIsPressed[event.KeyInput.Key] = event.KeyInput.PressedDown;
        if (event.EventType == irr::EET_GUI_EVENT && event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED) {
            irr::s32 id = event.GUIEvent.Caller->getID();
            switch (id) {
            case GUI_ID_QUIT_BUTTON:
                _device->closeDevice();
                return true;
            }
        }
        return false;
    }

    bool    IsKeyDown(irr::EKEY_CODE keyCode) const { return _keyIsPressed[keyCode]; }

    enum {
        GUI_ID_QUIT_BUTTON = 101,
    };
private:
    bool    _keyIsPressed[irr::KEY_KEY_CODES_COUNT];
    Display::Device _device;
};