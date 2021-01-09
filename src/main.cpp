#define SDL_main main

#include "math/Matrix.hpp"
#include "math/utils.hpp"
#include "parser/OBJParser.hpp"
#include "sdl/SDLWrapper.hpp"
#include "world/AABB.hpp"
#include "world/Object.hpp"
#include "world/Renderer.hpp"
#include "world/entity/Entity.hpp"
#include "world/entity/SpaceShip.hpp"

#include <ctime>
#include <iostream>
#include <memory>

using namespace space::world;
using namespace space::sdl;

int main(int argc, char* argv[]) {
    //    auto o = std::make_unique<Object>();
    //    o->add(Polygon {{
    //            Vector {0, 0, 0},
    //            Vector {6, 0, 0},
    //            Vector {6, 1, 0},
    //            Vector {1, 1, 0},
    //            Vector {1, 3, 0},
    //            Vector {0, 3, 0},
    //    }});
    //    o->add(Polygon {{
    //            Vector {6, 0, 0},
    //            Vector {6, 0, 4},
    //            Vector {6, 3, 4},
    //            Vector {6, 3, 3},
    //            Vector {6, 1, 3},
    //            Vector {6, 1, 0},
    //    }});
    //    o->add(Polygon {{
    //            Vector {0, 3, 0},
    //            Vector {0, 3, 4},
    //            Vector {6, 3, 4},
    //            Vector {6, 3, 3},
    //            Vector {1, 3, 3},
    //            Vector {1, 3, 0},
    //    }});
    //    o->add(Polygon {{
    //            Vector {1, 1, 0},
    //            Vector {6, 1, 0},
    //            Vector {6, 1, 3},
    //            Vector {1, 1, 3},
    //    }});
    //    o->add(Polygon {{
    //            Vector {1, 1, 0},
    //            Vector {1, 1, 3},
    //            Vector {1, 3, 3},
    //            Vector {1, 3, 0},
    //    }});
    //    o->add(Polygon {{
    //            Vector {1, 1, 3},
    //            Vector {6, 1, 3},
    //            Vector {6, 3, 3},
    //            Vector {1, 3, 3},
    //    }});
    //    o->add(Polygon {{
    //            Vector {0, 0, 0},
    //            Vector {6, 0, 0},
    //            Vector {6, 0, 4},
    //            Vector {0, 0, 4},
    //    }});
    //    o->add(Polygon {{
    //            Vector {0, 0, 0},
    //            Vector {0, 0, 4},
    //            Vector {0, 3, 4},
    //            Vector {0, 3, 0},
    //    }});
    //    o->add(Polygon {{
    //            Vector {0, 0, 4},
    //            Vector {6, 0, 4},
    //            Vector {6, 3, 4},
    //            Vector {0, 3, 4},
    //    }});
    //    o->add(Polygon {{
    //            Vector {1, 1, 1},
    //            Vector {6, 1, 1},
    //            Vector {1, 3, 1},
    //    }});
    //    o->add(Polygon {{
    //            Vector {1, 3, 1},
    //            Vector {6, 1, 1},
    //            Vector {6, 1, 2},
    //            Vector {1, 3, 2},
    //    }});
    //    o->add(Polygon {{
    //            Vector {1, 1, 2},
    //            Vector {6, 1, 2},
    //            Vector {1, 3, 2},
    //    }});

    World world;
    world.addSpaceShip();

    srand(time(NULL));
    for (int i = 0; i < 20; i++) {
        Target& t {world.addTarget()};
        t.yaw(toRadians(rand() % 360));
        t.roll(toRadians(rand() % 360));
        t.pitch(toRadians(rand() % 360));
        t.move(15 + (rand() % 5));
    }

    OrbitingCamera camera {};
    float cameraMovementSpeed {0.1};
    float cameraRotationSpeed {0.002};

    auto sdl = std::make_shared<space::sdl::SDLWrapper>(1000, 1000);
    auto renderer = std::make_unique<space::world::Renderer>(sdl);
    renderer->show_coordinate_system(true);
    renderer->show_hitboxes(true);

    SDL_bool done = SDL_FALSE;

    SDL_SetRelativeMouseMode(SDL_TRUE);
    while (!done) {
        auto* rocket = world.spaceship();

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                done = SDL_TRUE;
            }
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                        // TODO: world->spaceship()...dostuff
                    case SDLK_q:
                        rocket->roll(0.02);
                        break;
                    case SDLK_e:
                        rocket->roll(-0.02);
                        break;
                    case SDLK_w:
                        rocket->pitch(-0.02);
                        break;
                    case SDLK_s:
                        rocket->pitch(0.02);
                        break;
                    case SDLK_a:
                        rocket->yaw(0.02);
                        break;
                    case SDLK_d:
                        rocket->yaw(-0.02);
                        break;
                    case SDLK_LSHIFT:
                        rocket->setVelocity(0.4f);
                        break;
                    case SDLK_LCTRL:
                        rocket->setVelocity(rocket->getVelocity() / 2);
                        break;

                    case SDLK_UP:
                        camera.move(Vector {0, cameraMovementSpeed * 10, 0});
                        break;
                    case SDLK_RIGHT:
                        camera.move(Vector {cameraMovementSpeed * 10, 0, 0});
                        break;
                    case SDLK_DOWN:
                        camera.move(Vector {0, -cameraMovementSpeed * 10, 0});
                        break;
                    case SDLK_LEFT:
                        camera.move(Vector {-cameraMovementSpeed * 10, 0, 0});
                        break;
                    case SDLK_i:
                        camera.rotate(Vector {-cameraRotationSpeed * 10, 0, 0});
                        break;
                    case SDLK_l:
                        camera.rotate(Vector {0, -cameraRotationSpeed * 10, 0});
                        break;
                    case SDLK_k:
                        camera.rotate(Vector {cameraRotationSpeed * 10, 0, 0});
                        break;
                    case SDLK_j:
                        camera.rotate(Vector {0, cameraRotationSpeed * 10, 0});
                        break;
                    case SDLK_o:
                        camera.zoom(2);
                        break;
                    case SDLK_p:
                        camera.zoom(-2);
                        break;
                }
            }
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    rocket->shoot();
                }
            }
            if (event.type == SDL_MOUSEMOTION) {
                camera.rotate(
                        Vector {cameraRotationSpeed * event.motion.yrel, cameraRotationSpeed * event.motion.xrel, 0});
            }
            if (event.type == SDL_MOUSEWHEEL) {
                camera.zoom(0.8f * -event.wheel.y * (event.wheel.direction == SDL_MOUSEWHEEL_FLIPPED ? -1.0f : 1.0f));
            }
        }

        world.tick();

        sdl->clear();
        renderer->render_world(camera, world);
        sdl->present();

        SDL_Delay(20);
    }

    return 0;
}
