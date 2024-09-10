#pragma once

#include <X11/X.h>
#include <X11/XKBlib.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <sys/types.h>

#include <atomic>
#include <cstdint>
#include <iostream>
#include <map>
#include <string>
#include <thread>

using namespace std;

struct Button {
    bool isPressed;
    bool isReleased;
    bool isHeld;
};

class tjGameEngine {
   private:
    Display* display;
    Window rootWin;
    Window win;
    GC gc;

    atomic<bool> threadActive;
    uint32_t viewportWidth;
    uint32_t viewportHeight;
    uint32_t pixelWidth;
    uint32_t pixelHeight;

    uint32_t rootWidth;
    uint32_t rootHeight;

   public:
    enum Key {
        NONE,
        // Alph
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,
        // Num
        K0,
        K1,
        K2,
        K3,
        K4,
        K5,
        K6,
        K7,
        K8,
        K9,
        // Fn keys
        F1,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        F8,
        F9,
        F10,
        F11,
        F12,
        // Direction
        // keys
        UP,
        DOWN,
        LEFT,
        RIGHT,
        // Others
        SPACE,
        TAB,
        SHIFT,
        CTRL,
        ALT,
        INS,
        DEL,
        HOME,
        END,
        PGUP,
        PGDN,
        BACK,
        ESCAPE,
        RETURN,
        ENTER,
        PAUSE,
        SCROLL,
        // Numpad
        // Num keys
        NP0,
        NP1,
        NP2,
        NP3,
        NP4,
        NP5,
        NP6,
        NP7,
        NP8,
        NP9,
        // Numpad
        // others
        NP_MUL,
        NP_DIV,
        NP_ADD,
        NP_SUB,
        NP_DECIMAL,
        PERIOD,
        EQUALS,
        COMMA,
        MINUS,
        // All
        // others
        OEM_1,
        OEM_2,
        OEM_3,
        OEM_4,
        OEM_5,
        OEM_6,
        OEM_7,
        OEM_8,
        CAPS_LOCK,
        ENUM_END
    };

    map<Key, KeySym> keyToX11 = {
        // Alphabet
        // keys (use
        // lowercase
        // keysyms
        // for both
        // cases)
        {Key::A, XK_a},
        {Key::B, XK_b},
        {Key::C, XK_c},
        {Key::D, XK_d},
        {Key::E, XK_e},
        {Key::F, XK_f},
        {Key::G, XK_g},
        {Key::H, XK_h},
        {Key::I, XK_i},
        {Key::J, XK_j},
        {Key::K, XK_k},
        {Key::L, XK_l},
        {Key::M, XK_m},
        {Key::N, XK_n},
        {Key::O, XK_o},
        {Key::P, XK_p},
        {Key::Q, XK_q},
        {Key::R, XK_r},
        {Key::S, XK_s},
        {Key::T, XK_t},
        {Key::U, XK_u},
        {Key::V, XK_v},
        {Key::W, XK_w},
        {Key::X, XK_x},
        {Key::Y, XK_y},
        {Key::Z, XK_z},

        // Numeric
        // keys
        {Key::K0, XK_0},
        {Key::K1, XK_1},
        {Key::K2, XK_2},
        {Key::K3, XK_3},
        {Key::K4, XK_4},
        {Key::K5, XK_5},
        {Key::K6, XK_6},
        {Key::K7, XK_7},
        {Key::K8, XK_8},
        {Key::K9, XK_9},

        // Function
        // keys
        {Key::F1, XK_F1},
        {Key::F2, XK_F2},
        {Key::F3, XK_F3},
        {Key::F4, XK_F4},
        {Key::F5, XK_F5},
        {Key::F6, XK_F6},
        {Key::F7, XK_F7},
        {Key::F8, XK_F8},
        {Key::F9, XK_F9},
        {Key::F10, XK_F10},
        {Key::F11, XK_F11},
        {Key::F12, XK_F12},

        // Arrow
        // keys
        {Key::LEFT, XK_Left},
        {Key::RIGHT, XK_Right},
        {Key::UP, XK_Up},
        {Key::DOWN, XK_Down},

        // Special
        // keys
        {Key::ESCAPE, XK_Escape},
        {Key::SPACE, XK_space},
        {Key::TAB, XK_Tab},
        {Key::SHIFT, XK_Shift_L},
        {Key::CTRL, XK_Control_L},
        {Key::ENTER, XK_Return},
        {Key::BACK, XK_BackSpace},
        {Key::DEL, XK_Delete},
        {Key::HOME, XK_Home},
        {Key::END, XK_End},
        {Key::PGUP, XK_Page_Up},
        {Key::PGDN, XK_Page_Down},
        {Key::INS, XK_Insert},
        {Key::CAPS_LOCK, XK_Caps_Lock},

        // Numpad
        // keys
        {Key::NP0, XK_KP_0},
        {Key::NP1, XK_KP_1},
        {Key::NP2, XK_KP_2},
        {Key::NP3, XK_KP_3},
        {Key::NP4, XK_KP_4},
        {Key::NP5, XK_KP_5},
        {Key::NP6, XK_KP_6},
        {Key::NP7, XK_KP_7},
        {Key::NP8, XK_KP_8},
        {Key::NP9, XK_KP_9},
        {Key::NP_MUL, XK_KP_Multiply},
        {Key::NP_DIV, XK_KP_Divide},
        {Key::NP_ADD, XK_KP_Add},
        {Key::NP_SUB, XK_KP_Subtract},
        {Key::NP_DECIMAL, XK_KP_Decimal},

        // Punctuation
        // and
        // special
        // characters
        {Key::PERIOD, XK_period},
        {Key::COMMA, XK_comma},
        {Key::MINUS, XK_minus},
        {Key::EQUALS, XK_equal},
        {Key::OEM_1, XK_semicolon},
        {Key::OEM_2, XK_slash},
        {Key::OEM_3, XK_grave},
        {Key::OEM_4, XK_bracketleft},
        {Key::OEM_5, XK_backslash},
        {Key::OEM_6, XK_bracketright},
        {Key::OEM_7, XK_apostrophe},

        // Modifier
        // keys
        {Key::SHIFT, XK_Shift_L},
        {Key::CTRL, XK_Control_L},
        {Key::ALT, XK_Alt_L},
        {Key::PAUSE, XK_Pause},
        {Key::SCROLL, XK_Scroll_Lock},

        // Additional
        // keys
        {Key::ESCAPE, XK_Escape},
        {Key::SPACE, XK_space},
        {Key::ENTER, XK_Return},
        {Key::BACK, XK_BackSpace},
        {Key::DEL, XK_Delete},
        {Key::HOME, XK_Home},
        {Key::END, XK_End},
        {Key::PGUP, XK_Page_Up},
        {Key::PGDN, XK_Page_Down},
        {Key::INS, XK_Insert},
        {Key::CAPS_LOCK, XK_Caps_Lock}};

