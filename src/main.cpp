#define SDL_main main

#include "sdl/SDLWrapper.hpp"
#include "world/Vector.hpp"

#include <iostream>
#include <world/SpaceRenderer.hpp>

using namespace space::world;
using namespace space::sdl;

int main(int argc, char* argv[]) {
    Vector a {2, 4};
    Vector b {4, -2};
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << a + b << std::endl;
    std::cout << a - b << std::endl;
    std::cout << a * 2 << std::endl;

    auto sdl = std::make_shared<space::sdl::SDLWrapper>(500, 500);
    auto spaceRenderer = std::make_unique<space::world::SpaceRenderer>(sdl);

    SDL_bool done = SDL_FALSE;

    while (!done) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                done = SDL_TRUE;
            }
        }

        sdl->clear();
        spaceRenderer->renderGrid(25);
        spaceRenderer->renderVector(a, 25);
        spaceRenderer->renderVector(b, 25);
        spaceRenderer->renderVector(a + b, 25);
        spaceRenderer->renderVector(a - b, 25);
        spaceRenderer->renderVector(1.25 * a, 25);
        sdl->present();

        SDL_Delay(50);
    }

    return 0;
}
