#ifndef TIMERTHREAD_H
#define TIMERTHREAD_H

#include <thread>

class Gameengine;

class TimerThread : public std::thread
{
public:
    TimerThread() : std::thread(task) {}

    static void setGame(Gameengine*);
    static void terminate() { stop = true; }

private:
    static Gameengine* game;
    volatile static bool stop;

    static void task();
};

#endif // TIMERTHREAD_H
