[SDL_image库](http://www.libsdl.org/projects/SDL_image/)

[SDLAPI](https://wiki.libsdl.org/CategoryAPI)

[SDL文档教程](http://tjumyk.github.io/sdl-tutorial-cn/contents.html)

[SDL视频教程](https://www.bilibili.com/video/BV1rK411V7eu?p=9)

```c
// Headers
#include "SDL.h"
#include <SDL_image.h>
#include<stdbool.h>

// Main function
int main(int argc, char* argv[])
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
        return(1);
    
    SDL_Window* window = SDL_CreateWindow(u8"窗口", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);

    SDL_Renderer* render = SDL_CreateRenderer(window, -1, 0);
    SDL_Surface* surface =  IMG_Load(u8"千仞雪.jpg");
    SDL_Texture* texture = SDL_CreateTextureFromSurface(render, surface);

    SDL_RenderCopy(render, texture, NULL, NULL);

    SDL_RenderPresent(render);

    bool quit = false;
    SDL_Event ev;
    while (!quit)
    {
        SDL_WaitEvent(&ev);
        if (ev.type == SDL_QUIT)
        {
            quit = true;
        }
    }
    // Delay 2 seconds
    //SDL_Delay(5000);

    // 清理资源
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);

    // Quit SDL
    SDL_Quit();

    // Return
    return 0;
}
```

