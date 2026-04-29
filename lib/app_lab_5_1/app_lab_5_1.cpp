#include "app_lab_5_1.h"

static float s_setPointRpm = 0.0f;
static float s_measuredRpm = 0.0f;
static float s_pidOutput = 0.0f;
static unsigned long s_lastControlMs = 0UL;
static unsigned long s_lastStatusMs = 0UL;

static void tryReadSetPointFromSerial(void)
{
  if (!Serial.available())
  {
    return;
  }

  int newSetPoint = 0;
  if (scanf("%d", &newSetPoint) == 1)
  {
    if (newSetPoint < 0)
    {
      newSetPoint = 0;
    }
    s_setPointRpm = (float)newSetPoint;
    printf("SetPoint nou: %d RPM\r\n", newSetPoint);
  }
}

static void runControlStep(void)
{
  const unsigned long now = millis();
  if ((now - s_lastControlMs) < CONTROL_PERIOD_MS)
  {
    return;
  }
  s_lastControlMs = now;

  s_measuredRpm = ddEncoderReadRpmAndReset(CONTROL_PERIOD_MS);
  s_pidOutput = srvPidCompute(s_setPointRpm, s_measuredRpm);

  int8_t motorPercent = (int8_t)(s_pidOutput / 2.55f);
  if (motorPercent < 0)
  {
    motorPercent = 0;
  }
  if (motorPercent > 100)
  {
    motorPercent = 100;
  }
  srvDcMotorSetPower(motorPercent);
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
  printf("SP=%d RPM | PV=%d RPM | OUT=%d | PWM=%d%%\r\n",
         (int)s_setPointRpm,
         (int)s_measuredRpm,
         (int)s_pidOutput,
         motorState.power_percent);
}

void app_lab_5_1_setup(void)
{
  ddSerialStdioSetup();
  ddEncoderInit();
  srvDcMotorInit();
  srvPidInit(0.35f, 0.12f, 0.03f, 0.0f, 255.0f);
  s_lastControlMs = millis();
  s_lastStatusMs = millis();

  printf("\r\nControl PID turatie motor - Lab 5\r\n");
  printf("Introdu SetPoint RPM (ex: 120) si ENTER.\r\n");
  printf("Encoder PPR=%d, perioada control=%d ms\r\n", ENCODER_PPR, CONTROL_PERIOD_MS);
}

void app_lab_5_1_loop(void)
{
  tryReadSetPointFromSerial();
  runControlStep();
  printStatusPeriodically();
}

