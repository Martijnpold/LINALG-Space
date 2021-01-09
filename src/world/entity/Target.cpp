#include "Target.hpp"

#include "parser/OBJParser.hpp"

#include <math/utils.hpp>

namespace space::world {
    Target::Target(World& world) : Entity(world, nullptr) {
        _model = std::make_unique<Object>(parser::OBJParser::parse("./assets/target.txt"));
        _model->rotateX(math::toRadians(90));
        update_hitbox();
    }
} // namespace space::world