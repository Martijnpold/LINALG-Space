#pragma once

#include <memory>
#include <SDL.h>

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
        SDLWrapper(int width, int height);

        ~SDLWrapper();

        void drawLine(float x, float y, float x2, float y2);

        void clear();

        void present();

        void setColor(int r, int g, int b);

        int getWidth();

        int getHeight();
    };
}
