//
// Created by impodog on 9/9/23.
//

#ifndef SDL2_CPP_SURFACE_HPP
#define SDL2_CPP_SURFACE_HPP

#include "texture.hpp"

namespace sdl2::surface
{
    class Surface
    {
        SDL_Surface *ptr;

        explicit Surface(SDL_Surface *surface)
                : ptr(surface)
        {
            if (ptr == nullptr)
            {
                throw except::SDL2_Error();
            }
        }

        friend std::unique_ptr<Surface> make_surface(SDL_Surface *surface);

    public:
        Surface(int w, int h, int depth, Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask)
                : Surface(SDL_CreateRGBSurface(0, w, h, depth, Rmask, Gmask, Bmask, Amask))
        {}

        Surface(int w, int h, int depth, Uint32 Rmask, Uint32 Gmask, Uint32 Bmask)
                : Surface(w, h, depth, Rmask, Gmask, Bmask, 0)
        {}

        Surface(int w, int h, int depth)
                : Surface(w, h, depth, 0, 0, 0, 0)
        {}

        Surface(int w, int h)
                : Surface(w, h, 32)
        {}

        ~Surface() noexcept
        {
            SDL_FreeSurface(ptr);
            ptr = nullptr;
        }

        Surface(const Surface &) = delete;

        Surface &operator=(const Surface &) = delete;

        [[nodiscard]] SDL_Surface *get() const noexcept
        {
            return ptr;
        }

        SDL_Surface *operator->() const noexcept
        {
            return ptr;
        }

        void blit(const Surface &src)
        {
            if (SDL_BlitSurface(src.get(), nullptr, ptr, nullptr))
            {
                throw except::SDL2_Error();
            }
        }

        void blit(const Surface &src, const Point &dst_point)
        {
            Rect dst_rect{dst_point, src.get()->w, src.get()->h};
            if (SDL_BlitSurface(src.get(), nullptr, ptr, &dst_rect))
            {
                throw except::SDL2_Error();
            }
        }

        void blit(const Surface &src, Rect dst_rect)
        {
            if (SDL_BlitSurface(src.get(), nullptr, ptr, &dst_rect))
            {
                throw except::SDL2_Error();
            }
        }

        void blit(const Surface &src, const Rect &src_rect, Rect dst_rect)
        {
            if (SDL_BlitSurface(src.get(), &src_rect, ptr, &dst_rect))
            {
                throw except::SDL2_Error();
            }
        }

        void fill_rect(const Rect &rect, Uint32 color)
        {
            if (SDL_FillRect(ptr, &rect, color))
            {
                throw except::SDL2_Error();
            }
        }

        void fill_rects(const std::vector<Rect> &rects, Uint32 color)
        {
            if (SDL_FillRects(ptr, rects.data(), rects.size(), color))
            {
                throw except::SDL2_Error();
            }
        };

        void fill(Uint32 color)
        {
            if (SDL_FillRect(ptr, nullptr, color))
            {
                throw except::SDL2_Error();
            }
        }

        std::unique_ptr<Texture> convert(const Renderer &renderer)
        {
            return make_texture(SDL_CreateTextureFromSurface(renderer.get(), ptr));
        }
    };

    inline std::unique_ptr<Surface> make_surface(SDL_Surface *surface)
    {
        return std::unique_ptr<Surface>{new Surface(surface)};
    }
}

namespace sdl2
{
    using surface::Surface;
    using surface::make_surface;
}

namespace sdl2::window
{
    inline std::unique_ptr<::sdl2::surface::Surface> Window::get_surface() const
    {
        return surface::make_surface(SDL_GetWindowSurface(ptr));
    }
}
#endif //SDL2_CPP_SURFACE_HPP
