#ifndef _TIMER_H
#define _TIMER_H
#include <chrono>
#include <functional>
#include <thread>
//this should execute a function at a certain interval
class timer
{
    private:
        std::function<void()> func;
        int delT;
        bool running;
        void runTimer ()
        {
            while(running = true)
            {
                func();
                std::this_thread::sleep_for(std::chrono::milliseconds(delT));
            }
        }
    public:
        void start ()
        {
            running = true;
        }
        void end ()
        {
            running = false;
        }
        timer (std::function<void()> f, int d)
        {
            func = f;
            d = delT;
        }
};
#endif