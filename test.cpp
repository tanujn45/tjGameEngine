#include <unistd.h>

#include <cstdint>
#include <cstdlib>

#include "tjGameEngine.h"

using namespace std;

int main() {
    tjGameEngine tj;
    int windowWidth = 400 / 4;
    int windowHeight = 400 / 4;
    uint8_t color = 0, color2 = 0, color3 = 0;
    tj.createWindow(windowWidth, windowHeight, 4, 4);
    int i, j;
    i = j = 0;
    while (1) {
        tj.handleEvents();
        if (tj.mapKeySym[tj.Key::A].isPressed) {
            color += 1;
            color2 += 2;
            color3 += 3;
            /*cout << "A is pressed" << endl << flush;*/
            tj.drawPixel(i, j, tj.rgb(color, color2, color3));
            i++;
            if (i == windowWidth) {
                i = 0;
                j++;
            }
            if (j == windowHeight) {
                j = 0;
            }
        }
    }

    tj.destroyWindow();
}

/*
ApplicationStartUp(): Application Startup, this is useless function

CreateWindowPane(): create a window, this where we are setting up the display and protocols and mask

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
