#include "Events.hpp"

Events::Events(Device const &device, std::shared_ptr<IDisplay> &display)
{
    _device = device;
    _display = display;
    for (index i = 0; i < KEY_COUNT; ++i)
        _keyIsPressed[i] = false;
}

bool    Events::isInputEvent(Event const &event) { return event.EventType == INPUT_EVENT; }

bool    Events::isGuiEvent(Event const &event) { return event.EventType == GUI_EVENT;}

void    Events::OnEvent(const irr::EKEY_CODE &key) {
    _keyIsPressed[key] = true;
}

bool    Events::OnEvent(const Event& event)
{
    if (isInputEvent(event) && isGuiEvent(event))
        std::cout << "IDD " << event.GUIEvent.Caller->getID() << std::endl;
    if (isInputEvent(event)) {
        _keyIsPressed[event.KeyInput.Key] = event.KeyInput.PressedDown;
        if (event.KeyInput.Key == irr::KEY_ESCAPE) {
            _display->changeScene("menu");
            return true;
        }
    }
    return false;
}

bool    Events::IsKeyDown(const irr::EKEY_CODE &keyCode) const { return _keyIsPressed[keyCode]; }