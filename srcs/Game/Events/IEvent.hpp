#pragma once

template <typename T, typename U>
class IEvent {
public:
    virtual bool    OnEvent(const T &) = 0;
    virtual bool    IsKeyDown(const U &) = 0;
};