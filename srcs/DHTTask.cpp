/* cc: Irfan Nurhakim Hilmi - 2025
* RTOS task for DHT sensor reading
* will read temperature and humidity values from DHT sensor
*/

#ifndef PIN_DEFINED
    #include "PinDefine.h"
#endif

#ifndef VARIABLES_DECLARED
    #include "Variables.h"
#endif

#ifndef LIBRARY_INCLUDED
    #include <DHT.h>
#endif

#define DHT_TASK_DELAY 1000 // 1s delay for sensor reading update

DHT dht(PIN_DHT, DHT11);

float dht_humid, dht_temp = 0.0;

void dhtTask(void *pvParam) {
    // Task setup
    dht.begin();

    // Task loop
    while (1) {

        // read humidity and temperature from dht11 sensor
        dht_humid = dht.readHumidity();
        dht_temp = dht.readTemperature();

        vTaskDelay(pdMS_TO_TICKS(DHT_TASK_DELAY));
    }
}