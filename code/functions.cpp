#include "functions.h"

void readKeys(int maxBank, int maxBankKey)
{
    int pinValue = 0;
    for (int i = 0; i < maxBank; i++)
    {
        for (int j = 0; j < maxBankKey; j++)
        {
            readPin(i, j);
        }
        
    }
    
}

void readPin(int bankNo, int bankKeyNo, keys * keyboard)
{
    state retVal = NOCHANGE;


    for (int i = 0; i < BUTTONS_PER_KEY; i++)
    {
        if (keyboard[bankNo][bankKeyNo][i]->counter == BUTTONS_PER_KEY)
            keyboard[bankNo][bankKeyNo][i]->counter = 0;
        else
            keyboard[bankNo][bankKeyNo][i]->counter++;

        // read the hardware GPIO
        keyboard[bankNo][bankKeyNo][i]->samples[keyboard[bankNo][bankKeyNo][i]->counter] = readGPIO();
        
        // check if the state changed (debounce)
        for (int j = 0; j < BOUNCE_COUNT; j++)
        {
            if (j < BOUNCE_COUNT - 2)
            {
                if (keyboard[bankNo][bankKeyNo][i]->samples[j] == keyboard[bankNo][bankKeyNo][i]->samples[j +1])
                    retVal = keyboard[bankNo][bankKeyNo][i]->samples[j];
                else
                    retVal = NOCHANGE;
            }
            else if (j == BOUNCE_COUNT - 1)
            {
                if (keyboard[bankNo][bankKeyNo][i]->samples[j] == keyboard[bankNo][bankKeyNo][i]->samples[0])
                    retVal = keyboard[bankNo][bankKeyNo][i]->samples[j];
                else
                    retVal = NOCHANGE;
            }
            keyboard[bankNo][bankKeyNo][i]->states = retVal;
        }   
    }
}

state readGPIO(){

}