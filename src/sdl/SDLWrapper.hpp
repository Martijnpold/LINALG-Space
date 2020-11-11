#pragma once

#include <memory>

/*
    while (1) {
        SDL_Event e;
        if (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                break;
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, bitmapTex, NULL, NULL);
        SDL_RenderPresent(renderer);
    }
 */

namespace space::sdl {
    class SDLWrapper {
    private:
        std::unique_ptr<SDL_Window, void (*)(SDL_Window *)> _window{nullptr, SDL_DestroyWindow};
        std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer *)> _renderer{nullptr, SDL_DestroyRenderer};
    public:
        SDLWrapper();

        ~SDLWrapper();
    };
}
