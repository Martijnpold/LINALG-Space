#include "Bullet.hpp"

#include "../World.hpp"
#include "parser/OBJParser.hpp"

namespace space::world {
    Bullet::Bullet(World& world, Vector location, Vector heading, Vector pitch, Vector yaw, float velocity)
        : Entity(world, nullptr, location, heading, pitch, yaw) {
        _model = std::make_unique<Object>(parser::OBJParser::parse("./assets/bullet.txt"));
        _model->scale(0.5f);
        _velocity = velocity;
        update_hitbox();
    }

    void Bullet::tick() {
        Entity::tick();

        for (Target* target : _world.targets()) {
            if (target->collides_with(*this)) {
                _world.remove(*target);
                _world.remove(*this);
                return;
            }
        }

        _ticksRemaining--;
        if (_ticksRemaining <= 0) {
            _world.remove(*this);
        }
    }
} // namespace space::world