    map<KeySym, Key> X11ToKey = {
        // Alphabet
        // keys (use
        // lowercase
        // keysyms
        // for both
        // cases)
        {XK_a, Key::A},
        {XK_b, Key::B},
        {XK_c, Key::C},
        {XK_d, Key::D},
        {XK_e, Key::E},
        {XK_f, Key::F},
        {XK_g, Key::G},
        {XK_h, Key::H},
        {XK_i, Key::I},
        {XK_j, Key::J},
        {XK_k, Key::K},
        {XK_l, Key::L},
        {XK_m, Key::M},
        {XK_n, Key::N},
        {XK_o, Key::O},
        {XK_p, Key::P},
        {XK_q, Key::Q},
        {XK_r, Key::R},
        {XK_s, Key::S},
        {XK_t, Key::T},
        {XK_u, Key::U},
        {XK_v, Key::V},
        {XK_w, Key::W},
        {XK_x, Key::X},
        {XK_y, Key::Y},
        {XK_z, Key::Z},

        // Numeric
        // keys
        {XK_0, Key::K0},
        {XK_1, Key::K1},
        {XK_2, Key::K2},
        {XK_3, Key::K3},
        {XK_4, Key::K4},
        {XK_5, Key::K5},
        {XK_6, Key::K6},
        {XK_7, Key::K7},
        {XK_8, Key::K8},
        {XK_9, Key::K9},

        // Function
        // keys
        {XK_F1, Key::F1},
        {XK_F2, Key::F2},
        {XK_F3, Key::F3},
        {XK_F4, Key::F4},
        {XK_F5, Key::F5},
        {XK_F6, Key::F6},
        {XK_F7, Key::F7},
        {XK_F8, Key::F8},
        {XK_F9, Key::F9},
        {XK_F10, Key::F10},
        {XK_F11, Key::F11},
        {XK_F12, Key::F12},

        // Arrow
        // keys
        {XK_Left, Key::LEFT},
        {XK_Right, Key::RIGHT},
        {XK_Up, Key::UP},
        {XK_Down, Key::DOWN},

        // Special
        // keys
        {XK_Escape, Key::ESCAPE},
        {XK_space, Key::SPACE},
        {XK_Tab, Key::TAB},
        {XK_Shift_L, Key::SHIFT},
        {XK_Control_L, Key::CTRL},
        {XK_Return, Key::ENTER},
        {XK_BackSpace, Key::BACK},
        {XK_Delete, Key::DEL},
        {XK_Home, Key::HOME},
        {XK_End, Key::END},
        {XK_Page_Up, Key::PGUP},
        {XK_Page_Down, Key::PGDN},
        {XK_Insert, Key::INS},
        {XK_Caps_Lock, Key::CAPS_LOCK},

        // Numpad
        // keys
        {XK_KP_0, Key::NP0},
        {XK_KP_1, Key::NP1},
        {XK_KP_2, Key::NP2},
        {XK_KP_3, Key::NP3},
        {XK_KP_4, Key::NP4},
        {XK_KP_5, Key::NP5},
        {XK_KP_6, Key::NP6},
        {XK_KP_7, Key::NP7},
        {XK_KP_8, Key::NP8},
        {XK_KP_9, Key::NP9},
        {XK_KP_Multiply, Key::NP_MUL},
        {XK_KP_Divide, Key::NP_DIV},
        {XK_KP_Add, Key::NP_ADD},
        {XK_KP_Subtract, Key::NP_SUB},
        {XK_KP_Decimal, Key::NP_DECIMAL},

        // Punctuation
        // and
        // special
        // characters
        {XK_period, Key::PERIOD},
        {XK_comma, Key::COMMA},
        {XK_minus, Key::MINUS},
        {XK_equal, Key::EQUALS},
        {XK_semicolon, Key::OEM_1},
        {XK_slash, Key::OEM_2},
        {XK_grave, Key::OEM_3},
        {XK_bracketleft, Key::OEM_4},
        {XK_backslash, Key::OEM_5},
        {XK_bracketright, Key::OEM_6},
        {XK_apostrophe, Key::OEM_7},

        // Modifier
        // keys
        {XK_Shift_L, Key::SHIFT},
        {XK_Control_L, Key::CTRL},
        {XK_Alt_L, Key::ALT},
        {XK_Pause, Key::PAUSE},
        {XK_Scroll_Lock, Key::SCROLL},

        // Additional
        // keys
        {XK_Escape, Key::ESCAPE},
        {XK_space, Key::SPACE},
        {XK_Return, Key::ENTER},
        {XK_BackSpace, Key::BACK},
        {XK_Delete, Key::DEL},
        {XK_Home, Key::HOME},
        {XK_End, Key::END},
        {XK_Page_Up, Key::PGUP},
        {XK_Page_Down, Key::PGDN},
        {XK_Insert, Key::INS},
        {XK_Caps_Lock, Key::CAPS_LOCK}};

