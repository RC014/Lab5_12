#ifndef DD_ENCODER_H_
#define DD_ENCODER_H_

void ddEncoderInit(void);
float ddEncoderReadRpmAndReset(unsigned long sampleWindowMs);
long ddEncoderGetPositionTicks(void);
void ddEncoderResetPositionTicks(long value);

#endif
