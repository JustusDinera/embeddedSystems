
#ifndef KEYBOARD_H
#define KEYBOARD_H

#define KEYS 88
#define BANK_COUNT 8
#define KEY_COUNT_BANK 11
#define MAX_DEBOUNCE_COUNT 4

enum OUTPUT_STATE {LOW, HIGH};
enum BUTTON {MK, BR, MAX_BUTTON_COUNT};

union bankKeys
{
	uint16_t port;
	struct bits
	{
		unsigned int bit0:1;
		unsigned int bit1:1;
		unsigned int bit2:1;
		unsigned int bit3:1;
		unsigned int bit4:1;
		unsigned int bit5:1;
		unsigned int bit6:1;
		unsigned int bit7:1;
		unsigned int bit8:1;
		unsigned int bit9:1;
		unsigned int bit10:1;
	};
	
};

union banks
{
	uint16_t port;
	struct bits
	{
		unsigned int bit0:1;
		unsigned int bit1:1;
		unsigned int bit2:1;
		unsigned int bit3:1;
		unsigned int bit4:1;
		unsigned int bit5:1;
		unsigned int bit6:1;
		unsigned int bit7:1;
		unsigned int bit8:1;
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
	Keyboard();

	/**
	 * Empty Destructor
	 */
	virtual ~Keyboard();



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
		int key = keyNo + bankNo * KEYS;

		if (debounce(key,,MK) == HIGH)
		{
			
		}
		
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


private:
	// Private attributes
	//  
	OUTPUT_STATE keysState[MAX_BUTTON_COUNT][KEYS];
	int keysDebounceCount[MAX_BUTTON_COUNT][KEYS];
	int keysTime[KEYS];

	// Private attribute accessor methods
	//  


	/**
	 * Set the value of keys
	 * @param value the new value of keys
	 * @param key number of the key
	 * @param button type of button is pressed (MK, BR or in some implementations a third button per key)
	 */
	void setKeys(OUTPUT_STATE value, int key, BUTTON button)
	{
		keysState[button][key] = value;
	}

	/**
	 * Get the value of keys
	 * @param key number of the key
	 * @param button type of button is pressed (MK, BR or in some implementations a third button per key)
	 * @return the value of key
	 */
	OUTPUT_STATE getKeys(int key, BUTTON button)
	{
		return keysState[button][key];
	}

	/**
	 * debounce algorythm to check the signal is in stady state. Returns the Value of
	 * the key.
	 * @return returns the state of the key after current pin state
	 * @param  key number of the key
	 * @param  input value of the pin
	 * @param button type of button is pressed (MK, BR or in some implementations a third button per key)
	 */
	OUTPUT_STATE debounce(int key, int input, BUTTON button)
	{
		OUTPUT_STATE retVal;
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
			retVal = LOW;
		}
		else if (keysDebounceCount[button][key] >= MAX_DEBOUNCE_COUNT)
		{
			retVal = HIGH;
			keysDebounceCount[button][key] = MAX_DEBOUNCE_COUNT;  /* defensive code if integrator got corrupted */
		}
		else
		{
			retVal = keysState[button][key];
		}
		
		return retVal;
	}

	void initAttributes();

};

#endif // KEYBOARD_H
