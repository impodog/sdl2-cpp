//
// Created by impodog on 9/9/23.
//

#ifndef SDL2_CPP_KEYBOARD_HPP
#define SDL2_CPP_KEYBOARD_HPP

#include "event.hpp"

namespace sdl2::keyboard
{
    class KeyRecord
    {
        std::unordered_set<SDL_Keycode> down_keys, clicked_keys;
    public:
        KeyRecord() = default;

        void on_key_down(const SDL_KeyboardEvent &event)
        {
            down_keys.insert(event.keysym.sym);
            if (!event.repeat)
            {
                clicked_keys.insert(event.keysym.sym);
            }
        }

        void on_key_up(const SDL_KeyboardEvent &event)
        {
            down_keys.erase(event.keysym.sym);
        }

        void refresh()
        {
            clicked_keys.clear();
        }

        [[nodiscard]] bool is_down(SDL_Keycode key) const
        {
            return down_keys.contains(key);
        }

        [[nodiscard]] bool is_clicked(SDL_Keycode key) const
        {
            return clicked_keys.contains(key);
        }
    };
}

namespace sdl2
{
    using keyboard::KeyRecord;
}

#endif //SDL2_CPP_KEYBOARD_HPP
