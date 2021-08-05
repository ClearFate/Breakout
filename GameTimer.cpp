#include "GameTimer.h"

GameTimer::GameTimer(){
    
    _mainTicks = 0;
    _storedTicks = 0;

    _started = false;
    _paused = false;
}

void GameTimer::Start(){

    _mainTicks = SDL_GetTicks();
    _storedTicks = 0;
    
    _started = true;
    _paused = false;
    
}

void GameTimer::Stop(){

    _mainTicks = 0;
    _storedTicks = 0;
    
    _started = false;
    _paused = false;
}

void GameTimer::Pause(){
    if ( _started && !_paused ) {
        
        _storedTicks = SDL_GetTicks() - _mainTicks;
        _mainTicks = 0;
        
        _paused = true;
    }
}

void GameTimer::Unpause(){
    if ( _started && _paused ) {
            _mainTicks = SDL_GetTicks() - _storedTicks;
            _storedTicks = 0;
            
            _paused = false;
    }
}

Uint32 GameTimer::GetTicks(){
    if ( _started ) {
        if ( _paused ) {
            return _storedTicks;
        }
        else {
            return SDL_GetTicks() - _mainTicks;
        }
    }

    return 0;
}

bool GameTimer::IsStarted(){
    return _started;
}

bool GameTimer::IsPaused(){
    return _paused && _started;  // && mStarted je fora jer kod eventa nemoram provjeravat je li pokrenut i pauziran tajmer , vec je li pauziran to podrazumijeva
}
