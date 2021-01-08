#include "Target.hpp"

#include "parser/OBJParser.hpp"

namespace space::world {
    Target::Target(World& world) : Entity(world, nullptr) {
        _model = std::make_unique<Object>(parser::OBJParser::parse("./assets/target.txt"));
        update_hitbox();
    }
} // namespace space::world