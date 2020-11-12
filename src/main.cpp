#define SDL_main main

#include <iostream>
#include <world/SpaceRenderer.hpp>
#include "sdl/SDLWrapper.hpp"
#include "world/Vector.hpp"

using namespace space::world;
using namespace space::sdl;

int main() {
    Vector a{2, 4};
    Vector b{4, -2};
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
        spaceRenderer->renderVector(a * 1.25, 25);
        sdl->present();
    }

    return 0;
}
