#include "Keyboard.h"
#include <fstream>
#include <iostream>
#include <chrono>
#include <random> 

#define TEST_CYCLES 10
#define TIMER_OF_CAP 8

using namespace std;

// log file
ofstream output;

// test criteria
int criteria;

// unit under test
Keyboard testobject;

// timer emulation
int32_t timerCount = 0;
int timerOverFlow = 0;


// data register emulation
uint32_t portMK = 0;
uint32_t portBR = 0;

int main(int argc, char const *argv[])
{

    // start main()
    output.open(argv[2]);
    // catch file error 
    if (!output.is_open())
    {
        cout << "output file error" << endl;
        return 0;
    }

    // catch input errors
    try 
    {
        criteria = stoi(argv[1]);
    }
    catch(...)
    {
        cout << "criteria error" << endl;
        return 0;
    }
    
    
    output << "Test keyboard\n-------------" << endl; 

    output << "fill button states\n------------------" << endl;
    output << "fill first button (MK)\n-----------------" << endl;
    portMK = 0xFFFF;
    output << "MK port reg value: " << hex << portMK << endl;
     

    for (int i = 0; i < TEST_CYCLES; i++)
    {
        // set button states (MK)
        for (int bank = 0; bank < BANK_COUNT; bank++)
        {
            testobject.setKeys(portMK, portBR, bank, timerCount, timerOverFlow);
        }
        

        output << "Key values -> cycle " << i << "\n----------------------" << endl;
        output << "BR port reg value: " << hex << portBR << endl;

        for (int banks = 0; banks < BANK_COUNT; banks++)
        {
            for (int bankKeys = 0; bankKeys < KEY_COUNT_BANK; bankKeys++)
            {
                output << "bank No " << banks << ", key No " << bankKeys << ": ";
                output << testobject.readKey(bankKeys, banks);
            }

            // set buttons (BR)
            if (portBR > (1 << 15))
            {
                portBR = 1;
            }
            else
            {            
                portBR <<= 1;
            }      
            testobject.setKeys(portMK, portBR, banks, timerCount, timerOverFlow);
        }

        // controll timer 
        timerCount++;

        
        // set timer over flow
        if (timerCount > TIMER_OF_CAP)
        {
            timerOverFlow = 1;
        }
        
        
    }
    
    output.close();

    return 0;
}
