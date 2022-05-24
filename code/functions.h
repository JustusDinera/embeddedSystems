#define KEY_BANK_COUNT 8
#define KEYS_PER_BANK 11
#define BUTTONS_PER_KEY 2
#define BOUNCE_COUNT 3

enum eInPins {};
enum eOutPins {};
enum buttons {MK, BR};
enum state {LOW, HIGH, NOCHANGE};
/*
    typedefinitions
*/
struct bounce {
    int counter = 0;
    state samples[BOUNCE_COUNT];
    state states = LOW;
};
typedef bounce keyButtons[BUTTONS_PER_KEY];
typedef keyButtons keys[KEY_BANK_COUNT][KEYS_PER_BANK];


/*
    variable declatation
*/

/*
    function defninition
*/
// read the whole keys
void readKeys(int maxOutPins, int maxInPins, keys * keyboard, buttons button);

