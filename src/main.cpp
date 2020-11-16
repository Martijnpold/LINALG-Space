#define SDL_main main

#include "sdl/SDLWrapper.hpp"
#include "world/Matrix.hpp"
#include "world/Vector.hpp"

#include <iostream>
#include <math.h>
#include <world/SpaceRenderer.hpp>

using namespace space::world;
using namespace space::sdl;

int main(int argc, char* argv[]) {
    std::cout << "Vector (basics)" << std::endl;
    std::cout << std::endl;

    Vector a {2, 4};
    Vector b {-1, 2};
    std::cout << "a: " << a << std::endl;
    std::cout << "b: " << b << std::endl;
    std::cout << "a + b: " << a + b << std::endl;
    std::cout << "a - b: " << a - b << std::endl;
    std::cout << "2 * a: " << a * 2 << std::endl;

    std::cout << std::endl;
    std::cout << "Matrices (basic)" << std::endl;
    std::cout << std::endl;

    Matrix A {2, 2, {1, 2, 3, 4}};
    Matrix B {2, 2, {4, 3, 2, 1}};
    std::cout << "A: " << A << std::endl;
    std::cout << "B: " << B << std::endl;
    std::cout << "A + B: " << A + B << std::endl;
    std::cout << "A - B: " << A - B << std::endl;

    std::cout << std::endl;
    std::cout << "Matrix multiplication:" << std::endl;
    std::cout << std::endl;

    Matrix C {3, 2, {1, 2, 3, 4, 5, 6}};
    Matrix D {2, 3, {7, 8, 9, 10, 11, 12}};
    std::cout << "C: " << C << std::endl;
    std::cout << "D: " << D << std::endl;
    std::cout << "C * D: " << C * D << std::endl;

    std::cout << std::endl;
    std::cout << "Matrix multiplication with Vector:" << std::endl;
    std::cout << std::endl;

    Matrix E {3, 3, {1, 0, -1, 0, 1, 2, 0, 0, 1}};
    Vector c {3, -1};
    std::cout << "E: " << E << std::endl;
    std::cout << "c: " << c << std::endl;
    std::cout << "E * c: " << E * c << std::endl;
    
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
        spaceRenderer->renderVector(a + b, Color {0, 0, 255}, gridSize);
        spaceRenderer->renderVector(a - b, Color {255, 255, 0}, gridSize);
        spaceRenderer->renderVector(1.25 * a, Color {255, 0, 255}, gridSize);
        spaceRenderer->renderVector(a, Color {255, 0, 0}, gridSize);
        spaceRenderer->renderVector(b, Color {0, 255, 0}, gridSize);
        sdl->present();

        SDL_Delay(50);
    }

    return 0;
}
