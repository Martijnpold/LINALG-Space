#define SDL_main main

#include "sdl/SDLWrapper.hpp"
#include "world/Vector.hpp"

#include "world/Matrix.hpp"

#include <iostream>
#include <world/SpaceRenderer.hpp>

using namespace space::world;
using namespace space::sdl;

int main(int argc, char* argv[]) {
    Vector a {2, 4};
    Vector b {-1, 2};
    std::cout << "a: " << a << std::endl;
    std::cout << "b: " << b << std::endl;
    std::cout << "a + b: " << a + b << std::endl;
    std::cout << "a - b: " << a - b << std::endl;
    std::cout << "2 * a: " << a * 2 << std::endl;

    std::cout << std::endl;

    Matrix A {2, 2, {1, 2, 3, 4}};
    Matrix B {2, 2, {4, 3, 2, 1}};
    std::cout << "A: " << A << std::endl;
    std::cout << "B: " << B << std::endl;
    std::cout << "A + B: " << A + B << std::endl;
    std::cout << "A - B: " << A - B << std::endl;

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
