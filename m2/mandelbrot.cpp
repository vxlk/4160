#include "mandelbrot.h"

Mandelbrot::~Mandelbrot()
{
        //dynamically deallocate
    for (int i = 0; i < PaletteCols; i++) {
        delete[] palette[i];
    }
    delete[] palette;
}

void Mandelbrot::init(int width, int height, int sz, int cls)
{
    Width = width; 
    Height = height;
    PaletteSize = sz;
    PaletteCols = cls;

    //dynamic allocation
    palette = new int*[PaletteSize+1];
    for(int i = 0; i <= PaletteSize; ++i)
        palette[i] = new int[PaletteCols];
    
    //init palette
    for (int i = 0; i <= PaletteSize; ++i)
    {
        palette[i][0] = i < 2 * PaletteSize / 3 ? i * 255 * 3 / (2 * PaletteSize) : 255;
        palette[i][1] = i < PaletteSize / 3 ? 0 : (i - PaletteSize / 3) * 255 * 3 / (2 * PaletteSize);
        palette[i][2] = 0;
    }
   
}

void Mandelbrot::paint(SDL_Renderer* renderer) 
{
    //random color in middle
    srand(time(NULL));
    for (int y = 0; y < Height; ++y)
        for (int x = 0; x < Width; ++x)
        {                              
                                                                            //4
            std::complex<double> c(0.5 * (x - (Width - Height) / 2) / Height * 5.0 - 2.0, 0.5 * y / Height * 4.0 - 2.0);
            std::complex<double> z(0.0, 0.0);
            int i = 0;
            while (i < PaletteSize)
            {
                z = z * z + c;
                if (abs(z) > 2.0) break;
                ++i;
            }
            if (!palette[i][0] && !palette[i][1] && !palette[i][2])
                SDL_SetRenderDrawColor(renderer, palette[i][0], palette[i][1], palette[i][2], SDL_ALPHA_TRANSPARENT);
            
            else
                SDL_SetRenderDrawColor(renderer, palette[i][0], palette[i][1], palette[i][2], SDL_ALPHA_OPAQUE);
            SDL_RenderDrawPoint(renderer, x, y);
        }
}

void Mandelbrot::paintFromPos(SDL_Renderer* renderer, int _x, int _y)
{
    //random color in middle
    srand(time(NULL));
    for (int y = _y; y < Height; ++y)
        for (int x = _x; x < Width; ++x)
        {                              
                                                                            //4
            std::complex<double> c(0.5 * (x - (Width - Height) / 2) / Height * 5.0 - 2.0, 0.5 * y / Height * 4.0 - 2.0);
            std::complex<double> z(0.0, 0.0);
            int i = 0;
            while (i < PaletteSize)
            {
                z = z * z + c;
                if (abs(z) > 2.0) break;
                ++i;
            }
            if (!palette[i][0] && !palette[i][1] && !palette[i][2])
                SDL_SetRenderDrawColor(renderer, palette[i][0], palette[i][1], palette[i][2], 0);
            else
            SDL_SetRenderDrawColor(renderer, palette[i][0], palette[i][1], palette[i][2], 255);
            SDL_RenderDrawPoint(renderer, x, y);
        }
}

const Mandelbrot& Mandelbrot::operator=(const Mandelbrot& that)
{
    this->init(that.Width, 
               that.Height, 
               that.PaletteSize, 
               that.PaletteCols);
    return *this;
}

Mandelbrot::Mandelbrot(const Mandelbrot& that) : palette(nullptr)
{
    this->init(that.Width, 
               that.Height, 
               that.PaletteSize, 
               that.PaletteCols);
}