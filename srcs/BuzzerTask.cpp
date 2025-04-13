/* cc: Irfan Nurhakim Hilmi - 2025
* RTOS task for buzzer checking
* will turn on buzzer when alarm or timer is met
*/

#ifndef PIN_DEFINED
    #include "PinDefine.h"
#endif

#ifndef VARIABLES_DECLARED
    #include "Variables.h"
#endif

#include "Melodies.h"

#define BUZZER_TASK_DELAY 100 // 100ms delay for buzzer checking

// parameters for alarm buzzer
#define BUZZER_ALARM_REPEAT 2
#define BUZZER_ALARM_BPM (94*2)
#define BUZZER_ALARM_DELAY (int) (60000.0/BUZZER_ALARM_BPM)
const int buzzer_alarm_melodies[] = { // melodies for "Marry Had a Little Lamb"
    M_A5, 1, M_G4, 1, M_F4, 1, M_G4, 1, M_A5, 1, M_A5, 1, M_A5, 2, 
    M_G4, 1, M_G4, 1, M_G4, 2, M_A5, 1, M_C5, 1, M_C5, 2, 
    M_A5, 1, M_G4, 1, M_F4, 1, M_G4, 1, M_A5, 1, M_A5, 1, M_A5, 1, M_A5, 1,
    M_G4, 1, M_G4, 1, M_A5, 1, M_G4, 1, M_F4, 4, 
};
const int buzzer_alarm_melodies_length = sizeof(buzzer_alarm_melodies)/sizeof(buzzer_alarm_melodies[0]);

// parameters for timer buzzer
#define BUZZER_TIMER_REPEAT 2
#define BUZZER_TIMER_BPM (100*2)
#define BUZZER_TIMER_DELAY (int) (60000.0/BUZZER_ALARM_BPM)
const int buzzer_timer_melodies[] = { // melodies for "Ganyang Fufufafa"
    M_CS6, 2, M_AS6, 2, M_CS6, 2, M_AS6, 1, M_AS6, 1, M_CS6, 1, M_B6, 1, M_AS6, 1, M_B6, 1, M_CS6, 2, 
    M_AS6, 1, M_G5, 1, M_G5, 1, M_G5, 1, M_AS6, 1, M_B6, 2, M_CS6, 1, M_B6, 1, M_A6, 2, M_G5, 2, M_F5, 4

};
const int buzzer_timer_melodies_length = sizeof(buzzer_timer_melodies)/sizeof(buzzer_timer_melodies[0]);

int buzzer_alarm_on, buzzer_timer_on = 0;

void buzzerTask(void *pvParam) {
    // Task setup

    // buzzer pin setup
    pinMode(PIN_BUZZER, OUTPUT);
    analogWriteResolution(PIN_BUZZER, 8);

    // Task loop
    while (1) {
        if (buzzer_alarm_on) {
            for (int j = 0; j < BUZZER_ALARM_REPEAT; j++) {
                for (int i = 0; i < buzzer_alarm_melodies_length; i=i+2) {
                    analogWriteFrequency(PIN_BUZZER, buzzer_alarm_melodies[i]);
                    
                    for (int i = 1; i <= 128; i=i<<1) {
                        analogWrite(PIN_BUZZER, i);
                        vTaskDelay(pdMS_TO_TICKS(5));
                    }
                    
                    vTaskDelay(pdMS_TO_TICKS(BUZZER_ALARM_DELAY*buzzer_alarm_melodies[i+1]-5*16));
    
                    for (int i = 128; i > 0; i=i>>1) {
                        analogWrite(PIN_BUZZER, i);
                        vTaskDelay(pdMS_TO_TICKS(5));
                    }

                    analogWrite(PIN_BUZZER, 0);
                }
            }
            analogWrite(PIN_BUZZER, 0);
            buzzer_alarm_on = 0;
            buzzer_timer_on = 0;
        }

        if (buzzer_timer_on) {
            for (int j = 0; j < BUZZER_TIMER_REPEAT; j++) {
                for (int i = 0; i < buzzer_timer_melodies_length; i=i+2) {
                    analogWriteFrequency(PIN_BUZZER, buzzer_timer_melodies[i]);
                    
                    for (int i = 1; i <= 128; i=i<<1) {
                        analogWrite(PIN_BUZZER, i);
                        vTaskDelay(pdMS_TO_TICKS(5));
                    }
                    
                    vTaskDelay(pdMS_TO_TICKS(BUZZER_TIMER_DELAY*buzzer_timer_melodies[i+1]-5*16));
    
                    for (int i = 128; i > 0; i=i>>1) {
                        analogWrite(PIN_BUZZER, i);
                        vTaskDelay(pdMS_TO_TICKS(5));
                    }

                    analogWrite(PIN_BUZZER, 0);
                }
            }
            analogWrite(PIN_BUZZER, 0);
            buzzer_alarm_on = 0;
            buzzer_timer_on = 0;
        }

        vTaskDelay(pdMS_TO_TICKS(BUZZER_TASK_DELAY));
    }
}