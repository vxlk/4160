#include "frameGenerator.h"
#include <complex>
#include <time.h>
#include <iostream>

class Mandelbrot
{

    int Width = 0;
    int Height = 0;
    int PaletteSize = 0;
    int PaletteCols = 0;
    int **palette;
    
public:

    Mandelbrot() : palette(nullptr) {}

    //rule of 3
    ~Mandelbrot();
    Mandelbrot(const Mandelbrot& that);
    const Mandelbrot& operator=(const Mandelbrot& that);

    void init(int width, int height, int sz, int cls);

    void paint(SDL_Renderer* renderer);
    void paintFromPos(SDL_Renderer* renderer, int _x, int _y);
};