#include "SDLWrapper.hpp"

namespace space::sdl {
    SDLWrapper::SDLWrapper(int width, int height) {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            printf("SDL_Init failed: %s\n", SDL_GetError());
        }

        _window.reset(SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                       width, height, 0));
        _renderer.reset(SDL_CreateRenderer(_window.get(), -1, SDL_RENDERER_ACCELERATED));
    }

    SDLWrapper::~SDLWrapper() {
        SDL_Quit();
    }

    void SDLWrapper::drawLine(float x, float y, float x2, float y2) {
        SDL_RenderDrawLineF(_renderer.get(), x, y, x2, y2);
    }

    void SDLWrapper::clear() {
        setColor(0, 0, 0);
        SDL_RenderClear(_renderer.get());
    }

    void SDLWrapper::setColor(int r, int g, int b) {
        SDL_SetRenderDrawColor(_renderer.get(), r, g, b, 255);
    }

    void SDLWrapper::present() {
        SDL_RenderPresent(_renderer.get());
    }

    int SDLWrapper::getWidth() {
        int w;
        SDL_GetWindowSize(_window.get(), &w, nullptr);
        return w;
    }

    int SDLWrapper::getHeight() {
        int h;
        SDL_GetWindowSize(_window.get(), nullptr, &h);
        return h;
    }
}