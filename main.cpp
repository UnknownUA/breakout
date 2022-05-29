#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#include "gameengine.h"
#include "timerthread.h"


int main(int argc, char *argv[])
{
    TimerThread tt;
    Gameengine game;
    tt.setGame(&game);
    game.draw();
    game.readKeyCycle();
    tt.terminate();
    tt.join();
    return 0;
}
