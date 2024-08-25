#include <unistd.h>

#include <cstdlib>

#include "tjGameEngine.h"

using namespace std;

int main() {
    const int windowSize = 100;
    tjGameEngine tj;
    /*tj.createWindow(windowSize, windowSize, 4, 4);*/
    tj.createWindow(5120, 1080, 1, 1);
    while (1) {
        for (int i = 0; i < windowSize; i++) {
            for (int j = 0; j < windowSize; j++) {
                tj.drawPixel(
                    i, j,
                    (rand() % 2) ? tj.rgb(0, 0, 0) : tj.rgb(236, 238, 236));
            }
        }

        usleep(1000);
    }

    tj.destroyWindow();
}
