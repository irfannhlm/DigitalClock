/* cc: Irfan Nurhakim Hilmi - 2025
* RTOS task for button polling
* will decide which button is pressed or hold
*/

#ifndef PIN_DEFINED
    #include "PinDefine.h"
#endif

#ifndef VARIABLES_DECLARED
    #include "Variables.h"
#endif

#define BUTTON_TASK_DELAY 100 // 100ms delay for button polling

int button_clicked, button_held = 0; // int value tells which button (0 for none)
int button_processed = 0; // tells if button is already processed by other tasks

/// @brief task for button polling
void buttonTask(void *pvParam) {
    // Task setup

    // button pins setup
    for (int i = 0; i < NUM_BUTTONS; i++) {
        pinMode(pin_buttons[i], INPUT_PULLUP);
    }

    unsigned long start_ms, elapsed_ms = 0;
    int button_pressed, prev_pressed = 0; 
    // Task loop
    while (1) {

        // check if button pressed
        button_pressed = 0;
        for (int i = 0; i < NUM_BUTTONS; i++) {
            if (!digitalRead(pin_buttons[i])) { // active low
                button_pressed = i+1; // save pressed button
                if (button_pressed != prev_pressed) { // only start timer if just pressed
                    start_ms = millis();
                }
                break;
            }
        }
        
        if (button_pressed) {
            elapsed_ms = millis() - start_ms;
            // check for holding if pressed for 0.5 second
            if (elapsed_ms > 500) {
                button_held = button_processed ? 0 : button_pressed;
            } else button_held = 0;
        } else { // restart button state if no longer pressed
            button_held = 0;
            button_processed = 0;
        }
        
        // save clicked button on release (and when not held)
        if (!button_pressed && prev_pressed && (elapsed_ms < 500)) {
            button_clicked = prev_pressed;
        }

        prev_pressed = button_pressed;

        vTaskDelay(pdMS_TO_TICKS(BUTTON_TASK_DELAY));
    }
}