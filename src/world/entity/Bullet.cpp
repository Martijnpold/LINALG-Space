#include "Bullet.hpp"

#include "parser/OBJParser.hpp"

namespace space::world {
    Bullet::Bullet(World& world, Vector location, Vector heading, Vector pitch, Vector yaw, float velocity)
        : Entity(world, nullptr, location, heading, pitch, yaw) {
        _model = std::make_unique<Object>(parser::OBJParser::parse("./assets/bullet.txt"));
        _model->scale(0.5f);
        _velocity = velocity;
        update_hitbox();
    }
} // namespace space::world