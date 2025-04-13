/* cc: Irfan Nurhakim Hilmi - 2025
* Header file for pin definitions
*/

#define PIN_DEFINED

// button pins
#define NUM_BUTTONS 4
const int pin_buttons[NUM_BUTTONS] = {16, 17, 5, 18}; // button 1, 2, 3, 4

// buzzer pin
#define PIN_BUZZER 4

// led pin
#define PIN_LED_1 19 // yellow led
#define PIN_LED_2 23 // red led

// dht sensor pin
#define PIN_DHT 13