/* cc: Irfan Nurhakim Hilmi - 2025
* RTOS task for clock update
* will update clock based on RTC and button clicks
*/

#ifndef PIN_DEFINED
    #include "PinDefine.h"
#endif

#ifndef VARIABLES_DECLARED
    #include "Variables.h"
#endif

#ifndef LIBARIES_INCLUDED
    #include <ESP32Time.h>
    #include "time.h"
#endif

#define CLOCK_TASK_DELAY 200 // 200ms delay for clock update

// ntp server parameters
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = TIME_ZONE*3600;
const int   daylightOffset_sec = 0;

ESP32Time rtc(daylightOffset_sec);
struct tm timeinfo;

void clockTask(void *pvParam) {
    // Task setup

    // SETUP TIME FROM NTP
    // connect to Wi-Fi
    Serial.print("Connecting to ");
    Serial.println(WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        vTaskDelay(pdMS_TO_TICKS(500));
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected.");

    // init and get the time
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    if(!getLocalTime(&timeinfo)) {
        Serial.println("Failed to obtain time");
        ESP.restart();
    }

    //disconnect WiFi as it's no longer needed
    WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);
    
    // Task loop
    while (1) {
        if (lcd_clock_mode) { // clock manual set mode
            if (button_clicked == 3) { // decrement clock
                switch (lcd_cursor_pos) {
                case 7: // X0:00:00
                    timeinfo.tm_hour = (timeinfo.tm_hour-10>=0) ? timeinfo.tm_hour-10 : timeinfo.tm_hour;
                    break;
                case 8: // 0X:00:00
                    timeinfo.tm_hour = (timeinfo.tm_hour-1>=0) ? timeinfo.tm_hour-1 : timeinfo.tm_hour;
                    break;
                case 10: // 00:X0:00
                    timeinfo.tm_min = (timeinfo.tm_min-10>=0) ? timeinfo.tm_min-10 : timeinfo.tm_min;
                    break;
                case 11: // 00:0X:00
                    timeinfo.tm_min = (timeinfo.tm_min-1>=0) ? timeinfo.tm_min-1 : timeinfo.tm_min;
                    break;
                case 13: // 00:00:X0
                    timeinfo.tm_sec = (timeinfo.tm_sec-10>=0) ? timeinfo.tm_sec-10 : timeinfo.tm_sec;
                    break;
                case 14: // 00:00:0X
                    timeinfo.tm_sec = (timeinfo.tm_sec-1>=0) ? timeinfo.tm_sec-1 : timeinfo.tm_sec;
                    break;
                default:
                    break;
                }
                button_clicked = 0;

            } else if (button_clicked == 4) {
                switch (lcd_cursor_pos) { // increment clock
                case 7: // X0:00:00
                    timeinfo.tm_hour = (timeinfo.tm_hour+10<24) ? timeinfo.tm_hour+10 : timeinfo.tm_hour;
                    break;
                case 8: // 0X:00:00
                    timeinfo.tm_hour = (timeinfo.tm_hour+1<24) ? timeinfo.tm_hour+1 : timeinfo.tm_hour;
                    break;
                case 10: // 00:X0:00
                    timeinfo.tm_min = (timeinfo.tm_min+10<60) ? timeinfo.tm_min+10 : timeinfo.tm_min;
                    break;
                case 11: // 00:0X:00
                    timeinfo.tm_min = (timeinfo.tm_min+1<60) ? timeinfo.tm_min+1 : timeinfo.tm_min;
                    break;
                case 13: // 00:00:X0
                    timeinfo.tm_sec = (timeinfo.tm_sec+10<60) ? timeinfo.tm_sec+10 : timeinfo.tm_sec;
                    break;
                case 14: // 00:00:0X
                    timeinfo.tm_sec = (timeinfo.tm_sec+1<60) ? timeinfo.tm_sec+1 : timeinfo.tm_sec;
                    break;
                default:
                    break;
                }
                button_clicked = 0;
            }

            // set internal RTC
            rtc.setTimeStruct(timeinfo);

        } else { // continue time update from RTC
            timeinfo = rtc.getTimeStruct();
        }

        vTaskDelay(pdMS_TO_TICKS(CLOCK_TASK_DELAY));
    }
}

