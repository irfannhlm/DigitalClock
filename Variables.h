/* cc: Irfan Nurhakim Hilmi - 2025
* Header file for all global variables declarations
*/

#define VARIABLES_DECLARED

// button task global variables
extern int button_clicked, button_held;
extern int button_processed;

// buzzer task global variables
extern int buzzer_alarm_on, buzzer_timer_on;

// lcd task global variables
extern int lcd_cursor_pos, lcd_page_num;
extern int lcd_clock_mode, lcd_alarm_mode, lcd_timer_mode;

// clock task global variables
#define WIFI_SSID "IpronsWiFi"
#define WIFI_PASSWORD "Nurhakim!nt3rnet"
extern struct tm timeinfo;

// alarm task global variables
extern int alarm_hour, alarm_minute, alarm_second;

// timer task global variables
extern int timer_hour, timer_minute, timer_second;

// dht task global variables
extern float dht_humid, dht_temp;