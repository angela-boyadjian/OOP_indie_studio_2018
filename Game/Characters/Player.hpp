#pagma once

#include "ACharacter.hpp"

class Player : public ACharacter {
public:
    Player(const MapPos &pos) : ACharacter(pos) {};
    ~Player() = default;
};