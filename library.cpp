#include "sdl2-cpp/sdl2-cpp.h"

int main()
{
    sdl2::Rect r(1, 2, 3, 4);
    r += {1, 2};
    std::cout << r << std::endl;
    return 0;
}
