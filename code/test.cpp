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


int main(int argc, char const *argv[])
{
    int MIDIkeyInt;

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
    

    readTestParam(testcases);

    output << "Test keyboard\n-------------" << endl; 

    for (int i = 0; i < TEST_CYCLES; i++)
    {
        output << "Key values -> cycle " << i << "\n----------------------" << endl;


        for (int set = 0; set < criteria.size(); set++)
        {
            // set key with current criteria
            testobject.setKeys(criteria[set].portMK.banks, criteria[set].portBR.banks, criteria[set].bank, criteria[set].time);
            
            // output 
            output << "Set Nr. " << set + 1 << ":" << endl;
            output << "  key No: " << criteria[set].bank << endl;
            output << "  MK: " << hex << criteria[set].portMK.banks << endl;
            output << "  BR: " << hex << criteria[set].portBR.banks << endl;
            output << "  Time: " << criteria[set].time << endl;
            output << "    Key time: " << testobject.readKey(criteria[set].portBR.banks, criteria[set].bank) << endl;
      
        }

        output << endl;

        do
        {
            MIDIkeyInt = testobject.messageIntFlag();
            if (MIDIkeyInt == -1)
            {
                output << "kein MIDI Trigger aktiv" << endl;
            }
            else
            {
                output << "  MIDI Trigger Key: " << MIDIkeyInt << endl;
            }
        }
        while (MIDIkeyInt != -1);
        
    }
    
    output << "Test Ende" << endl;
    output.close();

    return 0;
}
