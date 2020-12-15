#define SDL_main main

#include "model/OBJParser.hpp"
#include "sdl/SDLWrapper.hpp"
#include "world/Matrix.hpp"
#include "world/Object.hpp"
#include "world/SpaceRenderer.hpp"

#include <iostream>

using namespace space::world;
using namespace space::sdl;

int main(int argc, char* argv[]) {

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////

    Object o {};
    o.add(Polygon {{
            Vector {0, 0, 0},
            Vector {6, 0, 0},
            Vector {6, 1, 0},
            Vector {1, 1, 0},
            Vector {1, 3, 0},
            Vector {0, 3, 0},
    }});
    o.add(Polygon {{
            Vector {6, 0, 0},
            Vector {6, 0, 4},
            Vector {6, 3, 4},
            Vector {6, 3, 3},
            Vector {6, 1, 3},
            Vector {6, 1, 0},
    }});
    o.add(Polygon {{
            Vector {0, 3, 0},
            Vector {0, 3, 4},
            Vector {6, 3, 4},
            Vector {6, 3, 3},
            Vector {1, 3, 3},
            Vector {1, 3, 0},
    }});
    o.add(Polygon {{
            Vector {1, 1, 0},
            Vector {6, 1, 0},
            Vector {6, 1, 3},
            Vector {1, 1, 3},
    }});
    o.add(Polygon {{
            Vector {1, 1, 0},
            Vector {1, 1, 3},
            Vector {1, 3, 3},
            Vector {1, 3, 0},
    }});
    o.add(Polygon {{
            Vector {1, 1, 3},
            Vector {6, 1, 3},
            Vector {6, 3, 3},
            Vector {1, 3, 3},
    }});
    o.add(Polygon {{
            Vector {0, 0, 0},
            Vector {6, 0, 0},
            Vector {6, 0, 4},
            Vector {0, 0, 4},
    }});
    o.add(Polygon {{
            Vector {0, 0, 0},
            Vector {0, 0, 4},
            Vector {0, 3, 4},
            Vector {0, 3, 0},
    }});
    o.add(Polygon {{
            Vector {0, 0, 4},
            Vector {6, 0, 4},
            Vector {6, 3, 4},
            Vector {0, 3, 4},
    }});
    o.add(Polygon {{
            Vector {1, 1, 1},
            Vector {6, 1, 1},
            Vector {1, 3, 1},
    }});
    o.add(Polygon {{
            Vector {1, 3, 1},
            Vector {6, 1, 1},
            Vector {6, 1, 2},
            Vector {1, 3, 2},
    }});
    o.add(Polygon {{
            Vector {1, 1, 2},
            Vector {6, 1, 2},
            Vector {1, 3, 2},
    }});


    //Object o = space::model::OBJParser::parse("./assets/rocket.txt");
    //o.scale(0.05, {0, 0, 0});

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////

    auto sdl = std::make_shared<space::sdl::SDLWrapper>(1000, 1000);
    auto spaceRenderer = std::make_unique<space::world::SpaceRenderer>(sdl);

    SDL_bool done = SDL_FALSE;

    while (!done) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                done = SDL_TRUE;
            }
        }

        float gridSize = 25;
        sdl->clear();
        spaceRenderer->renderGrid(Color {38, 38, 38}, gridSize);

        for (const auto& p : o.surfaces()) {
            spaceRenderer->renderPolygon(p, Color {0, 255, 0}, gridSize);
        }

        sdl->present();

        //        o.translate(0.001, 0.001, 0.001);
        //        o.scale(1.001);
        //o.rotateX(0.01);
        //o.rotateZ(0.01);
        o.surfaces()[0].rotateVec({0,0,1}, 0.01);
        //        p.scale(1.005, {0, 0});
        //        p.rotate(0.01);

        SDL_Delay(100);
    }

    return 0;
}
