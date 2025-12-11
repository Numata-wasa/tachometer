#include <Arduino.h>
#include <FreeRTOS.h>
#include <task.h>
#include "shared.h"

void onSensorPulse() {
    unsigned long now = micros();
    unsigned long diff = now - lastPulseTime;

    if (diff > 1000) {
        pulseInterval = diff;
        lastPulseTime = now;
        newPulseDetected = true;
    }

}


void TaskMeasure(void *pvParameters){
    (void) pvParameters;

    while (1) {
        if (newPulseDetected) {
            taskENTER_CRITICAL();
            unsigned long interval = pulseInterval;
            newPulseDetected = false;
            taskEXIT_CRITICAL();

            if (interval >0) {
                currentRPM = 60000000.0 / interval;
            }

        }
        
        if (micros() - lastPulseTime > 1000000) {
            currentRPM = 0;
        }
        
        vTaskDelay(pdMS_TO_TICKS(20));

    }
}