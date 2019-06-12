#include "Events.hpp"

Events::Events(Device const &device, std::shared_ptr<IDisplay> &display)
{
    _device = device;
    _display = display;
    for (index i = 0; i < KEY_COUNT; ++i)
        _keyIsPressed[i] = false;
}

bool    Events::isInputEvent(Event const &event) { return event.EventType == INPUT_EVENT; }
bool    Events::isGuiEvent(Event const &event) { return event.EventType == GUI_EVENT; }

void    Events::OnEvent(const irr::EKEY_CODE &key) {
    _keyIsPressed[key] = true;
}

bool    Events::OnEvent(const Event& event)
{
    if (isInputEvent(event)) {
//            std::cout << "pass" << std::endl;
        _keyIsPressed[event.KeyInput.Key] = event.KeyInput.PressedDown;
    }
    if (isGuiEvent(event)) {
        index id = event.GUIEvent.Caller->getID();
        if (id == GUI_ID_QUIT_BUTTON &&
            event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED) {
            _device->closeDevice();
            return true;
        } else if (id == GUI_ID_START_BUTTON &&
                   event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED) {
            _display->changeScene("game");
            return true;
        }
    }
    return false;
}

bool    Events::IsKeyDown(const irr::EKEY_CODE &keyCode) const { return _keyIsPressed[keyCode]; }