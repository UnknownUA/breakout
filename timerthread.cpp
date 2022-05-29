#include <iostream>

#include "timerthread.h"
#include "gameengine.h"

Gameengine* TimerThread::game = nullptr;
volatile bool TimerThread::stop = false;

void TimerThread::setGame(Gameengine *g)
{
    game = g;
}

void TimerThread::task()
{
    using namespace std;
    while (!stop)
    {
        this_thread::sleep_for(50ms);
        if (nullptr != game)
            game->draw();
    }
    //cout << "Timer thread finished\n";
}
