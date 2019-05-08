#pagma once

#include "ACharacter.hpp"

class Bot : public ACharacter {
public:
    Bot(const MapPos &pos) : ACharacter(pos) {};
    ~Bot() = default;
};