#include "tjGameEngine.h"

#include <cstdlib>

using namespace std;

tjGameEngine::tjGameEngine() {
}

tjGameEngine::~tjGameEngine() {
}

void tjGameEngine::createWindow(int width, int height, int pixelWidth,
                                int pixelHeight) {
    display = XOpenDisplay(NULL);
    if (!display) {
        cerr << "Cannot open display\n";
        exit(EXIT_FAILURE);
    }
    viewportWidth = width * pixelWidth;
    viewportHeight = height * pixelHeight;

    // These variables are just for checking
    // if the window we are trying to create is
    // fits inside our display.
    int screen = DefaultScreen(display);
    rootWin = RootWindow(display, screen);
    int rootX, rootY;
    uint32_t rootWidth, rootHeight;
    uint32_t rootBorderWidth, depth;
    XGetGeometry(display, rootWin, &rootWin, &rootX, &rootY, &rootWidth,
                 &rootHeight, &rootBorderWidth, &depth);

    cout << "Root window width " << rootWidth << endl;
    cout << "Root window height " << rootHeight << endl;

    cout << "viewport window width " << viewportWidth << endl;
    cout << "viewport window height " << viewportHeight << endl;

    if (rootWidth < viewportWidth || rootHeight < viewportHeight) {
        cerr << "Desired dimensions do not fit the screen\n";
        exit(EXIT_FAILURE);
    }

    win = XCreateSimpleWindow(display, RootWindow(display, 0), 0, 0,
                              viewportWidth, viewportHeight, 0, 0x000000,
                              0xFFFFFF);

    this->pixelWidth = pixelWidth;
    this->pixelHeight = pixelHeight;

    XStoreName(display, win, "tjGameEngine");
    gc = XCreateGC(display, win, 0, NULL);
    XMapWindow(display, win);
}

void tjGameEngine::destroyWindow() {
    XFreeGC(display, gc);
    XUnmapWindow(display, win);
    XDestroyWindow(display, win);
    XCloseDisplay(display);
}

uint32_t tjGameEngine::rgb(uint8_t r, uint8_t g, uint8_t b) {
    return r | (g << 8) | (b << 16) | (0xFF << 24);
}

void tjGameEngine::drawPixel(uint x, uint y, uint32_t color) {
    XSetForeground(display, gc, color);
    XFillRectangle(display, win, gc, x * pixelWidth, y * pixelHeight,
                   pixelWidth, pixelHeight);
}

void tjGameEngine::redraw(uint32_t color) {
    XSetForeground(display, gc, color);
    XFillRectangle(display, win, gc, 0, 0, viewportWidth, viewportHeight);
}

uint32_t tjGameEngine::getWindowWidth() {
    return viewportWidth;
}

uint32_t tjGameEngine::getWindowHeight() {
    return viewportHeight;
}
