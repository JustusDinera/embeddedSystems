#include "Keyboard.h"
#include <fstream>
#include <iostream>
#include <chrono>
#include <random> 
#include <vector>

#define TEST_CYCLES 1
#define TIMER_OF_CAP 8

#define DEBUG

struct sParams
{
    banks portMK; 
    banks portBR;
    int bank;
    int time;
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


/*
void readTestParam(ifstream &testcaseFile)
{
    sParams tempParams;
    string tempWord;
    int tempInt;

    cout << "lese Testparameter" << endl;

    // read first line
    testcaseFile >> tempWord;
    testcaseFile >> tempWord;
    testcaseFile >> tempWord;
    testcaseFile >> tempWord;

    while (testcaseFile >> tempInt);
    {
        tempParams.portMK.banks = tempInt;

        if (testcaseFile >> tempInt)
        {
            tempParams.portBR.banks = tempInt;
        }
        else
        {
            tempParams.portBR.banks = 0;
        }

        if (testcaseFile >> tempInt)
        {
            tempParams.bank = tempInt;
        }
        else
        {
            tempParams.bank = 0;
        }

        if (testcaseFile >> tempInt)
        {
            tempParams.time = tempInt;
        }
        else
        {
            tempParams.time = 0;
        }

        criteria.push_back(tempParams);
    }
}
*/
void pushParams(int bank, int mk, int br, int time){
    sParams tempParams;

    tempParams.bank = bank;
    tempParams.portMK.banks = mk;
    tempParams.portBR.banks = br;
    tempParams.time = time;
    criteria.push_back(tempParams);
}

void iniCriteria(){

    // Case 1
    pushParams(0,1,0,10);

    // case 2
    pushParams(0,1,1,50);

    // case 3
    pushParams(0,3,1,70);

    // case 4
    pushParams(0,3,3,80);

    // case 5
    pushParams(0,2,2,100);

    //case 6
    pushParams(0,2,2,120);

    //case 7 
    pushParams(0,0,0,140);

    // case 8 
    pushParams(0,4,0,200);

    // case 9
    pushParams(0,4,4,110);
}

void isInterrupt(int bank){
    int MIDIkeyInt;

    output << endl << "Interrupt state" << endl;

    do
    {
        MIDIkeyInt = testobject.messageIntFlag();
        if (MIDIkeyInt == -1)
        {
            output << "kein MIDI Trigger aktiv" << endl;
        }
        else
        {
            output << "MIDI Trigger Key: " << MIDIkeyInt << " / Key return value: " << testobject.readKey(MIDIkeyInt, 0) << endl;
        }
    }
    while (MIDIkeyInt != -1);
}

int main(int argc, char const *argv[])
{

    // start main()
    #ifndef DEBUG
    output.open(argv[2]);
    testcases.open(argv[1]);
    #else
    output.open("auswertung.txt");
    testcases.open("zeiten.tst");
    #endif

    // catch file error 
    if (!testcases.is_open())
    {
        cout << "input file error" << endl;
        return 0;
    }

    if (!output.is_open())
    {
        cout << "output file error" << endl;
        return 0;
    }
    
    iniCriteria();

    output << "Test keyboard\n-------------" << endl; 

    for (int i = 0; i < TEST_CYCLES; i++)
    {
        output << "Key values -> cycle " << i << "\n----------------------" << endl;


        for (int set = 0; set < criteria.size(); set++)
        {
            
            // output 
            output << "Set Nr. " << set + 1 << ":" << endl;
            output << "  bank No: " << criteria[set].bank << endl;
            output << "  MK: 0x" << hex << criteria[set].portMK.banks << endl;
            output << "  BR: 0x" << hex << criteria[set].portBR.banks << endl;
            output << "  Time: " << dec << criteria[set].time << endl;
            
            for (int stady = 0; stady < MAX_DEBOUNCE_COUNT + 1; stady++)
            {
                // set key with current criteria
                testobject.setKeys(criteria[set].portMK.banks, criteria[set].portBR.banks, criteria[set].bank, criteria[set].time);
                // read key time
                output << "     debounce round: " << stady << " Key time: " << testobject.readKey(criteria[set].portBR.banks, criteria[set].bank) << endl;
            }
      
        }
        output << endl;

        isInterrupt(1);

        output << endl;
    }
    
    output << "Test Ende" << endl;
    output.close();

    return 0;
}
