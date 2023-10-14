//
// Created by impodog on 9/10/23.
//

#ifndef SDL2_CPP_IMAGE_HPP
#define SDL2_CPP_IMAGE_HPP

#include "../include.h"
#include "../sdl2-cpp/sdl2-cpp.h"
#include "SDL2/SDL_image.h"

namespace sdl2
{
    inline std::unique_ptr<Surface> load_image(const char *file)
    {
        return make_surface(IMG_Load(file));
    }

    inline std::unique_ptr<Surface> load_bmp(const char *file)
    {
        return make_surface(SDL_LoadBMP(file));
    }

    inline std::unique_ptr<Surface> load_png(const char *file)
    {
        return make_surface(IMG_LoadPNG_RW(SDL_RWFromFile(file, "rb")));
    }

    inline std::unique_ptr<Surface> load_jpg(const char *file)
    {
        return make_surface(IMG_LoadJPG_RW(SDL_RWFromFile(file, "rb")));
    }

    inline std::unique_ptr<Surface> load_tif(const char *file)
    {
        return make_surface(IMG_LoadTIF_RW(SDL_RWFromFile(file, "rb")));
    }

    inline std::unique_ptr<Surface> load_xcf(const char *file)
    {
        return make_surface(IMG_LoadXCF_RW(SDL_RWFromFile(file, "rb")));
    }

    inline std::unique_ptr<Surface> load_xpm(const char *file)
    {
        return make_surface(IMG_LoadXPM_RW(SDL_RWFromFile(file, "rb")));
    }

    inline std::unique_ptr<Surface> load_webp(const char *file)
    {
        return make_surface(IMG_LoadWEBP_RW(SDL_RWFromFile(file, "rb")));
    }

    inline std::unique_ptr<Surface> load_ico(const char *file)
    {
        return make_surface(IMG_LoadICO_RW(SDL_RWFromFile(file, "rb")));
    }

    inline std::unique_ptr<Surface> load_cursor(const char *file)
    {
        return make_surface(IMG_LoadCUR_RW(SDL_RWFromFile(file, "rb")));
    }

    inline std::unique_ptr<Surface> load_gif(const char *file)
    {
        return make_surface(IMG_LoadGIF_RW(SDL_RWFromFile(file, "rb")));
    }

    inline std::unique_ptr<Surface> load_lbm(const char *file)
    {
        return make_surface(IMG_LoadLBM_RW(SDL_RWFromFile(file, "rb")));
    }

    inline std::unique_ptr<Surface> load_pcx(const char *file)
    {
        return make_surface(IMG_LoadPCX_RW(SDL_RWFromFile(file, "rb")));
    }

    inline std::unique_ptr<Surface> load_pnm(const char *file)
    {
        return make_surface(IMG_LoadPNM_RW(SDL_RWFromFile(file, "rb")));
    }

    inline std::unique_ptr<Surface> load_tga(const char *file)
    {
        return make_surface(IMG_LoadTGA_RW(SDL_RWFromFile(file, "rb")));
    }

    inline std::unique_ptr<Surface> load_svg(const char *file)
    {
        return make_surface(IMG_LoadSVG_RW(SDL_RWFromFile(file, "rb")));
    }

    inline void save_png(const char *file, std::unique_ptr<Surface> surface)
    {
        if (IMG_SavePNG(surface->get(), file))
        {
            throw except::SDL2_Error();
        }
    }

    inline void save_jpg(const char *file, std::unique_ptr<Surface> surface, int quality)
    {
        if (IMG_SaveJPG(surface->get(), file, quality))
        {
            throw except::SDL2_Error();
        }
    }
}

#endif //SDL2_CPP_IMAGE_HPP
