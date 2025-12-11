#include <Arduino.h>
#include <FreeRTOS.h>
#include <task.h>
#include "shared.h"

void TaskPrint(void *pvParameters) {
    (void) pvParameters;

    while (1) {
        Serial.print("RPM: ");
        Serial.println(currentRPM);

        vTaskDelay(pdMS_TO_TICKS(200));
    }
}