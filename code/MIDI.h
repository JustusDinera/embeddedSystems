
#ifndef MIDI_H
#define MIDI_H

class MIDI
{
public:
	// Constructors/Destructors
	//  


	/**
	 * Empty Constructor
	 */
	MIDI();

	/**
	 * Empty Destructor
	 */
	virtual ~MIDI();



	/**
	 * set the MIDI channel
	 * @param  channel sets the chnnel for the MIDI message
	 */
	void setChannel(char channel)
	{
	}


	/**
	 * get the MIDI channel
	 * @return char
	 */
	char getChannel()
	{
	}


	/**
	 * set channel mode
	 * @param  mode
	 */
	void setMode(char mode)
	{
	}


	/**
	 * set mode of the channle
	 * @return MIDIPACKAGE
	 * @param  mode
	 */
	MIDIPACKAGE createMIDIpackage(char mode)
	{
	}


	/**
	 * creates a MIDI package
	 * @return MIDIPACKAGE
	 * @param  note
	 * @param  velocity
	 */
	MIDIPACKAGE createMIDIpackage(char note, char velocity)
	{
	}


	/**
	 * get the current mode of the channel
	 * @return char
	 */
	char getMode()
	{
	}

protected:
	// Protected attributes
	//  

	// Union of MIDI package 
	MIDIPACKAGE msg;
	// MIDI channel (1 .. 16)
	char channel;
	// Mode of the MIDI channel
	// 1 poly on omni on
	// 2 mono on omni on
	// 3 poly on omni off
	// 4 mono on omni off
	char mode;

	// Protected attribute accessor methods
	//  


	/**
	 * Set the value of msg
	 * Union of MIDI package
	 * @param value the new value of msg
	 */
	void setMsg(MIDIPACKAGE value)
	{
		msg = value;
	}

	/**
	 * Get the value of msg
	 * Union of MIDI package
	 * @return the value of msg
	 */
	MIDIPACKAGE getMsg()
	{
		return msg;
	}

	/**
	 * Set the value of channel
	 * MIDI channel (1 .. 16)
	 * @param value the new value of channel
	 */
	void setChannel(char value)
	{
		channel = value;
	}

	/**
	 * Get the value of channel
	 * MIDI channel (1 .. 16)
	 * @return the value of channel
	 */
	char getChannel()
	{
		return channel;
	}

	/**
	 * Set the value of mode
	 * Mode of the MIDI channel
	 * 1 poly on omni on
	 * 2 mono on omni on
	 * 3 poly on omni off
	 * 4 mono on omni off
	 * @param value the new value of mode
	 */
	void setMode(char value)
	{
		mode = value;
	}

	/**
	 * Get the value of mode
	 * Mode of the MIDI channel
	 * 1 poly on omni on
	 * 2 mono on omni on
	 * 3 poly on omni off
	 * 4 mono on omni off
	 * @return the value of mode
	 */
	char getMode()
	{
		return mode;
	}


	/**
	 * create the status byte
	 * @param  type
	 */
	void setStatus(char type)
	{
	}


	/**
	 * set the databytes
	 * @param  type
	 * @param  byte0
	 * @param  byte1
	 */
	void setData(char type, char byte0, char byte1)
	{
	}

private:
	void initAttributes();

};

#endif // MIDI_H
