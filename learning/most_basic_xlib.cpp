#include <X11/X.h>
#include <X11/Xlib.h>
#include <assert.h>
#include <unistd.h>

#include <cstdio>

int main() {
    Display *display;

    // Most functions will take display as an argument.
    // Let's understand why: Xlib follows a client-server
    // architecture. Display structure servers as connection
    // to the X server and contains all the information
    // about that X server. It uses TCP or DECnet protocols
    // depnding upon the system.
    display = XOpenDisplay(NULL);

    // The colors are depicted using integers.
    // But the colors can be different for different
    // machines. The only two guaranteed colors are
    // white and black which can be accessed like
    // below.
    int blackColor = BlackPixel(display, DefaultScreen(display));
    int whiteColor = WhitePixel(display, DefaultScreen(display));

    Window w = XCreateSimpleWindow(display, DefaultRootWindow(display), 0, 0,
                                   200, 100, 0, blackColor, blackColor);

    // With this line the server informs us of any
    // structural changes in the code. These structural
    // changes can be creating and mapping.
    XSelectInput(display, w, StructureNotifyMask);

    // This is an asynchronus call to the server
    // asking it to map our window. We wait for
    // MapNotify event. This is when the window
    // is mapped.
    XMapWindow(display, w);

    // X server is stateless. With Graphic Context we provide
    // the parameters about the window which do not
    // change for each drawing reaquest.
    GC gc = XCreateGC(display, w, 0, NULL);

    XSetForeground(display, gc, whiteColor);

    // This is a listener for the MapNotify event.
    for (;;) {
        XEvent e;
        XNextEvent(display, &e);
        if (e.type == MapNotify) {
            break;
        }
    }

    XDrawLine(display, w, gc, 10, 60, 180, 20);

    // XFlush sends the request from client to the
    // server. XNextEvent calls XFlush for other events
    // too.
    XFlush(display);
    getchar();
}
