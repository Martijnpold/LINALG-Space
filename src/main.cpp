#define SDL_main main

#include <iostream>
#include "sdl/SDLWrapper.hpp"
#include "world/Vector.hpp"

using namespace space::world;
using namespace space::sdl;

int main() {
    Vector a{5, 10};
    Vector b{10, -5};
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << a + b << std::endl;
    std::cout << a - b << std::endl;
    std::cout << a * 3 << std::endl;

    auto sdl = std::make_shared<space::sdl::SDLWrapper>(500, 500);

    SDL_bool done = SDL_FALSE;

    while (!done) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                done = SDL_TRUE;
            }
        }

        sdl->clear();
        sdl->setColor(255, 0, 0);
        sdl->drawLine(0, 0, 100, 100);
        sdl->present();
    }

    return 0;
}
