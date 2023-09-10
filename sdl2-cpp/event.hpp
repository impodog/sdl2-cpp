//
// Created by impodog on 9/9/23.
//

#ifndef SDL2_CPP_EVENT_HPP
#define SDL2_CPP_EVENT_HPP

#include "utility.hpp"

namespace sdl2::event
{
    class Event
    {
        SDL_Event *event;
    public:
        Event()
                : event(new SDL_Event)
        {}

        ~Event()
        {
            delete event;
        }

        Event(const Event &) = delete;

        Event &operator=(const Event &) = delete;

        [[nodiscard]] SDL_Event *get() const noexcept
        {
            return event;
        }

        SDL_Event *operator->() const noexcept
        {
            return event;
        }

        bool poll() noexcept
        {
            return SDL_PollEvent(event);
        }

        void wait()
        {
            if (!SDL_WaitEvent(event))
            {
                throw except::SDL2_Error();
            }
        }

        void wait_timeout(int timeout)
        {
            if (!SDL_WaitEventTimeout(event, timeout))
            {
                throw except::SDL2_Error();
            }
        }

        [[nodiscard]] Uint32 get_type() const noexcept
        {
            return event->type;
        }
    };

    void push_event(SDL_Event *event)
    {
        if (SDL_PushEvent(event))
        {
            throw except::SDL2_Error();
        }
    }

    using std::chrono::system_clock;

    class Ticker
    {
        system_clock::time_point prev;

    public:
        Ticker() = default;

        void reset()
        {
            prev = system_clock::now();
        }

        [[nodiscard]] long long elapsed()
        {
            auto result = std::chrono::duration_cast<std::chrono::milliseconds>(system_clock::now() - prev).count();
            reset();
            return result;
        }

        long long delay(long long ms)
        {
            auto elapsed = this->elapsed();
            if (elapsed < ms)
            {
                SDL_Delay(ms - elapsed);
                return ms;
            }
            return elapsed;
        }

        double framerate(double framerate)
        {
            auto delay = this->delay(utility::framerate_to_delay(framerate));
            return utility::delay_to_framerate(delay);
        }
    };
}

namespace sdl2
{
    using event::Event;
    using event::push_event;
    using event::Ticker;
}

#endif //SDL2_CPP_EVENT_HPP
