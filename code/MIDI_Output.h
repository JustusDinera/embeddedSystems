#include <MIDI.h>

#ifndef MIDI_OUTPUT_H
#define MIDI_OUTPUT_H


class MIDI_Output : MIDI
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
	void transmitMsg(int note, int velocity)
	{
		createMIDIpackage(note, velocity);
	}


	/**
	 * create connection to medium and secure the transmit surounding
	 */
	void init()
	{
	}

private:

};

#endif // MIDI_OUTPUT_H
