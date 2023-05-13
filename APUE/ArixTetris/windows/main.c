#include <SDL2/SDL.h>
#include <stdbool.h>
int main(int argc, char *args[])
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    // 创建一个窗口并指定窗口的大小和创建的窗口的位置
    SDL_Window *window = SDL_CreateWindow("My Window",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          640, 480, 0);

    if (!window)
    {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return 1;
    }

    // Create a renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    if (!renderer)
    {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return 1;
    }

    // Draw a rectangle
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Set color to red
    SDL_Rect rect = {50, 50, 200, 100};               // Create a rectangle
    SDL_RenderFillRect(renderer, &rect);              // Fill the rectangle with the current color

    // Update the screen
    SDL_RenderPresent(renderer);

    // Wait for a keypress
    bool quit = false;
    while (!quit)
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_UP:
                case SDLK_w:
                    // 处理向上移动的操作
                    rect.y -= 10;
                    break;
                case SDLK_DOWN:
                case SDLK_s:
                    // 处理向下移动的操作
                    rect.y += 10;
                    break;
                case SDLK_LEFT:
                case SDLK_a:
                    // 处理向左移动的操作
                    rect.x -= 10;
                    break;
                case SDLK_RIGHT:
                case SDLK_d:
                    // 处理向右移动的操作
                    rect.x += 10;
                    break;
                default:
                    break;
                }
                break;
            default:
                break;
            }
        }
            // 清空屏幕
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // 绘制方块
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &rect);

        // 更新屏幕显示
        SDL_RenderPresent(renderer);

        // 延时一定时间，控制移动速度
        SDL_Delay(100);

    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
