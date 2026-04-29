#include "app_lab_5_2.h"

#include <stdio.h>

#include "../../include/config.h"
#include "../dd_serial_stdio/dd_serial_stdio.h"
#include "../dd_encoder/dd_encoder.h"
#include "../srv_dc_motor/srv_dc_motor.h"

typedef enum
{
  CTRL_STATE_OFF = 0,
  CTRL_STATE_ON_FWD,
  CTRL_STATE_ON_REV
} control_state_t;

static long s_setPointTicks = 0;
static long s_currentTicks = 0;
static control_state_t s_state = CTRL_STATE_OFF;
static unsigned long s_lastControlMs = 0UL;
static unsigned long s_lastStatusMs = 0UL;

static const char *stateToString(control_state_t state)
{
  if (state == CTRL_STATE_ON_FWD)
  {
    return "ON_FWD";
  }
  if (state == CTRL_STATE_ON_REV)
  {
    return "ON_REV";
  }
  return "OFF";
}

static void tryReadSetPointFromSerial(void)
{
  if (!Serial.available())
  {
    return;
  }

  long newSetPoint = 0;
  if (scanf("%ld", &newSetPoint) == 1)
  {
    s_setPointTicks = newSetPoint;
    printf("SetPoint nou: %ld ticks\r\n", s_setPointTicks);
  }
}

static void runOnOffControlWithHysteresis(void)
{
  const unsigned long now = millis();
  if ((now - s_lastControlMs) < CONTROL_PERIOD_MS)
  {
    return;
  }
  s_lastControlMs = now;

  s_currentTicks = ddEncoderGetPositionTicks();
  const long lowerThreshold = s_setPointTicks - ONOFF_HYSTERESIS_TICKS;
  const long upperThreshold = s_setPointTicks + ONOFF_HYSTERESIS_TICKS;

  if (s_currentTicks < lowerThreshold)
  {
    s_state = CTRL_STATE_ON_FWD;
    srvDcMotorSetPower(ONOFF_SATURATION_POWER_PERCENT);
  }
  else if (s_currentTicks > upperThreshold)
  {
    s_state = CTRL_STATE_ON_REV;
    srvDcMotorSetPower(-ONOFF_SATURATION_POWER_PERCENT);
  }
  else
  {
    s_state = CTRL_STATE_OFF;
    srvDcMotorStop();
  }
}

static void printStatusPeriodically(void)
{
  const unsigned long now = millis();
  if ((now - s_lastStatusMs) < STATUS_PERIOD_MS)
  {
    return;
  }
  s_lastStatusMs = now;

  const srv_dc_motor_state_t motorState = srvDcMotorGetState();
  printf("SP=%ld ticks | PV=%ld ticks | H=%d | ST=%s | PWM=%d%%\r\n",
         s_setPointTicks,
         s_currentTicks,
         ONOFF_HYSTERESIS_TICKS,
         stateToString(s_state),
         motorState.power_percent);
}

void app_lab_5_2_setup(void)
{
  ddSerialStdioSetup();
  ddEncoderInit();
  ddEncoderResetPositionTicks(0);
  srvDcMotorInit();

  s_setPointTicks = 0;
  s_currentTicks = 0;
  s_state = CTRL_STATE_OFF;
  s_lastControlMs = millis();
  s_lastStatusMs = millis();

  printf("\r\nLab 5.2 - Control pozitie ON-OFF cu histereza\r\n");
  printf("Introdu SetPoint in ticks (ex: 100) si ENTER.\r\n");
  printf("Motor saturat la %d%%, histereza = +/- %d ticks\r\n",
         ONOFF_SATURATION_POWER_PERCENT,
         ONOFF_HYSTERESIS_TICKS);
}

void app_lab_5_2_loop(void)
{
  tryReadSetPointFromSerial();
  runOnOffControlWithHysteresis();
  printStatusPeriodically();
}
