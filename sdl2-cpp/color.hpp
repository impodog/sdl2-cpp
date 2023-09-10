//
// Created by impodog on 9/9/23.
//

#ifndef SDL2_CPP_COLOR_HPP
#define SDL2_CPP_COLOR_HPP

#include "utility.hpp"

namespace sdl2::color
{
    class Color : public SDL_Color
    {
    public:
        Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255)
                : SDL_Color{r, g, b, a}
        {}

        void dim(double factor)
        {
            factor = std::clamp(factor, 0.0, std::max({r, g, b}) / 255.0);
            r = static_cast<Uint8>(r * factor);
            g = static_cast<Uint8>(g * factor);
            b = static_cast<Uint8>(b * factor);
        }
    };
}

namespace sdl2
{
    using color::Color;
}

#endif //SDL2_CPP_COLOR_HPP
