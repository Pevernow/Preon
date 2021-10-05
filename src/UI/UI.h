#pragma once
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include "tinyxml2/tinyxml2.h"

class UI
{
public:
    UI(uint16_t screenWidth = 800, uint16_t screenHeight = 600);
    ~UI();
    void MainLoop();
    void ProcessDom(tinyxml2::XMLDocument *dom);
    static UI &GetInstance();

private:
    void DrawFrameBuffer();
    void ProcessDomElement(tinyxml2::XMLElement *element);
    void ProcessEvent();
    void *m_FrameBuffer;
    SDL_Window *m_SdlWindow;
    SDL_Renderer *m_SdlRenderer;
    SDL_Texture *m_SdlDisplay;
    SDL_Event m_SdlEvent;
    static UI m_Instance;
};