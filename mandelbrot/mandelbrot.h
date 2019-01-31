#include "frameGenerator.h"
#include <complex>
#include <time.h>
#define PALETTE_COLS 3

class MandelBrot
{
    int Width = 0;
    int Height = 0;
    int PaletteSize = 12;
    //dynamically allocate this in constructor
    //int palette[PaletteSize + 1][PALETTE_COLS];
    int **palette;
public:
    //dont need so get rid
    MandelBrot() = delete;

    MandelBrot(int size, int width, int height);
   
    void paint(SDL_Renderer* renderer);
    const MandelBrot& operator=(const MandelBrot& that);
    MandelBrot(const MandelBrot& rhs);
    ~MandelBrot();
};