#include "Target.hpp"

#include "parser/OBJParser.hpp"

#include <math/utils.hpp>

namespace space::world {
    Target::Target(World& world) : Entity(world, nullptr) {
        _model = std::make_unique<Object>(parser::OBJParser::parse("./assets/target.txt"));
        _model->rotateX(math::toRadians(90));
        update_hitbox();
    }

    void Target::tick() {
        Entity::tick();

        if ((_scaling_up && _scale >= MAX_SCALE) || (!_scaling_up && _scale <= MIN_SCALE)) {
            _scaling_up = !_scaling_up;
        }

        float direction = (_scaling_up) ? 1 : -1;
        float scale_change = SCALE_ADJUSTMENT * direction;
        _scale += scale_change;

        _model->scale(1 + scale_change);
        update_hitbox();
    }
} // namespace space::world