#pragma once

#include <memory>
#include <irrlicht.h>

#include <driverChoice.h>
#include "IDisplay.hpp"

static const size_t KEY_COUNT = irr::KEY_KEY_CODES_COUNT;
static const size_t INPUT_EVENT = irr::EET_KEY_INPUT_EVENT;
static const size_t GUI_EVENT = irr::EET_GUI_EVENT;

class IDisplay;

class Events : public irr::IEventReceiver {
public:
    using Device = std::shared_ptr<irr::IrrlichtDevice>;
    using index = irr::u32;
    using Event = irr::SEvent;

    Events(Device const &device, std::shared_ptr<IDisplay> &);
    bool    isInputEvent(Event const &);
    bool    isGuiEvent(Event const &);
    void    OnEvent(const irr::EKEY_CODE &);
    bool    OnEvent(const Event &) final;

    bool    IsKeyDown(const irr::EKEY_CODE &keyCode) const;

    enum {
        GUI_ID_QUIT_BUTTON = 101,
        GUI_ID_START_BUTTON,
    };
private:
    bool    _keyIsPressed[KEY_COUNT];
    Device  _device;
    std::shared_ptr<IDisplay> _display;
};