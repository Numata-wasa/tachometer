#include "shared.h"

volatile unsigned long lastPulseTime = 0;
volatile unsigned long pulseInterval = 0;
volatile bool newPulseDetected = false;

volatile float currentRPM = 0.0;
