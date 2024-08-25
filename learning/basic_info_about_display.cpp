#include <X11/Xlib.h>
#include <assert.h>
#include <unistd.h>

#include <iostream>

using namespace std;

int main() {
    Display *display;

    display = XOpenDisplay(NULL);
    assert(display);
    int screen_num;

    int screen_width;
    int screen_height;

    Window root_window;

    unsigned long white_pixel;
    unsigned long black_pixel;

    // This is the screen number if there are multiple
    // screens.
    screen_num = DefaultScreen(display);

    screen_width = DisplayWidth(display, screen_num);
    screen_height = DisplayHeight(display, screen_num);

    cout << "Screen num: " << screen_num << endl;
    cout << "Screen width: " << screen_width << endl;
    cout << "Screen height: " << screen_height << endl;
    root_window = RootWindow(display, screen_num);

    white_pixel = WhitePixel(display, screen_num);
    black_pixel = BlackPixel(display, screen_num);
        
    sleep(100000);
    XCloseDisplay(display);
}
