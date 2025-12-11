#include <Arduino.h>
#include <FreeRTOS.h>
#include <task.h>
#include "config.h"
#include "shared.h"


extern void onSensorPulse();
extern void TaskMeasure(void *pvParameters);
extern void TaskPrint(void *pvParameters);

void setup() {
  Serial.begin(BAUD_RATE);
  
  pinMode(PIN_SENSOR_IRQ, INPUT);
  attachInterrupt(digitalPinToInterrupt(PIN_SENSOR_IRQ), onSensorPulse, RISING);

  xTaskCreate(TaskMeasure, "Measure Task", 1024, NULL, 2, NULL);
  xTaskCreate(TaskPrint, "Print Task", 1024, NULL, 1, NULL);

}

void loop() {
  // Empty. Tasks are running in FreeRTOS.
}