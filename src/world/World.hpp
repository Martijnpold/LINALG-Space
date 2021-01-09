#pragma once

#include "entity/Entity.hpp"
#include "world/entity/Bullet.hpp"
#include "world/entity/SpaceShip.hpp"
#include "world/entity/Target.hpp"

#include <vector>

namespace space::world {

    class World {
    private:
        std::vector<std::unique_ptr<Entity>> _entities;
        std::vector<Bullet*> _bullets;
        std::vector<Target*> _targets;
        std::vector<Entity*> _toRemove;
        SpaceShip* _spaceShip;

    public:
        void tick();

        template<typename Entity, typename... Args> void add(Args&&... args) {
            _entities.emplace_back(std::make_unique<Entity>(*this, args...));
        }

        SpaceShip& addSpaceShip() {
            auto ship = std::make_unique<SpaceShip>(*this);
            auto& temp = *ship;
            _entities.emplace_back(std::move(ship));
            _spaceShip = &temp;
            return temp;
        }

        Bullet& addBullet(Vector location, Vector heading, Vector pitch, Vector yaw, float velocity) {
            auto bullet = std::make_unique<Bullet>(*this, location, heading, pitch, yaw, velocity);
            auto& temp = *bullet;
            _entities.emplace_back(std::move(bullet));
            _bullets.emplace_back(&temp);
            return temp;
        }

        Target& addTarget() {
            auto target = std::make_unique<Target>(*this);
            auto& temp = *target;
            _entities.emplace_back(std::move(target));
            _targets.emplace_back(&temp);
            return temp;
        }

        std::vector<std::unique_ptr<Entity>>& entities();

        SpaceShip* spaceship();

        std::vector<Bullet*> bullets();

        std::vector<Target*> targets();

        void remove(Entity& ent);
    };

} // namespace space::world
