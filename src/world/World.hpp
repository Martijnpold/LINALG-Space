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
        SpaceShip* _spaceShip;

    public:
        template<typename Entity, typename... Args> void add(Args&&... args) {
            _entities.emplace_back(std::make_unique<Entity>(*this, args...));
        }

        template<typename... Args> void addSpaceShip(Args&&... args) {
            auto ship = std::make_unique<SpaceShip>(*this, args...);
            _spaceShip = ship.get();
            _entities.emplace_back(std::move(ship));
        }

        template<typename... Args> void addBullet(Args&&... args) {
            auto bullet = std::make_unique<Bullet>(*this, args...);
            _bullets.emplace_back(bullet.get());
            _entities.emplace_back(std::move(bullet));
        }

        template<typename... Args> void addTarget(Args&&... args) {
            auto target = std::make_unique<Target>(*this, args...);
            _targets.emplace_back(target.get());
            _entities.emplace_back(std::move(target));
        }

        std::vector<std::unique_ptr<Entity>>& entities();

        SpaceShip* spaceship();

        std::vector<Bullet*> bullets();

        std::vector<Target*> targets();
    };

} // namespace space::world
