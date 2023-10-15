//
// Created by impodog on 9/9/23.
//

#ifndef SDL2_CPP_KEYBOARD_HPP
#define SDL2_CPP_KEYBOARD_HPP

#include "event.hpp"

namespace sdl2::keyboard
{
	inline SDL_Keycode get_modded_key(SDL_Keycode key, Uint16 mod)
	{
		if (mod & KMOD_SHIFT)
		{
			if (key >= SDLK_a && key <= SDLK_z)
			{
				return key - SDLK_a + 'A';
			}
			switch (key)
			{
				case SDLK_1:
					return '!';
				case SDLK_2:
					return '@';
				case SDLK_3:
					return '#';
				case SDLK_4:
					return '$';
				case SDLK_5:
					return '%';
				case SDLK_6:
					return '^';
				case SDLK_7:
					return '&';
				case SDLK_8:
					return '*';
				case SDLK_9:
					return '(';
				case SDLK_0:
					return ')';
				case SDLK_MINUS:
					return '_';
				case SDLK_EQUALS:
					return '+';
				case SDLK_LEFTBRACKET:
					return '{';
				case SDLK_RIGHTBRACKET:
					return '}';
				case SDLK_BACKSLASH:
					return '|';
				case SDLK_SEMICOLON:
					return ':';
				case SDLK_QUOTE:
					return '"';
				case SDLK_COMMA:
					return '<';
				case SDLK_PERIOD:
					return '>';
				case SDLK_SLASH:
					return '?';
				default:
					return key;
			}
		}
		else
		{
			return key;
		}
	}

	inline void push_keycode(std::string &str, SDL_Keycode key)
	{
		if (key & 0xFF80)
		{
			for (int i = 0; i < sizeof(SDL_Keycode); ++i)
			{
				str.push_back(static_cast<char>(key >> (i * 8)));
			}
		}
		else
		{
			str.push_back(static_cast<char>(key));
		}
	}

	class KeyRecord
	{
		std::unordered_set<SDL_Keycode> down_keys, clicked_keys;
		std::queue<SDL_Keycode> m_key_queue;
	public:
		KeyRecord() = default;

		void on_key_down(const SDL_KeyboardEvent &event)
		{
			down_keys.insert(event.keysym.sym);
			if (!event.repeat)
			{
				clicked_keys.insert(event.keysym.sym);
			}
			m_key_queue.push(get_modded_key(event.keysym.sym, event.keysym.mod));
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

		[[nodiscard]] SDL_Keycode get_next_key()
		{
			if (m_key_queue.empty())
			{
				return SDLK_UNKNOWN;
			}
			auto key = m_key_queue.front();
			m_key_queue.pop();
			return key;
		}
	};
}

namespace sdl2
{
	using keyboard::KeyRecord;
}

#endif //SDL2_CPP_KEYBOARD_HPP
