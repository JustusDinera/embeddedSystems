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
        - Note On 
    - One or two data bytes
        - MSB = 0

- Message types:
    - common
### Technical conditions
#### Keyboard 
The keyboard consists of 88 keys connected in a diode matrix.[Diode matrix of the keyboard](https://doepfer.de/DIY/Matrix_88.gif)

##### Pinout
Pin out on the flat band calbles (at the connector on the keayboard the pin numbers are inverted):
|    |      | J3      | J4       | J2  |
|----|------|---------|----------|-----|
| 1  |  20  | ~~MD3~~ | MK10     | BR1 |
| 2  |  19  | ~~MD2~~ | BR10     | MK1 |
| 3  |  18  | ~~MD1~~ | ~~MD10~~ | BR0 |
| 4  |  17  | ~~MD0~~ |          | MK0 |
| 5  |  16  | BK4     | BR9      |     |
| 6  |  15  | MK4     | ~~MD9~~  |     |
| 7  |  14  | T7      | MK9      |     |
| 8  |  13  | BR3     | BR8      |     |
| 9  |  12  | T6      | ~~MD8~~  |     |
| 10 |  11  | MK3     | MK8      |     |
| 11 |  10  | T5      | BR7      |     |
| 12 |   9  | BR2     | ~~MD7~~  |     |
| 13 |   8  | T4      | MK7      |     |
| 14 |   7  | MK2     | BR6      |     |
| 15 |   6  | T3      | ~~MD6~~  |     |
| 16 |   5  | T2      | MK6      |     |
| 17 |   4  | T1      | BR5      |     |
| 18 |   3  | T0      | ~~MD5~~  |     |
| 19 |   2  |         | MK5      |     |
| 20 |   1  |         | ~~MD4~~  |     |

#### Microcontroller
The chosen microcontroller is a [STM32G01RB](https://www.st.com/en/microcontrollers-microprocessors/stm32g071rb.html#documentation) on a [Nucleo development board](https://www.st.com/en/evaluation-tools/nucleo-g071rb.html). (HAL: [HAL Reference](https://www.st.com/resource/en/user_manual/dm00451807-description-of-stm32g0-hal-and-lowlayer-drivers-stmicroelectronics.pdf))


