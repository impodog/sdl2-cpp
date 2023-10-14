//
// Created by impodog on 9/9/23.
//

#ifndef SDL2_CPP_WINDOW_HPP
#define SDL2_CPP_WINDOW_HPP

#include "rect.hpp"
#include "color.hpp"

namespace sdl2::surface
{
    class Surface;
}

namespace sdl2::window
{
    class Window
    {
        SDL_Window *ptr;

        explicit Window(SDL_Window *window)
                : ptr(window)
        {
            if (ptr == nullptr)
            {
                throw except::SDL2_Error();
            }
        }

        friend std::unique_ptr<Window> make_window(SDL_Window *window);

    public:
        Window(const char *title, int x, int y, int w, int h, Uint32 flags)
                : Window(SDL_CreateWindow(title, x, y, w, h, flags))
        {}

        Window(const char *title, int w, int h, Uint32 flags)
                : Window(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, flags)
        {}

        ~Window() noexcept
        {
            SDL_DestroyWindow(ptr);
            ptr = nullptr;
        }

        Window(const Window &) = delete;

        Window &operator=(const Window &) = delete;

        [[nodiscard]] SDL_Window *get() const noexcept
        {
            return ptr;
        }

        [[nodiscard]] Uint32 get_id() const noexcept
        {
            return SDL_GetWindowID(ptr);
        }

        [[nodiscard]] std::string get_title() const noexcept
        {
            return SDL_GetWindowTitle(ptr);
        }

        [[nodiscard]] sdl2::Point get_position() const noexcept
        {
            int x, y;
            SDL_GetWindowPosition(ptr, &x, &y);
            return {x, y};
        }

        [[nodiscard]] sdl2::Point get_size() const noexcept
        {
            int w, h;
            SDL_GetWindowSize(ptr, &w, &h);
            return {w, h};
        }

        [[nodiscard]] int get_display_index() const noexcept
        {
            return SDL_GetWindowDisplayIndex(ptr);
        }

        [[nodiscard]] SDL_DisplayMode get_display_mode() const
        {
            SDL_DisplayMode mode;
            if (SDL_GetWindowDisplayMode(ptr, &mode))
            {
                throw except::SDL2_Error();
            }
            return mode;
        }

        [[nodiscard]] Uint32 get_flags() const noexcept
        {
            return SDL_GetWindowFlags(ptr);
        }

        [[nodiscard]] std::unique_ptr<::sdl2::surface::Surface> get_surface() const;

        [[nodiscard]] auto get_pixel_format() const noexcept
        {
            return SDL_GetWindowPixelFormat(ptr);
        }

        [[nodiscard]] void *get_data(const char *name) const noexcept
        {
            return SDL_GetWindowData(ptr, name);
        }

        [[nodiscard]] float get_opacity() const
        {
            float opacity;
            if (SDL_GetWindowOpacity(ptr, &opacity))
            {
                throw except::SDL2_Error();
            }
            return opacity;
        }

        [[nodiscard]] bool get_grab() const noexcept
        {
            return SDL_GetWindowGrab(ptr);
        }

        [[nodiscard]] float get_brightness() const noexcept
        {
            return SDL_GetWindowBrightness(ptr);
        }

        void get_gamma_ramp(Uint16 *red, Uint16 *green, Uint16 *blue)
        {
            if (SDL_GetWindowGammaRamp(ptr, red, green, blue))
            {
                throw except::SDL2_Error();
            }
        }

        void set_title(const char *title) noexcept
        {
            SDL_SetWindowTitle(ptr, title);
        }

        void set_icon(SDL_Surface *icon) noexcept
        {
            SDL_SetWindowIcon(ptr, icon);
        }

        void set_position(int x, int y) noexcept
        {
            SDL_SetWindowPosition(ptr, x, y);
        }

        void set_size(int w, int h) noexcept
        {
            SDL_SetWindowSize(ptr, w, h);
        }

        void set_minimum_size(int min_w, int min_h) noexcept
        {
            SDL_SetWindowMinimumSize(ptr, min_w, min_h);
        }

        void set_maximum_size(int max_w, int max_h) noexcept
        {
            SDL_SetWindowMaximumSize(ptr, max_w, max_h);
        }

        void set_bordered(bool bordered) noexcept
        {
            SDL_SetWindowBordered(ptr, bordered ? SDL_TRUE : SDL_FALSE);
        }

        void set_resizable(bool resizable) noexcept
        {
            SDL_SetWindowResizable(ptr, resizable ? SDL_TRUE : SDL_FALSE);
        }

        void set_fullscreen(Uint32 flags) noexcept
        {
            SDL_SetWindowFullscreen(ptr, flags);
        }

        void set_display_mode(const SDL_DisplayMode *mode) noexcept
        {
            SDL_SetWindowDisplayMode(ptr, mode);
        }

        void set_gamma_ramp(const Uint16 *red, const Uint16 *green, const Uint16 *blue)
        {
            if (SDL_SetWindowGammaRamp(ptr, red, green, blue))
            {
                throw except::SDL2_Error();
            }
        }

        void set_hit_test(SDL_HitTest callback, void *callback_data) noexcept
        {
            SDL_SetWindowHitTest(ptr, callback, callback_data);
        }

        void set_data(const char *name, void *userdata) noexcept
        {
            SDL_SetWindowData(ptr, name, userdata);
        }

        void set_opacity(float opacity)
        {
            if (SDL_SetWindowOpacity(ptr, opacity))
            {
                throw except::SDL2_Error();
            }
        }

        void set_grab(bool grabbed) noexcept
        {
            SDL_SetWindowGrab(ptr, grabbed ? SDL_TRUE : SDL_FALSE);
        }

        void set_brightness(float brightness)
        {
            if (SDL_SetWindowBrightness(ptr, brightness))
            {
                throw except::SDL2_Error();
            }
        }

        void set_input_focus() noexcept
        {
            SDL_SetWindowInputFocus(ptr);
        }

        void show() noexcept
        {
            SDL_ShowWindow(ptr);
        }

        void hide() noexcept
        {
            SDL_HideWindow(ptr);
        }

        void maximize() noexcept
        {
            SDL_MaximizeWindow(ptr);
        }

        void minimize() noexcept
        {
            SDL_MinimizeWindow(ptr);
        }

        void restore() noexcept
        {
            SDL_RestoreWindow(ptr);
        }

        void raise() noexcept
        {
            SDL_RaiseWindow(ptr);
        }

        void update_surface() noexcept
        {
            SDL_UpdateWindowSurface(ptr);
        }

        void update_surface_rects(const std::vector<Rect> &rects) noexcept
        {
            SDL_UpdateWindowSurfaceRects(ptr, rects.data(), rects.size());
        }
    };

    inline std::unique_ptr<Window> make_window(SDL_Window *window)
    {
        return std::unique_ptr<Window>{new Window(window)};
    }
}

namespace sdl2
{
    using window::Window;
    using window::make_window;
}


#endif //SDL2_CPP_WINDOW_HPP
