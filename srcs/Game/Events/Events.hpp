#pragma once

#include <irrlicht.h>

#include <driverChoice.h>

static const size_t KEY_COUNT = irr::KEY_KEY_CODES_COUNT;
static const size_t INPUT_EVENT = irr::EET_KEY_INPUT_EVENT;
static const size_t GUI_EVENT = irr::EET_GUI_EVENT;

template <typename T>
class Events : public T {
public:
    using index = irr::u32;
    Events() {
        for (index i = 0; i < KEY_COUNT; ++i)
            _keyIsPressed[i] = false;
    }

    template <typename U> // U ->irr::SEvent::EventType
    bool    isInputEvent(const U &eventType) { return eventType == INPUT_EVENT; }

    template <typename U>
    bool    isGuiEvent(const U &eventType) { return eventType == GUI_EVENT; }

    template <typename U> // U -> irr::SEvent::KeyInput::Key
    void    OnEvent(const U& key) {
        _keyIsPressed[key] = true;
    }

    template <typename V> // V -> irr::EKEY_CODE
    bool    IsKeyDown(const V &keyCode) const { return _keyIsPressed[keyCode]; }

private:
    bool    _keyIsPressed[KEY_COUNT];
};