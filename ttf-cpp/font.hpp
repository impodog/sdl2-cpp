//
// Created by impodog on 9/10/23.
//

#ifndef SDL2_CPP_FONT_HPP
#define SDL2_CPP_FONT_HPP

#include "../include.h"
#include "../sdl2-cpp/sdl2-cpp.h"
#include "SDL2/SDL_ttf.h"

namespace sdl2::ttf
{
    class Font
    {
        TTF_Font *ptr;

        explicit Font(TTF_Font *ptr)
                : ptr(ptr)
        {
            if (ptr == nullptr)
            {
                throw except::SDL2_Error();
            }
        }

        friend std::unique_ptr<Font> make_font(TTF_Font *ptr);

    public:
        Font(const char *file, int size)
                : Font(TTF_OpenFont(file, size))
        {
        }

        ~Font()
        {
            TTF_CloseFont(ptr);
        }

        Font(const Font &) = delete;

        Font &operator=(const Font &) = delete;

        // Font attribute getters

        [[nodiscard]] int ascent() const noexcept
        {
            return TTF_FontAscent(ptr);
        }

        [[nodiscard]] int descent() const noexcept
        {
            return TTF_FontDescent(ptr);
        }

        [[nodiscard]] const char *family_name() const noexcept
        {
            return TTF_FontFaceFamilyName(ptr);
        }

        [[nodiscard]] bool is_fixed_width() const noexcept
        {
            return TTF_FontFaceIsFixedWidth(ptr);
        }

        [[nodiscard]] const char *style_name() const noexcept
        {
            return TTF_FontFaceStyleName(ptr);
        }

        [[nodiscard]] long faces() const noexcept
        {
            return TTF_FontFaces(ptr);
        }

        [[nodiscard]] int height() const noexcept
        {
            return TTF_FontHeight(ptr);
        }

        [[nodiscard]] int line_skip() const noexcept
        {
            return TTF_FontLineSkip(ptr);
        }

        [[nodiscard]] int get_hinting() const noexcept
        {
            return TTF_GetFontHinting(ptr);
        }

        [[nodiscard]] int get_kerning() const noexcept
        {
            return TTF_GetFontKerning(ptr);
        }

        [[nodiscard]] int get_kerning_glyphs(Uint16 previous_ch, Uint16 ch) const noexcept
        {
            return TTF_GetFontKerningSizeGlyphs(ptr, previous_ch, ch);
        }

        [[nodiscard]] int get_kerning_glyphs32(Uint32 previous_ch, Uint32 ch) const noexcept
        {
            return TTF_GetFontKerningSizeGlyphs32(ptr, previous_ch, ch);
        }

        [[nodiscard]] int get_outline() const noexcept
        {
            return TTF_GetFontOutline(ptr);
        }

        [[nodiscard]] int get_style() const noexcept
        {
            return TTF_GetFontStyle(ptr);
        }

        [[nodiscard]] int get_wrapped_align() const noexcept
        {
            return TTF_GetFontWrappedAlign(ptr);
        }

        // Font attribute setters

        void set_size(int size) const noexcept
        {
            TTF_SetFontSize(ptr, size);
        }

        void set_hinting(int hinting) const noexcept
        {
            TTF_SetFontHinting(ptr, hinting);
        }

        void set_kerning(bool allowed) const noexcept
        {
            TTF_SetFontKerning(ptr, allowed);
        }

        void set_outline(int outline) const noexcept
        {
            TTF_SetFontOutline(ptr, outline);
        }

        void set_style(int style) const noexcept
        {
            TTF_SetFontStyle(ptr, style);
        }

        void set_wrapped_align(int wrapped_align) const noexcept
        {
            TTF_SetFontWrappedAlign(ptr, wrapped_align);
        }

        // Rendering text

        [[nodiscard]] std::unique_ptr<Surface> render_solid(const char *text, const Color &color) const
        {
            return make_surface(TTF_RenderText_Solid(ptr, text, color));
        }

        [[nodiscard]] std::unique_ptr<Surface> render_shaded(const char *text, const Color &fg, const Color &bg) const
        {
            return make_surface(TTF_RenderText_Shaded(ptr, text, fg, bg));
        }

        [[nodiscard]] std::unique_ptr<Surface> render_blended(const char *text, const Color &color) const
        {
            return make_surface(TTF_RenderText_Blended(ptr, text, color));
        }

        [[nodiscard]] std::unique_ptr<Surface>
        render_blended_wrapped(const char *text, const Color &color, Uint32 wrap_length) const
        {
            return make_surface(TTF_RenderText_Blended_Wrapped(ptr, text, color, wrap_length));
        }

        [[nodiscard]] std::unique_ptr<Surface> render_utf8_solid(const char *text, const Color &color) const
        {
            return make_surface(TTF_RenderUTF8_Solid(ptr, text, color));
        }

        [[nodiscard]] std::unique_ptr<Surface>
        render_utf8_shaded(const char *text, const Color &fg, const Color &bg) const
        {
            return make_surface(TTF_RenderUTF8_Shaded(ptr, text, fg, bg));
        }

        [[nodiscard]] std::unique_ptr<Surface> render_utf8_blended(const char *text, const Color &color) const
        {
            return make_surface(TTF_RenderUTF8_Blended(ptr, text, color));
        }

        [[nodiscard]] std::unique_ptr<Surface>
        render_utf8_blended_wrapped(const char *text, const Color &color, Uint32 wrap_length) const
        {
            return make_surface(TTF_RenderUTF8_Blended_Wrapped(ptr, text, color, wrap_length));
        }

        [[nodiscard]] std::unique_ptr<Surface> render_glyph_solid(Uint16 ch, const Color &color) const
        {
            return make_surface(TTF_RenderGlyph_Solid(ptr, ch, color));
        }

        [[nodiscard]] std::unique_ptr<Surface> render_glyph_shaded(Uint16 ch, const Color &fg, const Color &bg) const
        {
            return make_surface(TTF_RenderGlyph_Shaded(ptr, ch, fg, bg));
        }

        [[nodiscard]] std::unique_ptr<Surface> render_glyph_blended(Uint16 ch, const Color &color) const
        {
            return make_surface(TTF_RenderGlyph_Blended(ptr, ch, color));
        }
    };

    inline std::unique_ptr<Font> make_font(TTF_Font *ptr)
    {
        return std::unique_ptr<Font>{new Font(ptr)};
    }
}

namespace sdl2
{
    using ttf::Font;
    using ttf::make_font;
}

#endif //SDL2_CPP_FONT_HPP
