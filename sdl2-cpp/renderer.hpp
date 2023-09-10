//
// Created by impodog on 9/9/23.
//

#ifndef SDL2_CPP_RENDERER_HPP
#define SDL2_CPP_RENDERER_HPP

#include "window.hpp"

namespace sdl2::texture
{
    class Texture;
}

namespace sdl2::renderer
{
    class Renderer
    {
        SDL_Renderer *renderer;

        explicit Renderer(SDL_Renderer *renderer)
                : renderer(renderer)
        {
            if (renderer == nullptr)
            {
                throw except::SDL2_Error();
            }
        }

        friend std::unique_ptr<Renderer> make_renderer(SDL_Renderer *renderer);

    public:
        Renderer(const Window &window, int index, Uint32 flags)
                : Renderer(SDL_CreateRenderer(window.get(), index, flags))
        {}

        Renderer(const Window &window, int index)
                : Renderer(window, index, SDL_RENDERER_ACCELERATED)
        {}

        explicit Renderer(const Window &window)
                : Renderer(window, -1)
        {}

        ~Renderer() noexcept
        {
            SDL_DestroyRenderer(renderer);
            renderer = nullptr;
        }

        Renderer(const Renderer &) = delete;

        Renderer &operator=(const Renderer &) = delete;

        [[nodiscard]] SDL_Renderer *get() const noexcept
        {
            return renderer;
        }

        [[nodiscard]] SDL_RendererInfo get_info() const
        {
            SDL_RendererInfo info;
            if (SDL_GetRendererInfo(renderer, &info))
            {
                throw except::SDL2_Error();
            }
            return info;
        }

        [[nodiscard]] Point get_output_size() const
        {
            int w, h;
            SDL_GetRendererOutputSize(renderer, &w, &h);
            return {w, h};
        }

        void set_draw_color(const Color &color) const
        {
            if (SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a))
            {
                throw except::SDL2_Error();
            }
        }

        void set_draw_blend_mode(SDL_BlendMode blendMode) const
        {
            if (SDL_SetRenderDrawBlendMode(renderer, blendMode))
            {
                throw except::SDL2_Error();
            }
        }

        void set_target(const ::sdl2::texture::Texture &texture) const;

        void set_target() const
        {
            if (SDL_SetRenderTarget(renderer, nullptr))
            {
                throw except::SDL2_Error();
            }
        }

        void set_clip_rect(const Rect &rect) const
        {
            if (SDL_RenderSetClipRect(renderer, &rect))
            {
                throw except::SDL2_Error();
            }
        }

        void set_clip_rect() const
        {
            if (SDL_RenderSetClipRect(renderer, nullptr))
            {
                throw except::SDL2_Error();
            }
        }

        void set_scale(float scaleX, float scaleY) const
        {
            if (SDL_RenderSetScale(renderer, scaleX, scaleY))
            {
                throw except::SDL2_Error();
            }
        }

        void set_scale() const
        {
            if (SDL_RenderSetScale(renderer, 1.0f, 1.0f))
            {
                throw except::SDL2_Error();
            }
        }

        void set_logical_size(int w, int h) const
        {
            if (SDL_RenderSetLogicalSize(renderer, w, h))
            {
                throw except::SDL2_Error();
            }
        }

        void copy(const ::sdl2::texture::Texture &texture, const Rect &src_rect, const Rect &dst_rect) const;

        void copy(const ::sdl2::texture::Texture &texture, const Rect &dst_rect) const;

        void copy(const ::sdl2::texture::Texture &texture) const;

        void clear() const
        {
            if (SDL_RenderClear(renderer))
            {
                throw except::SDL2_Error();
            }
        }

        void present() const
        {
            SDL_RenderPresent(renderer);
        }

        void fill_rect(const Rect &rect) const
        {
            if (SDL_RenderFillRect(renderer, &rect))
            {
                throw except::SDL2_Error();
            }
        }

        void draw_line(const Point &p1, const Point &p2) const
        {
            if (SDL_RenderDrawLine(renderer, p1.x, p1.y, p2.x, p2.y))
            {
                throw except::SDL2_Error();
            }
        }

        void draw_rect(const Rect &rect) const
        {
            if (SDL_RenderDrawRect(renderer, &rect))
            {
                throw except::SDL2_Error();
            }
        }

        void draw_point(const Point &p) const
        {
            if (SDL_RenderDrawPoint(renderer, p.x, p.y))
            {
                throw except::SDL2_Error();
            }
        }

        void draw_points(const std::vector<Point> &points) const
        {
            if (SDL_RenderDrawPoints(renderer, points.data(), points.size()))
            {
                throw except::SDL2_Error();
            }
        }
    };

    std::unique_ptr<Renderer> make_renderer(SDL_Renderer *renderer)
    {
        return std::unique_ptr<Renderer>{new Renderer(renderer)};
    }
}

namespace sdl2
{
    using renderer::Renderer;
    using renderer::make_renderer;
}
#endif //SDL2_CPP_RENDERER_HPP
