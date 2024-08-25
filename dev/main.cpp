// What I want from this library
//
// # initScreen(width, height)
// This function makes a screen of the provided width and height
// This function can be overloaded to set a background color and
// size of the pixel that we want
//
// # DrawPixel on the screen using x and y value. along with the offset
#include <X11/Xlib.h>
#include <unistd.h>

#include <cstdio>

#define WIN_SIZE 1000

using namespace std;

int main() {
    Display* display;
    display = XOpenDisplay(NULL);

    Window w = XCreateSimpleWindow(display, RootWindow(display, 0), 0, 0,
                                   WIN_SIZE, WIN_SIZE, 0, 0x000000, 0xFFFFFF);

    XStoreName(display, w, "Test lib");
    GC gc = XCreateGC(display, w, 0, NULL);
    XMapWindow(display, w);
    int x = 0, y = 0;
    int pixelWidth = 10;
    int pixelHeight = 10;
    int pixelSize = 10;
    while (1) {
        XSetForeground(display, gc, 0x000000);
        XFillRectangle(display, w, gc, x, y, pixelWidth, pixelHeight);
        x += pixelSize;
        if (x > WIN_SIZE) {
            x = 0;
            y += pixelSize;
        }
        if (y > WIN_SIZE) {
            break;
        }
        XFlush(display);
        usleep(1000);
    }
    getchar();

    XFreeGC(display, gc);
    XUnmapWindow(display, w);
    XDestroyWindow(display, w);
    XCloseDisplay(display);
}
