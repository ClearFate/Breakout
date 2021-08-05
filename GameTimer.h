#ifndef MY_TIMER_H
#define MY_TIMER_H

#include <SDL.h>

class GameTimer{

  public:
    GameTimer();
    // clock actions
    void Start();
    void Stop();
    void Pause();
    void Unpause();
    Uint32 GetTicks();  // dohvati vrijeme tajmera

    // check timer status
    bool IsStarted();
    bool IsPaused();
    
  private:
    Uint32 _mainTicks;   // milisekunde koje prolaze
    Uint32 _storedTicks; // spremljene pauzirane milisekunde (ticks)

    bool _started;  //  zastavica za pokretanje tajmera
    bool _paused;   //  zastavica za zaustavljanje tajmera
};


#endif
