//
// Created by impodog on 9/9/23.
//

#ifndef SDL2_CPP_TEXTURE_HPP
#define SDL2_CPP_TEXTURE_HPP

#include "renderer.hpp"

namespace sdl2::texture
{
    class Texture
    {
        SDL_Texture *texture;

        explicit Texture(SDL_Texture *texture)
                : texture(texture)
        {
            if (texture == nullptr)
            {
                throw except::SDL2_Error();
            }
        }

        friend std::unique_ptr<Texture> make_texture(SDL_Texture *texture);

    public:
        Texture(const Renderer &renderer, Uint32 format, int access, int w, int h)
                : Texture(SDL_CreateTexture(renderer.get(), format, access, w, h))
        {}

        ~Texture() noexcept
        {
            SDL_DestroyTexture(texture);
            texture = nullptr;
        }

        Texture(const Texture &) = delete;

        Texture &operator=(const Texture &) = delete;

        [[nodiscard]] SDL_Texture *get() const noexcept
        {
            return texture;
        }

        void query(Uint32 *format, int *access, int *w, int *h) const
        {
            if (SDL_QueryTexture(texture, format, access, w, h))
            {
                throw except::SDL2_Error();
            }
        }

        void set_color_mod(const Color &color)
        {
            if (SDL_SetTextureColorMod(texture, color.r, color.g, color.b))
            {
                throw except::SDL2_Error();
            }
        }

        void set_alpha_mod(Uint8 alpha)
        {
            if (SDL_SetTextureAlphaMod(texture, alpha))
            {
                throw except::SDL2_Error();
            }
        }

        void set_blend_mode(SDL_BlendMode blend_mode)
        {
            if (SDL_SetTextureBlendMode(texture, blend_mode))
            {
                throw except::SDL2_Error();
            }
        }

        void lock(const Rect *rect, void **pixels, int *pitch)
        {
            if (SDL_LockTexture(texture, rect, pixels, pitch))
            {
                throw except::SDL2_Error();
            }
        }

        void unlock()
        {
            SDL_UnlockTexture(texture);
        }

        void update(const Rect *rect, const void *pixels, int pitch)
        {
            if (SDL_UpdateTexture(texture, rect, pixels, pitch))
            {
                throw except::SDL2_Error();
            }
        }

        [[nodiscard]] Rect query_src() const
        {
            Rect rect;
            query(nullptr, nullptr, &rect.w, &rect.h);
            return rect;
        }

        void copy_to(const Renderer &renderer) const
        {
            if (SDL_RenderCopy(renderer.get(), texture, nullptr, nullptr))
            {
                throw except::SDL2_Error();
            }
        }

        void copy_to(const Renderer &renderer, const Rect &dst) const
        {
            if (SDL_RenderCopy(renderer.get(), texture, nullptr, &dst))
            {
                throw except::SDL2_Error();
            }
        }

        void copy_to(const Renderer &renderer, const Rect &src, const Rect &dst) const
        {
            if (SDL_RenderCopy(renderer.get(), texture, &src, &dst))
            {
                throw except::SDL2_Error();
            }
        }
    };

    std::unique_ptr<Texture> make_texture(SDL_Texture *texture)
    {
        return std::unique_ptr<Texture>{new Texture(texture)};
    }
}

namespace sdl2
{
    using sdl2::texture::Texture;
    using sdl2::texture::make_texture;
}

namespace sdl2::renderer
{
    void Renderer::set_target(const ::sdl2::texture::Texture &texture) const
    {
        if (SDL_SetRenderTarget(renderer, texture.get()))
        {
            throw except::SDL2_Error();
        }
    }

    void Renderer::copy(const ::sdl2::texture::Texture &texture, const Rect &src_rect, const Rect &dst_rect) const
    {
        if (SDL_RenderCopy(renderer, texture.get(), &src_rect, &dst_rect))
        {
            throw except::SDL2_Error();
        }
    }

    void Renderer::copy(const Texture &texture, const Rect &dst_rect) const
    {
        if (SDL_RenderCopy(renderer, texture.get(), nullptr, &dst_rect))
        {
            throw except::SDL2_Error();
        }
    }

    void Renderer::copy(const Texture &texture) const
    {
        if (SDL_RenderCopy(renderer, texture.get(), nullptr, nullptr))
        {
            throw except::SDL2_Error();
        }
    }
}

#endif //SDL2_CPP_TEXTURE_HPP
