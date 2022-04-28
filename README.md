# Controller for Fatar 88TP/40GH with MIDI output
[Fatar TP40GH](http://www.fatar.com/Pages/TP_40_GH_ES.htm)
## General conditions
### MIDI
#### Transmission conditions
- 1 start and 1 stop bit per byte
- baud rate: 31.25kBit --> 320s per transmitted byte
- LSB first
#### Message
- listen/transmit on 16 channels
- consists of max 3 byte
    - Status byte
    - One or two data bytes
- Message types:
    - 
