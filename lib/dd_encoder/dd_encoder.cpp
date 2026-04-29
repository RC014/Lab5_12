#include "dd_encoder.h"

static volatile long s_deltaTicks = 0L;
static volatile long s_positionTicks = 0L;

static void encoderIsr(void)
{
  const int dtLevel = digitalRead(ENCODER_DT_PIN);
  if (dtLevel == HIGH)
  {
    s_deltaTicks++;
    s_positionTicks++;
  }
  else
  {
    s_deltaTicks--;
    s_positionTicks--;
  }
}

void ddEncoderInit(void)
{
  pinMode(ENCODER_CLK_PIN, INPUT_PULLUP);
  pinMode(ENCODER_DT_PIN, INPUT_PULLUP);
  pinMode(ENCODER_SW_PIN, INPUT_PULLUP);

  s_deltaTicks = 0L;
  s_positionTicks = 0L;
  attachInterrupt(digitalPinToInterrupt(ENCODER_CLK_PIN), encoderIsr, RISING);
}

float ddEncoderReadRpmAndReset(unsigned long sampleWindowMs)
{
  if (sampleWindowMs == 0UL || ENCODER_PPR == 0)
  {
    return 0.0f;
  }

  noInterrupts();
  long ticks = s_deltaTicks;
  s_deltaTicks = 0L;
  interrupts();

  if (ticks < 0)
  {
    ticks = -ticks;
  }

  const float pulsesPerMinute = (float)ticks * (60000.0f / (float)sampleWindowMs);
  return pulsesPerMinute / (float)ENCODER_PPR;
}

long ddEncoderGetPositionTicks(void)
{
  noInterrupts();
  long ticks = s_positionTicks;
  interrupts();
  return ticks;
}

void ddEncoderResetPositionTicks(long value)
{
  noInterrupts();
  s_positionTicks = value;
  interrupts();
}
