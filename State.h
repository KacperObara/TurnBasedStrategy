#ifndef STATE_H
#define STATE_H

#include "GameEngine.h"
class State
{
    public:

        virtual void Update()=0;
        virtual void Draw()=0;

		GameEngine *game;
    protected:
        

    private:
};

#endif // STATE_H
