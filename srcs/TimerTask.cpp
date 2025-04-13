/* cc: Irfan Nurhakim Hilmi - 2025
* RTOS task for timer update
* will update timer based on time ticks and button clicks
*/

#ifndef PIN_DEFINED
    #include "PinDefine.h"
#endif

#ifndef VARIABLES_DECLARED
    #include "Variables.h"
#endif

#define TIMER_TASK_DELAY 200 // 200ms delay for timer update

int timer_hour, timer_minute, timer_second = 0;
int timer_totalsecond;

// timer parameters
#define TIMER_FREQ 1e6 // 1MHz frequency
const int isr_period = 1e6; // 1s interrupt period (in microsecond) 
hw_timer_t *timer = NULL;

// do countdown using timer interrupt
void IRAM_ATTR timerISR() {
    if (!lcd_timer_mode) { // only start countdown on the right mode (lcd_timer_mode == 0) 
        timer_totalsecond = (timer_totalsecond-1>=0) ? timer_totalsecond-1 : timer_totalsecond;
    } 
}

void timerTask(void *pvParam) {
    // Task setup

    // setup pin for alarm led indicator
    pinMode(PIN_LED_2, OUTPUT);

    // setup timer interrupt
    timer = timerBegin(TIMER_FREQ);
    timerAttachInterrupt(timer, &timerISR);
    timerAlarm(timer, isr_period, true, 0);

    // set 30s as initial timer time
    int timer_temp = 30;
    timer_totalsecond = 30;

    // Task loop
    while (1) {
        if (lcd_timer_mode) { // timer manual set mode
            timer_totalsecond = timer_temp;
            if (lcd_page_num == 2) {
                if (button_clicked == 3) { // decrement timer
                    switch (lcd_cursor_pos) {
                    case 7: // X0:00:00
                        timer_temp = (timer_temp-36000>=0) ? timer_temp-36000 : timer_temp;
                        break;
                    case 8: // 0X:00:00
                        timer_temp = (timer_temp-3600>=0) ? timer_temp-3600 : timer_temp;
                        break;
                    case 10: // 00:X0:00
                        timer_temp = (timer_temp-600>=0) ? timer_temp-600 : timer_temp;
                        break;
                    case 11: // 00:0X:00
                        timer_temp = (timer_temp-60>=0) ? timer_temp-60 : timer_temp;
                        break;
                    case 13: // 00:00:X0
                        timer_temp = (timer_temp-10>=0) ? timer_temp-10 : timer_temp;
                        break;
                    case 14: // 00:00:0X
                        timer_temp = (timer_temp-1>=0) ? timer_temp-1 : timer_temp;
                        break;
                    default:
                        break;
                    }
                    button_clicked = 0;
    
                } else if (button_clicked == 4) {
                    switch (lcd_cursor_pos) { // increment timer
                    case 7: // X0:00:00
                        timer_temp = (timer_temp+36000<(3600*24)) ? timer_temp+36000 : timer_temp;
                        break;
                    case 8: // 0X:00:00
                        timer_temp = (timer_temp+3600<(3600*24)) ? timer_temp+3600 : timer_temp;
                        break;
                    case 10: // 00:X0:00
                        timer_temp = (timer_temp+600<(3600*24)) ? timer_temp+600 : timer_temp;
                        break;
                    case 11: // 00:0X:00
                        timer_temp = (timer_temp+60<(3600*24)) ? timer_temp+60 : timer_temp;
                        break;
                    case 13: // 00:00:X0
                        timer_temp = (timer_temp+10<(3600*24)) ? timer_temp+10 : timer_temp;
                        break;
                    case 14: // 00:00:0X
                        timer_temp = (timer_temp+1<(3600*24)) ? timer_temp+1 : timer_temp;
                        break;
                    default:
                        break;
                    }
                    button_clicked = 0;
                } else if (button_held == 4) {
                    timer_temp = 30;
                }
            }
            
        } else { // check for timer buzzer
            if (!timer_totalsecond) {
                buzzer_timer_on = 1;
                lcd_timer_mode = 1; // back to setting mode
            };
        }
        
        timer_hour = timer_totalsecond / 3600;
        timer_minute = (timer_totalsecond % 3600) / 60;
        timer_second = (timer_totalsecond % 3600) % 60;

        digitalWrite(PIN_LED_2, buzzer_timer_on);
        vTaskDelay(pdMS_TO_TICKS(TIMER_TASK_DELAY));
    }
}

