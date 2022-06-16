
#ifndef KEYBOARD_H
#define KEYBOARD_H

#ifdef __linux__
#include <stdint.h>
#endif


#define KEYS 88
#define BANK_COUNT 11
#define KEY_COUNT_BANK 8
#define MAX_DEBOUNCE_COUNT 4
#define MAX_INT_32 0xFFFFFFFF

enum OUTPUT_STATE {LOW, HIGH};
enum BUTTON {MK, BR, MAX_BUTTON_COUNT};

union banks
{
	uint16_t banks;
	struct bits
	{
		unsigned int bank0:1;
		unsigned int bank1:1;
		unsigned int bank2:1;
		unsigned int bank3:1;
		unsigned int bank4:1;
		unsigned int bank5:1;
		unsigned int bank6:1;
		unsigned int bank7:1;
		unsigned int bank8:1;
		unsigned int bank9:1;
		unsigned int bank10:1;
	} bits;
	
};

union BankKeys
{
	uint16_t port;
	struct bits
	{
		unsigned int key0:1;
		unsigned int key1:1;
		unsigned int key2:1;
		unsigned int key3:1;
		unsigned int key4:1;
		unsigned int key5:1;
		unsigned int key6:1;
		unsigned int key7:1;
		unsigned int reserved:1;
		unsigned int key8:1;
	};
};



class Keyboard
{
public:
	// Constructors/Destructors
	//  


	/**
	 * Empty Constructor
	 */
	Keyboard(){}

	/**
	 * Empty Destructor
	 */
	virtual ~Keyboard(){}



	/**
	 * Create the internal timer, debounce variables
	 */
	void init()
	{
	}


	/**
	 * function to read a single key.
	 * @return int
	 * @param  keyNo Number of the key in a bank.
	 * @param  bankNo Number of a bank of 11 keys
	 */
	int readKey(int keyNo, int bankNo)
	{
		int key = keyNo + bankNo * KEY_COUNT_BANK;
		return keysTime[MAX_BUTTON_COUNT][key];
	}

	void setKeys(int MKportValue, int BRportValue, int bankNo, int timerVal)
	{
		int key = bankNo * KEY_COUNT_BANK;
		setKeyButtons(MKportValue, key, MK, timerVal);
		setKeyButtons(BRportValue, key, BR, timerVal);
	}

	/**
	 * cycle shift a bit in a 8 bit variable. 
	 * @return a bit pattern to enable a single bit in a port
	 */
	unsigned char shiftOutput(){
		static unsigned char port = 0x80;
		port = (port << 1)|(port >> 7);
		return port;
	}

	int messageIntFlag()
	{
		int retVal = -1;
		for (int i = 0; i < KEY_COUNT_BANK * BANK_COUNT; i++)
		{
			if (sendMsg[i] == 1)
			{
				retVal = i;
				sendMsg[i] = 0;
				return retVal;
			}
		}
		
		return retVal;
	}

private:
	// Private attributes
	//  
	OUTPUT_STATE keysState[MAX_BUTTON_COUNT][KEYS];
	int keysDebounceCount[MAX_BUTTON_COUNT][KEYS];
	uint32_t keysTime[MAX_BUTTON_COUNT +1][KEYS];
	int sendMsg[KEYS];
	// Private attribute accessor methods
	//  


	/**
	 * Set the value of keys
	 * @param value the key (MK & BR) data port register 
	 * @param key number of the key
	 * @param button type of button is pressed (MK, BR or in some implementations a third button per key)
	 */
	void setKeyButtons(int PortValue, int key, BUTTON button, int timerVal)
	{
		int inputVal = 0;

		for (int i = 0; i < KEY_COUNT_BANK; i++)
		{
			inputVal = (PortValue >> i) & 1;
			debounce(key + i,inputVal,(BUTTON)button);

			setTime(key + i, (BUTTON)button, timerVal);
		}
	}

	/**
	 * Get the value of keys
	 * @param key number of the key
	 * @param button type of button is pressed (MK, BR or in some implementations a third button per key)
	 * @return the value of key
	 */
	uint32_t getKeys(int key)
	{
		return keysTime[MAX_BUTTON_COUNT][key];
	}

	/**
	 * debounce algorythm to check the signal is in stady state. Returns the Value of
	 * the key.
	 * @return returns the state of the key after current pin state
	 * @param key number of the key
	 * @param input value of the pin
	 * @param button type of button is pressed (MK, BR or in some implementations a third button per key)
	 */
	OUTPUT_STATE debounce(int key, int input, BUTTON button)
	{
		// set debounce counter
		if (input == 0)
		{
			if (keysDebounceCount[button][key] > 0)
			{
				keysDebounceCount[button][key]--;
			}
		}
		else if (keysDebounceCount[button][key] < MAX_DEBOUNCE_COUNT)
		{
			keysDebounceCount[button][key]++;
		}
		// set output
		if (keysDebounceCount[button][key] == 0)
		{
			keysState[button][key] = LOW;
		}
		else if (keysDebounceCount[button][key] >= MAX_DEBOUNCE_COUNT)
		{
			keysState[button][key] = HIGH;
			keysDebounceCount[button][key] = MAX_DEBOUNCE_COUNT;  
		}
		
		return keysState[button][key];
	}


	void setTime(int key, BUTTON button, int timerVal){
		static OUTPUT_STATE keysStateOld[MAX_BUTTON_COUNT][KEYS];

		if (keysStateOld[button][key] != keysState[button][key])
		{
			if (keysState[button][key] == HIGH)
			{
				keysTime[button][key] = timerVal;
				keysStateOld[button][key] = HIGH;
				setTimeDif(key);
			}
			else
			{
				keysTime[button][key] = 0;
				keysStateOld[button][key] = LOW;
				clearTime(key);
			}
			sendMsg[key] = 1;
		}
	}

	void setTimeDif(int key){
		if ((keysState[BR][key] == HIGH) && (keysState[MK][key] == HIGH))
		{
			
			if (keysTime[BR][key] < keysTime[MK][key])
			{
				keysTime[MAX_BUTTON_COUNT][key] = MAX_INT_32 - keysTime[BR][key] + keysTime[MK][key];
			}
			else 
			{
				keysTime[MAX_BUTTON_COUNT][key] = keysTime[BR][key] - keysTime[MK][key];
			}
		}
		
	}

	void clearTime(int key){
		keysTime[MK][key] = 0;
		keysTime[BR][key] = 0;
		keysTime[MAX_BUTTON_COUNT][key] = 0;
	}


	void initAttributes();

};

#endif // KEYBOARD_H
