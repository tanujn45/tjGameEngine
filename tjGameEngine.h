#pragma once

#include <X11/Xlib.h>
#include <sys/types.h>

#include <cstdint>
#include <iostream>
#include <string>

using namespace std;

class tjGameEngine {
   private:
    Display *display;
    Window rootWin;
    Window win;
    GC gc;

    uint32_t viewportWidth;
    uint32_t viewportHeight;
    uint32_t pixelWidth;
    uint32_t pixelHeight;

   public:
    tjGameEngine();
    ~tjGameEngine();

    void createWindow(int width, int height, int pixelWidth, int pixelHeight);
    void setWindowName(string name);

    void updateWindow();
    void destroyWindow();

    void drawPixel(uint x, uint y, uint32_t color);

    uint32_t getWindowWidth();
    uint32_t getWindowHeight();

   public:
    // Helper functions
    uint32_t rgb(uint8_t r, uint8_t g, uint8_t b);
    void redraw(uint32_t color);
};

/*
 * This is what I am going to do with this library
 *   - Generate a window
 *   - Set it's width and height
 *   - Define pixel width and height
 *   - Check for user input
 *       - this can be keyboard input or mouse input
 *   - Redraw the window
 *   - Destroy the window
 */
