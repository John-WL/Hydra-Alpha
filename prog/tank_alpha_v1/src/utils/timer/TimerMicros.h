// Author: John-William Lebel, 2021-04-08, creation

// implementation of a simple timer

#ifndef TIMER_US_H
#define TIMER_US_H

class TimerMicros
{
    public:
        TimerMicros(long mircoseconds, void (*recurrentCallback)(void));

        void start();
        void update();
        
    private:
        void lapse();
        bool elapsed();
        bool elapsedAutoReload();

        long _nextTime;
        long _duration;

        void(*_recurrentCallback)(void);
};

#endif