/* cc: Irfan Nurhakim Hilmi - 2025
* RTOS task for LCD page update
* will update LCD display based on button clicks/holds
*/

#ifndef PIN_DEFINED
    #include "PinDefine.h"
#endif

#ifndef VARIABLES_DECLARED
    #include "Variables.h"
#endif

#ifndef LIBRARY_INCLUDED
    #include <LiquidCrystal_I2C.h>
    #include "time.h"
#endif

#define LCD_TASK_DELAY 200 // 200ms for lcd update

LiquidCrystal_I2C lcd(0x27, 16, 2);  

int lcd_page_num = 0; // 0: clock, 1: alarm, 2: timer
int lcd_cursor_pos = 8; // horizontal position of lcd cursor
int lcd_update_count = 0; // update counts for changing display

int lcd_clock_mode = 0; // 0: start clock, 1: manual set
int lcd_alarm_mode = 0; // 0: start alarm, 1: set alarm
int lcd_timer_mode = 1; // 0: start timer, 1: set timer

// dayname array for display
const char dayname_id[7][10] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"};

// additional characters


void pageUpdate() {
    char line[20];

    // always update lcd
    lcd.cursor_off();
    if (lcd_page_num == 0) { // clock update
        sprintf(line, "%02d:%02d:%02d", timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
    } else if (lcd_page_num == 1) { // alarm update
        sprintf(line, "%02d:%02d:%02d", alarm_hour, alarm_minute, alarm_second);
    } else { // timer update
        sprintf(line, "%02d:%02d:%02d", timer_hour, timer_minute, timer_second);
    }
    lcd.setCursor(7,0);
    lcd.print(line);

    // clock page dynamic display
    if (lcd_page_num == 0) {
        if (!lcd_clock_mode) {
            if (lcd_update_count%75 == 0) {
                // clear line
                sprintf(line, "                ");
                lcd.setCursor(0,1);
                lcd.print(line);
                // show date
                sprintf(line, "%s %02d/%02d/%02d", dayname_id[timeinfo.tm_wday], timeinfo.tm_mday, 
                    timeinfo.tm_mon+1, timeinfo.tm_year-100);
                lcd.setCursor(0,1);
                lcd.print(line);
            } else if (lcd_update_count%75 == 20) {
                // clear line
                sprintf(line, "                ");
                lcd.setCursor(0,1);
                lcd.print(line);
                // show temperature
                sprintf(line, "Temp: %.2fC", dht_temp);
                lcd.setCursor(0,1);
                lcd.print(line);
            } else if (lcd_update_count%75 == 30) {
                sprintf(line, "                ");
                lcd.setCursor(0,1);
                lcd.print(line);
                sprintf(line, "Humid: %.2f%", dht_humid);
                lcd.setCursor(0,1);
                lcd.print(line);
            } else if (lcd_update_count%75 == 40) {
                sprintf(line, " < | > | v | ^  ");
                lcd.setCursor(0,1);
                lcd.print(line);
            }
        } else {
            if (lcd_update_count%75 == 0 || lcd_update_count%75 == 15 || lcd_update_count%75 == 30) {
                sprintf(line, "Setting clock.  "); // show setting mode
                lcd.setCursor(0,1);
                lcd.print(line);    
            } else if (lcd_update_count%75 == 5 || lcd_update_count%75 == 20 || lcd_update_count%75 == 35) {
                sprintf(line, "Setting clock.. "); // show setting mode
                lcd.setCursor(0,1);
                lcd.print(line);    
            } else if (lcd_update_count%75 == 10 || lcd_update_count%75 == 25 || lcd_update_count%75 == 40) {
                sprintf(line, "Setting clock..."); // show setting mode
                lcd.setCursor(0,1);
                lcd.print(line);    
            } else if (lcd_update_count%75 == 45) {
                sprintf(line, " < | > | v | ^  "); // show controls
                lcd.setCursor(0,1);
                lcd.print(line);    
            }
        }

    // alarm page dynamic display
    } else if (lcd_page_num == 1) {
        if (!lcd_alarm_mode) {
            sprintf(line, " < | > | v | ^  "); // show controls
            lcd.setCursor(0,1);
            lcd.print(line);    
        } else {
            if (lcd_update_count%75 == 0 || lcd_update_count%75 == 15 || lcd_update_count%75 == 30) {
                sprintf(line, "Setting alarm.  "); // show setting mode
                lcd.setCursor(0,1);
                lcd.print(line);    
            } else if (lcd_update_count%75 == 5 || lcd_update_count%75 == 20 || lcd_update_count%75 == 35) {
                sprintf(line, "Setting alarm.. "); // show setting mode
                lcd.setCursor(0,1);
                lcd.print(line);    
            } else if (lcd_update_count%75 == 10 || lcd_update_count%75 == 25 || lcd_update_count%75 == 40) {
                sprintf(line, "Setting alarm..."); // show setting mode
                lcd.setCursor(0,1);
                lcd.print(line);    
            } else if (lcd_update_count%75 == 45) {
                sprintf(line, " < | > | v | ^  "); // show controls
                lcd.setCursor(0,1);
                lcd.print(line);    
            }
        }

    // timer page dynamic display
    } else if (lcd_page_num == 2) { 
        if (!lcd_timer_mode) {
            if (lcd_update_count%15 == 0) {
                sprintf(line, "Timer ticking.  "); // show timer ticking
                lcd.setCursor(0,1);
                lcd.print(line);    
            } else if (lcd_update_count%15 == 5) {
                sprintf(line, "Timer ticking.. "); // show timer ticking
                lcd.setCursor(0,1);
                lcd.print(line);    
            } else if (lcd_update_count%15 == 10) {
                sprintf(line, "Timer ticking..."); // show timer ticking
                lcd.setCursor(0,1);
                lcd.print(line);    
            }
        } else {
            if (lcd_update_count%75 == 0 || lcd_update_count%75 == 15 || lcd_update_count%75 == 30) {
                sprintf(line, "Setting timer.  "); // show setting mode
                lcd.setCursor(0,1);
                lcd.print(line);    
            } else if (lcd_update_count%75 == 5 || lcd_update_count%75 == 20 || lcd_update_count%75 == 35) {
                sprintf(line, "Setting timer.. "); // show setting mode
                lcd.setCursor(0,1);
                lcd.print(line);    
            } else if (lcd_update_count%75 == 10 || lcd_update_count%75 == 25 || lcd_update_count%75 == 40) {
                sprintf(line, "Setting timer..."); // show setting mode
                lcd.setCursor(0,1);
                lcd.print(line);    
            } else if (lcd_update_count%75 == 45) {
                sprintf(line, " < | > | v | ^  "); // show controls
                lcd.setCursor(0,1);
                lcd.print(line);    
            }
        }
    }

    // cursor control
    if ((lcd_page_num == 0 && lcd_clock_mode) || // digital clock manual set
        (lcd_page_num == 1 && lcd_alarm_mode) || // set alarm
        (lcd_page_num == 2 && lcd_timer_mode)    // set timer
        ) { 
        lcd.cursor_on();
        if (button_clicked == 1) {
            if (lcd_cursor_pos > 7) lcd_cursor_pos--;
            button_clicked = 0; 
        } else if (button_clicked == 2) {
            if (lcd_cursor_pos < 14) lcd_cursor_pos++;
            button_clicked = 0;
        }
        lcd.setCursor(lcd_cursor_pos,0);
    }
}

// setup each page based on page number
/*
    Clock: 00:00:00     Alarm: 00:00:00     Timer: 00:00:00
     < | > | v | ^       < | > | v | ^       < | > | v | ^ 
*/
void setPage() {
    lcd.clear();
    
    char line[20];
    if (lcd_page_num == 0) {
        sprintf(line, "Clock: %02d:%02d:%02d", timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
    } else if (lcd_page_num == 1) {
        sprintf(line, "Alarm: %02d:%02d:%02d", alarm_hour, alarm_minute, alarm_second);
    } else {
        sprintf(line, "Timer: %02d:%02d:%02d", timer_hour, timer_minute, timer_second);
    }
    lcd.setCursor(0,0);
    lcd.print(line);

    sprintf(line, " < | > | v | ^  ");
    lcd.setCursor(0,1);
    lcd.print(line);
}

void lcdTask(void *pvParam) {
    // Task setup
    lcd.init();
    lcd.backlight();
    
    // starts with clock page
    lcd_page_num = 0;
    setPage();
    
    // Task loop
    while (1) {
        switch (lcd_page_num) {
        case 0: // clock page
            if (button_held == 1) { // switch page to the left
                lcd_page_num = 2; // wrap around to timer page
                setPage(); 
                button_processed = 1;
            } else if (button_held == 2) { // switch page to the right
                lcd_page_num++;
                setPage();
                button_processed = 1;
            } else if (button_held == 3) { // switch clock mode
                lcd.setCursor(7,0);
                lcd_clock_mode = !lcd_clock_mode;
                button_processed = 1;
            }  else {
                pageUpdate();
            }
            break;

        case 1: // alarm page
            if (button_held == 1) { // switch page to the left
                lcd_page_num--;
                setPage();
                button_processed = 1;
            } else if (button_held == 2) { // switch page to the right
                lcd_page_num++;
                setPage();
                button_processed = 1;
            } else if (button_held == 3) { // switch alarm mode
                lcd.setCursor(7,0);
                lcd_alarm_mode = !lcd_alarm_mode;
                button_processed = 1;
            }   else {
                pageUpdate();
            }
            break;

        case 2: // timer page
            if (button_held == 1) { // switch page to the left
                lcd_page_num--;
                setPage();
                button_processed = 1;
            } else if (button_held == 2) { // switch page to the right
                lcd_page_num = 0; // wrap around to clock page
                setPage(); 
                button_processed = 1;
           } else if (button_held == 3) { // switch timer mode
                lcd.setCursor(7,0);
                lcd_timer_mode = !lcd_timer_mode;
                button_processed = 1;
            }   else {
                pageUpdate();
            }
            break;
        
        default:
            break;
        }

        lcd_update_count++;
        vTaskDelay(pdMS_TO_TICKS(LCD_TASK_DELAY));
    }
}