   public:
    map<Key, Button> mapKeySym;
    map<KeySym, bool> keyRepeatTracker;
    Button mouse;
    Button keyboard[256] = {false};

    long eventMask;

    void setMapKeySym();
    void updateKeyState(KeySym sym, bool flag);

    virtual bool Create();
    virtual bool Update();
    virtual bool Destroy();

   public:
    tjGameEngine();
    ~tjGameEngine();

    void Construct(int width, int height, int pixelWidth, int pixelHeight);
    void Start();

   public:
    void createWindow();
    void setWindowName(string name);

    void updateWindow();
    void destroyWindow();

   public:
    void DrawPixel(uint x, uint y, uint32_t color);

    uint32_t getWindowWidth();
    uint32_t getWindowHeight();

    void handleEvents();

   public:
    // Helper
    // functions
    uint32_t rgb(uint8_t r, uint8_t g, uint8_t b);
    void Clear(uint32_t color);
};

inline tjGameEngine::tjGameEngine() {
}

inline tjGameEngine::~tjGameEngine() {
}

inline void tjGameEngine::Construct(int width, int height, int pixelWidth, int pixelHeight) {
    this->pixelWidth = pixelWidth;
    this->pixelHeight = pixelHeight;
    this->viewportWidth = width * pixelWidth;
    this->viewportHeight = height * pixelHeight;
}

inline void tjGameEngine::Start() {
    // Construct the window
    createWindow();
    threadActive = true;
    thread t = thread(&tjGameEngine::updateWindow, this);

    t.join();
    // Destroy everything, mhahahaha!!!
    destroyWindow();
}

