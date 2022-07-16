
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

typedef union MIDIdataByte
{
    struct bits
    {
        unsigned char dataBit :1;
        unsigned char NoteNr_Velocity :7;
    } bits;
    char whole;
} MIDIdataByte;	

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

typedef struct MIDIPACKAGE
{
	int startBit:1;
	union midi 
	{
		MIDIstatusMsg statusMsg;
		MIDIdataMsg dataMsg;
	} midi;
} MIDIPACKAGE;


class MIDI
{
public:
	// Constructors/Destructors
	//  

	/**
	 * Constructors
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
	void setChannel(CHANNEL ch)
	{
		channel = ch;
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
	 * set mode of the channle
	 * @return MIDIPACKAGE
	 * @param  mode
	 */
	void createMIDIpackage(char data)
	{
		msg.startBit = 0;
        msg.midi.statusMsg.Status.channel = channel;
        msg.midi.statusMsg.Status.statusType = NOTEON;
        msg.midi.statusMsg.data0.whole = data;
	}


	/**
	 * creates a MIDI package 
	 * note on events are implemented only (velocity 0 is NOTEOFF event)
	 * @return MIDIPACKAGE
	 * @param  note key of the keyboard
	 * @param  velocity intensity of the pressed key
	 */
	void createMIDIpackage(char note, char velocity)
	{
		msg.startBit = 0;
		msg.midi.dataMsg.Status.statusType = NOTEON;
		msg.midi.dataMsg.Status.channel = channel;
		msg.midi.dataMsg.data0.bits.dataBit = 0;
		msg.midi.dataMsg.data0.bits.NoteNr_Velocity = note;
		msg.midi.dataMsg.data1.bits.dataBit = 0;
		msg.midi.dataMsg.data1.bits.NoteNr_Velocity = velocity;
	}

	/**
	 * get the current mode of the channel
	 * @return char
	 */
	char getMode()
	{
		return mode;
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
	 * Set the value of channel
	 * MIDI channel (1 .. 16)
	 * @param value the new value of channel
	 */
	void setChannel(CHANNEL value)
	{
		channel = value;
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


private:
	void initAttributes();

};

#endif // MIDI_H
