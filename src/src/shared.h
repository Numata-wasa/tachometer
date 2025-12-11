#pragma once
#include <Arduino.h>

extern volatile unsigned long lastPulseTime;
extern volatile unsigned long pulseInterval;
extern volatile bool newPulseDetected;

extern volatile float currentRPM;
