#include "UI.h"
#define GUILITE_ON
#include "GuiLite/GuiLite.h"
#include "CompileConfig.h"
#include <SDL2/SDL_syswm.h>

c_surface *g_GuiLiteSurface;
c_display *g_GuiLiteDisplay;

UI UI::m_Instance;

const uint8_t COLOR_BYTES = 4; //equals to 32bits

UI::UI(uint16_t screenWidth, uint16_t screenHeight)
{
    SDL_SetMainReady();
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        ; //TODO: Error process
    };

    m_SdlWindow = SDL_CreateWindow(PREON_VERSION, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
    if (m_SdlWindow == nullptr)
    {
        ; //TODO: Error process
    }

    /*
    SDL_SysWMinfo wmi;
    SDL_VERSION(&wmi.version);
    if (!SDL_GetWindowWMInfo(m_SdlWindow, &wmi))
    {
        ; //TODO: Error process
    }
    void *windowHandle = nullptr;

#if SDL_VIDEO_DRIVER_WINDOWS
    windowHandle = wmi.info.win.window;
#endif
#if SDL_VIDEO_DRIVER_X11
    windowHandle = wmi.info.
#endif
#if SDL_VIDEO_DRIVER_WINDOW
    windowHandle = wmi.info.win.window;
#endif
*/
    //创建Renderer
    m_SdlRenderer = SDL_CreateRenderer(m_SdlWindow, -1, 0);
    if (NULL == m_SdlRenderer)
    {
        ; //TODO: process error
    }
    //设置Renderer画笔颜色，透明度(此时透明度不会生效，因为没有设置BlendMode)
    SDL_SetRenderDrawColor(m_SdlRenderer, 0, 255, 0, 255);
    m_FrameBuffer = new uint32_t[screenWidth * screenHeight * COLOR_BYTES];
    g_GuiLiteSurface = new c_surface(screenWidth, screenHeight, COLOR_BYTES);
    g_GuiLiteDisplay = new c_display(m_FrameBuffer, screenWidth, screenHeight, g_GuiLiteSurface);
    SDL_CreateTexture(m_SdlRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, screenWidth, screenHeight);
    SDL_LockTexture(m_SdlDisplay, NULL, &m_FrameBuffer, 0);
}

UI::~UI()
{
    SDL_DestroyRenderer(m_SdlRenderer);
    SDL_DestroyTexture(m_SdlDisplay);
    SDL_DestroyWindow(m_SdlWindow);
    delete g_GuiLiteDisplay;
    delete g_GuiLiteSurface;
    delete[] m_FrameBuffer;
    SDL_Quit();
}

void UI::MainLoop()
{
    while (1)
    {
        ProcessEvent();
        DrawFrameBuffer();
        SDL_Delay(20);
    }
}

void UI::ProcessEvent()
{
    while (SDL_PollEvent(&m_SdlEvent))
    {
        switch (m_SdlEvent.type)
        {
        case SDL_QUIT:
        {
            SDL_Quit();
            break;
        }
        default:
            break;
        }
    }
}

void UI::DrawFrameBuffer()
{
    SDL_RenderClear(m_SdlRenderer);
    SDL_Rect textureRect;
    textureRect.x = 0;
    textureRect.y = 0;
    textureRect.w = 800;
    textureRect.h = 600;
    SDL_RenderCopy(m_SdlRenderer, m_SdlDisplay, NULL, &textureRect);
    SDL_RenderPresent(m_SdlRenderer);
}

UI &UI::GetInstance()
{
    return m_Instance;
}
