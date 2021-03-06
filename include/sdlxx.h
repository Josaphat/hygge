#ifndef SDLXX_SDLXX_H
#define SDLXX_SDLXX_H

#include <SDL.h>
#include <iostream>
#include <stdexcept>

namespace sdlxx {

// RAII class so you can't forget to call SDL_Quit
class Sdl_system {
public:
    Sdl_system(decltype(SDL_INIT_VIDEO) flags)
    {
        const auto init_result = SDL_Init(flags);
        if (init_result != 0) {
            throw std::runtime_error{"SDL_Init Error: " +
                                     std::string(SDL_GetError())};
        }
    }
    ~Sdl_system() { SDL_Quit(); }
};

class Sdl_window {
public:
    Sdl_window(const char* title, int x, int y, int w, int h,
               std::uint32_t flags)
        : window_{SDL_CreateWindow(title, x, y, w, h, flags)}
    {
        if (window_ == NULL) {
            throw std::runtime_error{"SDL_CreateWindow Error: " +
                                     std::string(SDL_GetError())};
        }
    }
    ~Sdl_window() { SDL_DestroyWindow(window_); }

    // Allow an Sdl_window to be implicitly converted to SDL_Window*
    operator SDL_Window*() { return window_; }

private:
    SDL_Window* window_;
};

class Sdl_renderer {
public:
    Sdl_renderer(Sdl_window& window, int index, std::uint32_t flags)
        : renderer_{SDL_CreateRenderer(window, index, flags)}
    {
        if (renderer_ == nullptr) {
            throw std::runtime_error{"SDL_CreateRenderer Error: " +
                                     std::string(SDL_GetError())};
        }
    }
    ~Sdl_renderer() { SDL_DestroyRenderer(renderer_); }

    void clear()
    {
        SDL_SetRenderDrawColor(renderer_, 0, 0, 0, SDL_ALPHA_OPAQUE);

        SDL_RenderClear(renderer_);
    }

    /// Copies the given texture into the renderer at destination coordinates
    /// given by \p x and \p y, and scaled to width \p w and height \p h.
    void copy(SDL_Texture* texture, int x, int y, int w, int h)
    {
        SDL_Rect dest;
        dest.x = x;
        dest.y = y;
        dest.w = w;
        dest.h = h;
        SDL_RenderCopy(renderer_, texture, nullptr, &dest);
    }

    /// Copies the given texture into the renderer without any scaling.
    void copy(SDL_Texture* texture, int x, int y)
    {
        int w, h;
        SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
        copy(texture, x, y, w, h);
    }

    void copy(SDL_Texture* texture, int x, int y, SDL_Rect* clip)
    {
        int w, h;
        w = clip->w;
        h = clip->h;
        SDL_Rect dest{ x, y, w, h };
        SDL_RenderCopyEx(renderer_, texture, clip, &dest,0,
            /*center=*/nullptr, SDL_FLIP_NONE);
    }

    void copy(SDL_Texture* texture, int x, int y, SDL_Rect* clip, double angle)
    {
        int w, h;
        w = clip->w;
        h = clip->h;
        SDL_Rect dest{x, y, w, h};
        SDL_RenderCopyEx(renderer_, texture, clip, &dest, angle,
                         /*center=*/nullptr, SDL_FLIP_NONE);
    }

    void present() { SDL_RenderPresent(renderer_); }

    void fill_rect(int x, int y, int w, int h, int color_r, int color_g,
                   int color_b)
    {
        SDL_SetRenderDrawColor(renderer_, color_r, color_g, color_b,
                               SDL_ALPHA_OPAQUE);
        SDL_Rect rect;
        rect.x = x;
        rect.y = y;
        rect.w = w;
        rect.h = h;
        SDL_RenderFillRect(renderer_, &rect);
    }

    void draw_rect(int x, int y, int w, int h, int color_r, int color_g,
                   int color_b)
    {
        uint8_t r, g, b, a;
        SDL_GetRenderDrawColor(renderer_, &r, &g, &b, &a);
        SDL_SetRenderDrawColor(renderer_, color_r, color_g, color_b,
                               SDL_ALPHA_OPAQUE);
        SDL_Rect rect;
        rect.x = x;
        rect.y = y;
        rect.w = w;
        rect.h = h;
        SDL_RenderDrawRect(renderer_, &rect);
        SDL_SetRenderDrawColor(renderer_, r, g, b, SDL_ALPHA_OPAQUE);
    }

    operator SDL_Renderer*() { return renderer_; }

private:
    SDL_Renderer* renderer_;
};

class Sdl_surface {
public:
    ~Sdl_surface()
    {
        if (surface_ != nullptr) { SDL_FreeSurface(surface_); }
    }

    void free()
    {
        SDL_FreeSurface(surface_);
        surface_ = nullptr;
    }

    operator SDL_Surface*() { return surface_; }

    static Sdl_surface load_bmp(std::string path)
    {
        return {SDL_LoadBMP(path.c_str())};
    }

private:
    Sdl_surface(SDL_Surface* surf) : surface_{surf}
    {
        if (surface_ == nullptr) {
            throw std::runtime_error{"Creating SDL_Surface failed: " +
                                     std::string(SDL_GetError())};
        }
    }

    SDL_Surface* surface_;
};

class Sdl_texture {
public:
    Sdl_texture(Sdl_renderer& renderer, Sdl_surface& surface)
        : texture_{SDL_CreateTextureFromSurface(renderer, surface)}
    {
        if (texture_ == nullptr) {
            throw std::runtime_error{"CreateTextureFromSurface failed: " +
                                     std::string(SDL_GetError())};
        }
    }

    Sdl_texture(const std::string& path, Sdl_renderer& renderer)
    {
        auto surf = Sdl_surface::load_bmp(path);
        texture_ = SDL_CreateTextureFromSurface(renderer, surf);
        surf.free();
        if (texture_ == nullptr) {
            throw std::runtime_error{"Failed to create texture from surface: " +
                                     std::string(SDL_GetError())};
        }
    }

    Sdl_texture(Sdl_texture && rhs)
        : texture_{rhs.texture_}
    {
        rhs.texture_ = nullptr;
    }

    ~Sdl_texture() { if (texture_ != nullptr) {SDL_DestroyTexture(texture_);} }

    operator SDL_Texture*() { return texture_; }

private:
    SDL_Texture* texture_;
};

}  // namespace sdlxx

#endif
