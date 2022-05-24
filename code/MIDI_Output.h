
#ifndef MIDI_OUTPUT_H
#define MIDI_OUTPUT_H

class MIDI_Output
{
public:
	// Constructors/Destructors
	//  


	/**
	 * Empty Constructor
	 */
	MIDI_Output();

	/**
	 * Empty Destructor
	 */
	virtual ~MIDI_Output();



	/**
	 * Send message through the medium.
	 * 
	 */
	void transmitMsg()
	{
	}


	/**
	 * create connection to medium and secure the transmit surounding
	 */
	void init()
	{
	}


};

#endif // MIDI_OUTPUT_H
