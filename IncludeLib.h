/* cc: Irfan Nurhakim Hilmi - 2025
* Header file to include all library used
*/

#define LIBRARY_INCLUDED

#include <LiquidCrystal_I2C.h>
#include <ESP32Time.h>
#include <DHT.h>
#include "WiFi.h"
#include "Wire.h"
#include "time.h"

#include "PinDefine.h"
#include "Variables.h"
#include "srcs/ButtonTask.cpp"
#include "srcs/BuzzerTask.cpp"
#include "srcs/LCDTask.cpp"
#include "srcs/AlarmTask.cpp"
#include "srcs/TimerTask.cpp"
#include "srcs/ClockTask.cpp"
#include "srcs/DHTTask.cpp"