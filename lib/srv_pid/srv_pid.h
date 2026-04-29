#ifndef SRV_PID_H_
#define SRV_PID_H_

#include <Arduino.h>

#include "../../include/config.h"

void srvPidInit(float kp, float ki, float kd, float outMin, float outMax);
float srvPidCompute(float setPoint, float processValue);

#endif
