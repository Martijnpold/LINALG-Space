#define SDL_main main

#include "sdl/SDLWrapper.hpp"
#include "world/Matrix.hpp"
#include "world/Object.hpp"
#include "world/SpaceRenderer.hpp"

#include <iostream>

using namespace space::world;
using namespace space::sdl;

int main(int argc, char* argv[]) {
    std::cout << "Vector (basics)" << std::endl;
    std::cout << std::endl;

    Vector a {2, 4, 0};
    Vector b {-1, 2, 0};
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

    Matrix E = Matrix::createTranslationMatrix(-1, 2, 1);
    Matrix F = Matrix::createScalingMatrix(2, 2, 2);
    Vector c {3, -1, 3};
    std::cout << "E: " << E << std::endl;
    std::cout << "F: " << F << std::endl;
    std::cout << "c: " << c << std::endl;
    std::cout << "E * c: " << E * c << std::endl;
    std::cout << "F * c: " << F * c << std::endl;

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
    std::cout << "kloenk " << o.center() << std::endl;

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
        o.rotateZ(0.01);
        o.rotateX(0.01);
        //        p.scale(1.005, {0, 0});
        //        p.rotate(0.01);

        SDL_Delay(50);
    }

    return 0;
}
