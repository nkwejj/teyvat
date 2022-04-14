#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>

#include "gamemodel.h"

gamemodel::gamemodel():
    gameStatus(PLAYING),
    gameLevel(BASIC)
{

}
gamemodel::~gamemodel()
{
    if(gameMap)
    {
        free(gameMap);
        gameMap = NULL;
    }
}


