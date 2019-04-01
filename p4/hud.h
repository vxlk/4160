#include "viewport.h"

//fight me xiang
//it's technically a class
struct HUD final
{
    HUD() = default;
    HUD(HUD&) = default;
    HUD(HUD&&) = default;

    static void draw();
};