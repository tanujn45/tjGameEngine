#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define WIN_SIZE 600

int main() {
    Display *display;
    Window win;
    GC gc;
    int x = 0, y = 0;
    float speed = 0;

    display = XOpenDisplay(NULL);

    win = XCreateSimpleWindow(display, RootWindow(display, 0), 0, 0, WIN_SIZE,
                              WIN_SIZE / 2, 0, 0x000000, 0xFFFFFF);
    XStoreName(display, win, "Car Animation");
    gc = XCreateGC(display, win, 0, NULL);
    XMapWindow(display, win);
    int pixelSize = 2;
    while (1) {
        XSetForeground(display, gc, 0x969696);
        XFillRectangle(display, win, gc, x, y, pixelSize, pixelSize);
        x += pixelSize;
        if (x + pixelSize > WIN_SIZE) {
            x = 0;
            y += pixelSize;
        }
        if (y + pixelSize > WIN_SIZE / 2) {
            break;
        }
        XFlush(display);
    }
    getchar();
    // Clean up and close the window
    XFreeGC(display, gc);
    XUnmapWindow(display, win);
    XDestroyWindow(display, win);
    XCloseDisplay(display);
}
