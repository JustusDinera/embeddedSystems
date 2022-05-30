
#ifndef MIDI_H
#define MIDI_H

enum MIDIcontrollerChange {
	MODULATION =1, VOLUME =7, PAN = 10, EXPRESSION = 11, SUSTAIN = 64, RESET_ALL_CONTROLL = 121, ALL_NOTES_OFF = 123
};

enum STATUS {
	NOTEOFF = 0x8, NOTEON, POLY_KEY_PRESURE, CONTROLL_CHANGE, PROG_CHANGE, CHANNEL_PRESSURE, PITCH_BEND
};

enum CHANNEL {
	CH1, CH2, CH3, CH4, CH5, CH6, CH7, CH8, CH9, CH10, CH11, CH12, CH13, CH14, CH15, CH16
};

struct MIDIstatusByte
{
	STATUS statusType :4;
	CHANNEL channel :4;
};
struct MIDIdataByte
{
	unsigned int dataBit :1;
	unsigned char NoteNr_Velocity :7;
};	

struct MIDIstatusMsg 
{
	MIDIstatusByte Status;
	MIDIdataByte data0;
};

struct MIDIdataMsg {
	MIDIstatusByte Status;
	MIDIdataByte data0;
	MIDIdataByte data1;
};

union MIDIPACKAGE
{
	MIDIstatusMsg statusMsg;
	MIDIdataMsg dataMsg;
};


class MIDI
{
public:
	// Constructors/Destructors
	//  


	/**
	 * Empty Constructor
	 */
	MIDI();
	MIDI(CHANNEL channel){
		setChannel(channel);
	}

	/**
	 * Empty Destructor
	 */
	virtual ~MIDI();



	/**
	 * set the MIDI channel
	 * @param  channel sets the chnnel for the MIDI message
	 */
	void setChannel(CHANNEL channel)
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
		MIDIPACKAGE tempMsg;

		tempMsg.dataMsg.Status.statusType = NOTEON;
		tempMsg.dataMsg.Status.channel = channel;
		tempMsg.dataMsg.data0.dataBit = 0;
		tempMsg.dataMsg.data0.NoteNr_Velocity = note;
		tempMsg.dataMsg.data1.dataBit = 0;
		tempMsg.dataMsg.data1.NoteNr_Velocity = velocity;
	
		return tempMsg;
	}

	MIDIPACKAGE createMIDIpackage(char note, char velocity)
	{
		MIDIPACKAGE tempMsg;

		tempMsg.dataMsg.Status.statusType = NOTEON;
		tempMsg.dataMsg.Status.channel = channel;
		tempMsg.dataMsg.data0.dataBit = 0;
		tempMsg.dataMsg.data0.NoteNr_Velocity = note;
		tempMsg.dataMsg.data1.dataBit = 0;
		tempMsg.dataMsg.data1.NoteNr_Velocity = velocity;

		return tempMsg;
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
	CHANNEL channel;
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
	void setChannel(CHANNEL value)
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



private:
	void initAttributes();

};

#endif // MIDI_H
