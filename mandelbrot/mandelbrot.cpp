#include "mandelbrot.h"

MandelBrot::MandelBrot(int size, int width, int height) : PaletteSize(size) , Width(width) , Height(height)
{
    //init palette
    for (int i = 0; i <= PaletteSize; ++i)
    {
      srand(time(NULL)); //random color
      palette[i][0] = i < 4 * PaletteSize / 3 ? i * 255 * 3 / (2 * PaletteSize) : 255;
      palette[i][1] = i < PaletteSize / 2 ? rand()%255 : (i - PaletteSize / 3) * 255 * 3 / (2 * PaletteSize);
      palette[i][2] = 0; //was 0
    }
}

MandelBrot::~MandelBrot()
{
    //dynamically deallocate
}

void MandelBrot::paint(SDL_Renderer* renderer)
{
    srand(time(NULL));
    for (int y = 0; y < Height; ++y)
        for (int x = 0; x < Width; ++x)
        {                                                                                                  //4
            std::complex<double> c(0.5 * (x - (Width - Height) / 2) / Height * 5.0 - 2.0, 0.5 * y / Height * 4.0 - 2.0);
            std::complex<double> z(0.0, 0.0);
            int cnt = 0;
            while (cnt < PaletteSize)
            {
                z = z * z + c;
                if (abs(z) > 2.0)
                break;
                ++cnt;
            }
        
            SDL_SetRenderDrawColor(renderer, palette[cnt][0], palette[cnt][1], palette[cnt][2], 0xff);
            SDL_RenderDrawPoint(renderer, x, y);
        }
}

const MandelBrot& MandelBrot::operator=(const MandelBrot& that)
{
        this->PaletteSize = that.PaletteSize;
        this->Width = that.Width;
        this->PaletteSize = that.PaletteSize;
}