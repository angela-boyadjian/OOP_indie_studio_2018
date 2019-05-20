#pragma once

#include <memory>
#include <irrlicht.h>

#include <driverChoice.h>

static const size_t KEY_COUNT = irr::KEY_KEY_CODES_COUNT;
static const size_t INPUT_EVENT = irr::EET_KEY_INPUT_EVENT;
static const size_t GUI_EVENT = irr::EET_GUI_EVENT;

class Events : public irr::IEventReceiver {
public:
    using Device = std::shared_ptr<irr::IrrlichtDevice>;
    using index = irr::u32;
    using Event = irr::SEvent;

    Events(Device const &device) {
        _device = device;
        for (index i = 0; i < KEY_COUNT; ++i)
            _keyIsPressed[i] = false;
    }

    bool    isInputEvent(Event const &event) { return event.EventType == INPUT_EVENT; }

    bool    isGuiEvent(Event const &event) { return event.EventType == GUI_EVENT; }

    void    OnEvent(const irr::EKEY_CODE &key) {
        _keyIsPressed[key] = true;
    }

    bool    OnEvent(const Event& event)
    {
        if (isInputEvent(event))
            _keyIsPressed[event.KeyInput.Key] = event.KeyInput.PressedDown;
        if(isGuiEvent(event)) {
            index id = event.GUIEvent.Caller->getID();
            if (id == GUI_ID_QUIT_BUTTON && event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED) {
                _device->closeDevice();
                return true;
            }
        }
        return false;
    }

    bool    IsKeyDown(const irr::EKEY_CODE &keyCode) const { return _keyIsPressed[keyCode]; }

    enum {
        GUI_ID_QUIT_BUTTON = 101,
    };
private:
    bool    _keyIsPressed[KEY_COUNT];
    Device  _device;
};