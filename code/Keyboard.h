
#ifndef KEYBOARD_H
#define KEYBOARD_H

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
	}


	/**
	 * debounce algorythm to check the signal is in stady state. Returns the Value of
	 * the key.
	 * @return int
	 * @param  currentValue The current state of a key.
	 * @param  lastState last memorized state
	 */
	int debounce(int currentValue, int lastState)
	{
	}

private:
	// Private attributes
	//  

	int Keys;
	int bounce_us;

	// Private attribute accessor methods
	//  


	/**
	 * Set the value of Keys
	 * @param value the new value of Keys
	 */
	void setKeys(int value)
	{
		Keys = value;
	}

	/**
	 * Get the value of Keys
	 * @return the value of Keys
	 */
	int getKeys()
	{
		return Keys;
	}

	/**
	 * Set the value of bounce_us
	 * @param value the new value of bounce_us
	 */
	void setBounce_us(int value)
	{
		bounce_us = value;
	}

	/**
	 * Get the value of bounce_us
	 * @return the value of bounce_us
	 */
	int getBounce_us()
	{
		return bounce_us;
	}

	void initAttributes();

};

#endif // KEYBOARD_H
