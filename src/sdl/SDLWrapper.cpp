#include "SDLWrapper.hpp"

namespace space::sdl {
    SDLWrapper::SDLWrapper() {
        SDL_Init(SDL_INIT_VIDEO);

        _window.reset(SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                       500, 500, 0));
        _renderer.reset(SDL_CreateRenderer(_window.get(), -1, SDL_RENDERER_ACCELERATED));
    }

    SDLWrapper::~SDLWrapper() {
        SDL_Quit();
    }
}