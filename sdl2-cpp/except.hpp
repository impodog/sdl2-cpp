//
// Created by impodog on 9/9/23.
//

#ifndef SDL2_CPP_EXCEPT_HPP
#define SDL2_CPP_EXCEPT_HPP

#include "../include.h"

namespace sdl2::except
{
    class SDL2_Error : public std::runtime_error
    {
    public:
        explicit SDL2_Error()
                : std::runtime_error(SDL_GetError())
        {}
    };
}

#endif //SDL2_CPP_EXCEPT_HPP
