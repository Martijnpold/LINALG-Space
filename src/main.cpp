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

    SDLWrapper wrapper {};

    return 0;
}

int WinMain() {
    return main();
}
