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
        - MSB = 1
        - 
    - One or two data bytes
        - MSB = 0

- Message types:
    - common
### Technical conditions
#### Keyboard 
The keyboard consists of 88 keys connected in a diode matrix.[Diode matrix of the keyboard](https://doepfer.de/DIY/Matrix_88.gif)
#### Microcontroller
The chosen microcontroller is a [STM32G01RB](https://www.st.com/en/microcontrollers-microprocessors/stm32g071rb.html#documentation) on a [Nucleo development board](https://www.st.com/en/evaluation-tools/nucleo-g071rb.html).


