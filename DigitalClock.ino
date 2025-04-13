#include "IncludeLib.h"

// task priorities | lower = less prioroty
#define BUTTON_TASK_PRIORITY 4
#define BUZZER_TASK_PRIORITY 3
#define LCD_TASK_PRIORITY 2
#define CLOCK_TASK_PRIORITY 3
#define ALARM_TASK_PRIORITY 3
#define TIMER_TASK_PRIORITY 4
#define DHT_TASK_PRIORITY 2


// task for debugging
void debugTask(void *pvParam) {
    // Task setup
    // Task loop
    while (1) {
        if (button_clicked) {
            Serial.print("Button clicked: ");
            Serial.println(button_clicked);
        }

        if (button_held) {
            Serial.print("Button held: ");
            Serial.println(button_held);
        }

        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void setup() {

    // Serial setup
    Serial.begin(115200);

    // Tasks setup
    xTaskCreatePinnedToCore(buzzerTask, "Buzzer Task", 2048, NULL, BUZZER_TASK_PRIORITY, NULL, 0); 
    xTaskCreatePinnedToCore(buttonTask, "Button Task", 2048, NULL, BUTTON_TASK_PRIORITY, NULL, 0); 
    xTaskCreatePinnedToCore(lcdTask, "LCD Task", 2048, NULL, LCD_TASK_PRIORITY, NULL, 0); 
    xTaskCreatePinnedToCore(clockTask, "Clock Task", 2048, NULL, CLOCK_TASK_PRIORITY, NULL, 0); 
    xTaskCreatePinnedToCore(alarmTask, "Alarm Task", 2048, NULL, ALARM_TASK_PRIORITY, NULL, 0); 
    xTaskCreatePinnedToCore(timerTask, "Timer Task", 2048, NULL, TIMER_TASK_PRIORITY, NULL, 0); 
    xTaskCreatePinnedToCore(dhtTask, "DHT Task", 2048, NULL, DHT_TASK_PRIORITY, NULL, 0); 
    // xTaskCreatePinnedToCore(debugTask, "Debug Task", 2048, NULL, 5, NULL, 0); 

    Serial.println("Tasks started!");
}

void loop() {   
}