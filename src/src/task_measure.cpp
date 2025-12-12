#include <Arduino.h>
#include <FreeRTOS.h>
#include <task.h>
#include "shared.h"

const int NUM_SAMPLES = 10;

float rpmHistory[NUM_SAMPLES] = {0};
int historyIndex = 0;

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

                float instantRPM = 60000000.0 / interval;

                rpmHistory[historyIndex] = instantRPM;
                historyIndex = (historyIndex + 1) % NUM_SAMPLES;

                float sum = 0;
                for (int i = 0; i < NUM_SAMPLES; i++) {
                    sum += rpmHistory[i];

                }

                currentRPM = sum / NUM_SAMPLES;
            }

        }
        
        if (micros() - lastPulseTime > 1000000) {

            currentRPM = 0;
            for (int i = 0; i < NUM_SAMPLES; i++) {
                rpmHistory[i] = 0.0;
            }
        }
        
        vTaskDelay(pdMS_TO_TICKS(20));

    }
}