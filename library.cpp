#include "sdl2-cpp/sdl2-cpp.h"
#include "image-cpp/image-cpp.h"
#include "ttf-cpp/ttf-cpp.h"

namespace sdl2::test
{
    int test_main()
    {
        sdl2::Window window("Hello World", 800, 600, SDL_WINDOW_RESIZABLE);
        sdl2::Renderer renderer(window);
        sdl2::Event event;
        sdl2::Ticker ticker;
        sdl2::KeyRecord key_record;

        renderer.set_logical_size(800, 600);

        auto img = std::unique_ptr<sdl2::Surface>{sdl2::load_png("test/test.png")};
        auto texture = img->convert(renderer);
        sdl2::Font font("arial.ttf", 24);
        bool quit = false;
        while (!quit)
        {
            event.poll();
            switch (event.get_type())
            {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    key_record.on_key_down(event->key);
                    break;
                case SDL_KEYUP:
                    key_record.on_key_up(event->key);
                    break;
                default:
                    break;
            }

            renderer.set_draw_color(sdl2::Color(0, 0, 0));
            renderer.clear();

            ticker.framerate(30);
            key_record.refresh();
            renderer.present();
        }
        return 0;
    }
}