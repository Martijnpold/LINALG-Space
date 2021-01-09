#include "SpaceShip.hpp"

#include "../World.hpp"
#include "parser/OBJParser.hpp"

namespace space::world {
    SpaceShip::SpaceShip(World& world) : Entity(world, nullptr) {
        _model = std::make_unique<Object>(parser::OBJParser::parse("./assets/ship.txt"));
        update_hitbox();
    }

    void SpaceShip::shoot() {
        auto& bullet = _world.addBullet(_location, _heading, _pitch, _yaw, _velocity + 0.4);
    }
} // namespace space::world