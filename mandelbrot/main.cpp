#include <SDL2/SDL.h>
#include <iostream>
#include <complex>
#include <time.h>

#define PaletteSize 12 //32
enum { Width = 1280, Height = 720 };


void mandelbrot(int pal[PaletteSize+1][3])
  {
    for (int i = 0; i <= PaletteSize; ++i)
    {
      srand(time(NULL));
      pal[i][0] = i < 4 * PaletteSize / 3 ? i * 255 * 3 / (2 * PaletteSize) : 255;
      pal[i][1] = i < PaletteSize / 2 ? rand()%255 : (i - PaletteSize / 3) * 255 * 3 / (2 * PaletteSize);
      pal[i][2] = 0; //was 0
    }
  }

  void paint(SDL_Renderer *renderer)
  {
    srand(time(NULL));
    int palette[PaletteSize + 1][3];
    mandelbrot(palette); 
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

int main()
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    std::cerr << "SDL_Init(SDL_INIT_VIDEO)\n";
    return -1;
  }
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_CreateWindowAndRenderer(Width, Height, SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS, &window, &renderer);
  SDL_SetWindowPosition(window, 65, 126);

    for (int x = 0; x < 1; ++x)
    {                                                                                                  //4
      paint(renderer);
    }
//-------------
  SDL_RenderPresent(renderer);

  SDL_Event event;
  const Uint8* keystate;
  while ( true ) {
    keystate = SDL_GetKeyboardState(0);
    if (keystate[SDL_SCANCODE_ESCAPE]) { break; }
    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        break;
      }
    }
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return EXIT_SUCCESS;
}
