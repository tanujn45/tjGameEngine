#include <unistd.h>

#include <cstdint>
#include <cstdlib>

#include "tjGameEngine.h"

using namespace std;

class Engine : public tjGameEngine {
    int i, j;
    uint8_t color, color2, color3;

   public:
    bool Create() override {
        i = j = 0;
        color = 0, color2 = 0, color3 = 0;
        cout << "I am being created" << endl;
        return true;
    }

    bool Update() override {
        if (mapKeySym[Key::A].isPressed) {
            color += 1;
            color2 += rand() % 3 + 1;
            color3 += rand() % 2 + 1;
            /*cout << "A is pressed" << endl << flush;*/
            DrawPixel(i, j, rgb(color, color2, color3));
            i++;
            if (i == getWindowWidth()) {
                i = 0;
                j++;
            }
            if (j == getWindowHeight()) {
                j = 0;
            }
        }
        if (mapKeySym[Key::R].isPressed) {
            Clear(rgb(0, 0, 0));
        }
        if (mapKeySym[Key::Q].isPressed) {
            return false;
        }
        return true;
    }
};

int main() {
    int windowWidth = 400 / 4;
    int windowHeight = 400 / 4;

    Engine eng;
    eng.Construct(windowWidth, windowHeight, 4, 4);
    eng.Start();
}

/*
ApplicationStartUp(): Application Startup, this is useless function

DONE: CreateWindowPane(): create a window, this where we are setting up the display and protocols and mask

bAtomActive = true: Set the active flag to true

thread t = thread(EngineThread, this): Start the thread
    ThreadStartUp(): Does nothing

    olc_PrepareEngine()
        CreateGraphics()
        also setting the mapSym
        m_tp1 = clock now
        m_tp2 = clock now

    OnUserCreate(): Overridden function I don't know why it is used

    while bAtomActive
        olc_CoreUpdate();
            m_tp2 = clock now
            elapsedTime = m_tp2 - m_tp1
            m_tp1 = m_tp2
            fLastElapsed = elapsedTime.count()

            HandleSystemEvent(): Similar to our handleEvents, nothing else


        !OnUserDestroy();
            bAtomActive = true;

    ThreadCleanUp():

StartSystemEventLoop(); does nothing

t.join();

ApplicationCleanUp(): Calls destroy device which is similar to ours
*/

/*
My plan of action

Make a namespace {
     declare a class
}
*/
