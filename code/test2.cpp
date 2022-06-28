#include "Keyboard.h"
#include <fstream>
#include <iostream>
#include <chrono>
#include <random> 
#include <vector>

#define TEST_CYCLES 1
#define TIMER_OF_CAP 8
#define SPACE "   "

#define DEBUG

struct sParams
{
    banks portMK; 
    banks portBR;
    uint bank;
    uint time;
    uint target;
};


using namespace std;

// log file
ofstream output;

// input file
ifstream testcases;

// test criteria
vector<sParams> criteria;

// unit under test
Keyboard testobject;

// timer emulation
int32_t timerCount = 0;


void pushParams(uint bank, uint mk, uint br, uint time, uint target){
    sParams tempParams;

    tempParams.bank = bank;
    tempParams.portMK.banks = mk;
    tempParams.portBR.banks = br;
    tempParams.time = time;
    tempParams.target = target;
    criteria.push_back(tempParams);
}

void iniCriteria(){

    // Case 1
    pushParams(0,1,0,10, 0);

    // case 2
    pushParams(0,1,1,50, 40);

    // case 3
    pushParams(0,3,1,70, 0);

    // case 4
    pushParams(0,3,3,80, 10);

    // case 5
    pushParams(0,2,2,100, 0);

    //case 6
    pushParams(0,2,2,120, 0);

    //case 7 
    pushParams(0,0,0,140, 0);

    // case 8 
    pushParams(0,4,0,0xFFFFFFF0, 0);

    // case 9
    pushParams(0,4,4,110, 125);
}

void isInterrupt(int bank){
    bool testPassed = true;
    int MIDIkeyInt;

    while (MIDIkeyInt != -1);
}

int main(int argc, char const *argv[])
{
    Keyboard testobject;
    vector<int> functionValues;
    bool firstRun = true;
    int testsPassed = 0;

    output.open("test_outputs.txt");


    /* 
    * TODO Test Tasten auslesen 
    */
    /* initial Test param */
    iniCriteria();
    /* Read functions */
    output << "---- KEY VALUE TEST ----" << endl;
    for (size_t i = 0; i < criteria.size(); i++)
    {
        // set parameter 
        testobject.setKeys(criteria[i].portMK.banks, criteria[i].portBR.banks, criteria[i].bank, criteria[i].time);
        
        // read key parameter
        output << "Parameters of criteria" << i << endl;
        for (int bankNo = 0; bankNo < BANK_COUNT; bankNo++)
        {
            for (int keyNo = 0; keyNo < KEY_COUNT_BANK; keyNo++)
            {
                if (firstRun)
                {
                    output << SPACE << "Bank No. " << bankNo << " hat die folgenden Keys aktiv: " << endl;
                    firstRun = false;
                }
                
                if (testobject.readKey(i, bankNo) > 0)
                {
                    output << SPACE << SPACE << "Vales in Key " << keyNo << testobject.readKey(i, bankNo) << endl;
                }

                // Time Erte Test !!!!
                if ((i != 0) && ((1 << keyNo) & criteria[i].portBR.banks) )
                {
                    if (((1 << keyNo) & criteria[i].portBR.banks) == ((1 << keyNo) & criteria[i-1].portBR.banks))
                    {
                        if((criteria[i].time - criteria[i-1].time) && (testobject.readKey(i, bankNo)))
                        {
                            output << "TEST PASSED!" << endl;
                        }
                        else
                        {
                            testsPassed++;
                            output << "TEST FAILED!" << endl;
                        }
                    }  
                }
            }

            firstRun = true;
        }
        
        
    }
    
    /* auswerten */ 

    /* ausgeben */

    /* 
    * TODO Test MIDI 
    */
    /* initial Test param */
    
    /* Read functions */

    /* auswerten */ 

    /* ausgeben */
    
    return 0;
}
