/* cc: Irfan Nurhakim Hilmi - 2025
* RTOS task for alarm updates and checks
* will update alarm time based on button clicks
* and will check alarm time if met
*/

#ifndef PIN_DEFINED
    #include "PinDefine.h"
#endif

#ifndef VARIABLES_DECLARED
    #include "Variables.h"
    #include "time.h"
#endif

#define ALARM_TASK_DELAY 200 // 200ms delay for alarm checking

int alarm_hour, alarm_minute, alarm_second = 0;

void alarmTask(void *pvParam) {
    // Task setup

    // setup pin for alarm led indicator
    pinMode(PIN_LED_1, OUTPUT);

    // set 5 o'clock as default alarm
    alarm_hour = 5;

    // Task loop
    while (1) {
        if (lcd_alarm_mode && (lcd_page_num == 1)) { // alarm manual set mode
            if (button_clicked == 3) { // decrement timer
                switch (lcd_cursor_pos) {
                case 7: // X0:00:00
                    alarm_hour = (alarm_hour-10>=0) ? alarm_hour-10 : alarm_hour;
                    break;
                case 8: // 0X:00:00
                    alarm_hour = (alarm_hour-1>=0) ? alarm_hour-1 : alarm_hour;
                    break;
                case 10: // 00:X0:00
                    alarm_minute = (alarm_minute-10>=0) ? alarm_minute-10 : alarm_minute;
                    break;
                case 11: // 00:0X:00
                    alarm_minute = (alarm_minute-1>=0) ? alarm_minute-1 : alarm_minute;
                    break;
                case 13: // 00:00:X0
                    alarm_second = (alarm_second-10>=0) ? alarm_second-10 : alarm_second;
                    break;
                case 14: // 00:00:0X
                    alarm_second = (alarm_second-1>=0) ? alarm_second-1 : alarm_second;
                    break;
                default:
                    break;
                }
                button_clicked = 0;

            } else if (button_clicked == 4) {
                switch (lcd_cursor_pos) { // increment timer
                case 7: // X0:00:00
                    alarm_hour = (alarm_hour+10<24) ? alarm_hour+10 : alarm_hour;
                    break;
                case 8: // 0X:00:00
                    alarm_hour = (alarm_hour+1<24) ? alarm_hour+1 : alarm_hour;
                    break;
                case 10: // 00:X0:00
                    alarm_minute = (alarm_minute+10<60) ? alarm_minute+10 : alarm_minute;
                    break;
                case 11: // 00:0X:00
                    alarm_minute = (alarm_minute+1<60) ? alarm_minute+1 : alarm_minute;
                    break;
                case 13: // 00:00:X0
                    alarm_second = (alarm_second+10<60) ? alarm_second+10 : alarm_second;
                    break;
                case 14: // 00:00:0X
                    alarm_second = (alarm_second+1<60) ? alarm_second+1 : alarm_second;
                    break;
                default:
                    break;
                }
                button_clicked = 0;
            } else if (button_held == 4) {
                alarm_hour = 5; alarm_minute = 0; alarm_second = 0;
            }

        } else {
            if ((alarm_hour == timeinfo.tm_hour) && (alarm_minute == timeinfo.tm_min) 
            && (alarm_second == timeinfo.tm_sec)) {
                buzzer_alarm_on = 1;
            } 
        }

        digitalWrite(PIN_LED_1, buzzer_alarm_on);
        vTaskDelay(pdMS_TO_TICKS(ALARM_TASK_DELAY));
    }
}

