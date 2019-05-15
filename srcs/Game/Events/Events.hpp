#pragma once

#include <irrlicht.h>
#include <driverChoice.h>

static const size_t KEY_COUNT = irr::KEY_KEY_CODES_COUNT;

template <typename T>
class Events : public T {
public:
    Events() {
        for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
            _keyIsPressed[i] = false;
    }

    template <typename U> // U ->irr::SEvent
    bool    OnEvent(const U& event) {
        if (event.EventType == irr::EET_KEY_INPUT_EVENT)
            _keyIsPressed[event.KeyInput.Key] = event.KeyInput.PressedDown;
        return false;
    }

    template <typename V> // V -> irr::EKEY_CODE
    bool    IsKeyDown(const V &keyCode) const { return _keyIsPressed[keyCode]; }

private:
    bool    _keyIsPressed[KEY_COUNT];
};