inline void tjGameEngine::createWindow() {
    // Allow threads
    XInitThreads();

    // Open a connection to the X Server
    display = XOpenDisplay(NULL);
    if (!display) {
        cerr << "Cannot open display\n";
        exit(EXIT_FAILURE);
    }

    int screen = DefaultScreen(display);

    // Get the dimensions of the montitor
    // and check if the window will fit inside
    rootWin = RootWindow(display, screen);
    int rootX, rootY;
    uint32_t rootBorderWidth, depth;
    XGetGeometry(display, rootWin, &rootWin, &rootX, &rootY, &rootWidth, &rootHeight, &rootBorderWidth, &depth);

    /*cout << "Root window width " << rootWidth << endl;*/
    /*cout << "Root window height " << rootHeight << endl;*/
    /**/
    /*cout << "viewport window width " << viewportWidth << endl;*/
    /*cout << "viewport window height " << viewportHeight << endl;*/
    /**/
    /*cout << "rootX " << rootX << endl;*/
    /*cout << "rootY " << rootY << endl;*/

    if (rootWidth < viewportWidth || rootHeight < viewportHeight) {
        cerr << "Desired dimensions do not fit the screen\n";
        exit(EXIT_FAILURE);
    }

    // Create a window
    win = XCreateSimpleWindow(display, RootWindow(display, 0), 0, 0, viewportWidth, viewportHeight, 0, 0x000000,
                              0xFFFFFF);

    // Set name of the window
    XStoreName(display, win, "tjGameEngine");
    gc = XCreateGC(display, win, 0, NULL);
    XMapWindow(display, win);

    // Events that will be read;
    eventMask = KeyPressMask | KeyReleaseMask;
    XSelectInput(display, win, eventMask);

    Bool supported;
    if (XkbSetDetectableAutoRepeat(display, true, &supported)) {
        if (supported) {
            cout << "Auto detect supported" << endl << flush;
        } else {
            cout << "Auto detect not supported" << endl << flush;
        }
    } else {
        cout << "Auto detect is not set" << endl << flush;
    }

    /*XAutoRepeatOff(display);*/
}

inline void tjGameEngine::destroyWindow() {
    /*XAutoRepeatOn(display);*/
    XFreeGC(display, gc);
    XUnmapWindow(display, win);
    XDestroyWindow(display, win);
    XCloseDisplay(display);
}

inline void tjGameEngine::updateWindow() {
    bool created = Create();
    if (!created) {
        threadActive = false;
    }

    while (threadActive) {
        bool ifUpdated = Update();
        if (!ifUpdated) {
            threadActive = false;
        }
        handleEvents();
        if (!tjGameEngine::Destroy()) {
            threadActive = true;
        }
    }
}

inline bool tjGameEngine::Create() {
    return false;
}

inline bool tjGameEngine::Update() {
    return false;
}

inline bool tjGameEngine::Destroy() {
    return true;
}

inline uint32_t tjGameEngine::rgb(uint8_t r, uint8_t g, uint8_t b) {
    return r | (g << 8) | (b << 16) | (0xFF << 24);
}

inline void tjGameEngine::DrawPixel(uint x, uint y, uint32_t color) {
    XSetForeground(display, gc, color);
    XFillRectangle(display, win, gc, x * pixelWidth, y * pixelHeight, pixelWidth, pixelHeight);
}

inline void tjGameEngine::Clear(uint32_t color) {
    XSetForeground(display, gc, color);
    XFillRectangle(display, win, gc, 0, 0, viewportWidth, viewportHeight);
}

inline uint32_t tjGameEngine::getWindowWidth() {
    return viewportWidth / pixelWidth;
}

inline uint32_t tjGameEngine::getWindowHeight() {
    return viewportHeight / pixelHeight;
}

inline void tjGameEngine::handleEvents() {
    XEvent xev, xnev;
    while (XPending(display)) {
        XNextEvent(display, &xev);
        if (xev.type == KeyPress) {
            KeySym sym = XLookupKeysym(&xev.xkey, 0);
            updateKeyState(sym, true);

            /*XPeekEvent(display, &xnev);*/
            /*if (xnev.type == KeyRelease) {*/
            /*    if (xev.xany.serial == xnev.xany.serial) {*/
            /*        XNextEvent(display, &xnev);*/
            /*        cout << "Same serial of the even, therefore ignoring" << endl << flush;*/
            /*    } else {*/
            /*        cout << "Am I ever coming here" << endl << flush;*/
            /*        updateKeyState(sym, false);*/
            /*    }*/
            /*}*/
        } else if (xev.type == KeyRelease) {
            KeySym sym = XLookupKeysym(&xev.xkey, 0);
            updateKeyState(sym, false);
        }
    }
}

inline void tjGameEngine::updateKeyState(KeySym sym, bool flag) {
    auto it = X11ToKey.find(sym);
    if (it == X11ToKey.end()) {
        return;
    }
    Key key = it->second;

    if (mapKeySym.find(key) == mapKeySym.end()) {
        mapKeySym[key] = {false, false, false};
        cout << "Init key " << key << endl << flush;
    }

    auto& keyState = mapKeySym[key];
    if (flag) {
        if (!keyState.isHeld) {
            keyState.isPressed = true;
            keyState.isHeld = true;
            keyState.isReleased = false;
            cout << "key " << key << " is pressed" << endl << flush;
        } else {
            keyState.isPressed = false;
            cout << "key " << key << " is held down" << endl << flush;
        }
    } else {
        if (keyState.isHeld) {
            keyState.isReleased = true;
        }
        keyState.isPressed = false;
        keyState.isHeld = false;
        cout << "key " << key << " is released" << endl << flush;
    }
}
