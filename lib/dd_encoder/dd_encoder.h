#ifndef DD_ENCODER_H_
#define DD_ENCODER_H_

#include <Arduino.h>

#include "../../include/config.h"

void ddEncoderInit(void);
float ddEncoderReadRpmAndReset(unsigned long sampleWindowMs);
long ddEncoderGetPositionTicks(void);
void ddEncoderResetPositionTicks(long value);

#endif
