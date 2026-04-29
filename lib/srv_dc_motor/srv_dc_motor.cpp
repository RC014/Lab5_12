#include "srv_dc_motor.h"

static srv_dc_motor_state_t s_state = { 0 };

static uint8_t percentToDuty(int8_t percent)
{
  if (percent < 0) percent = (int8_t)(-percent);
  if (percent > 100) percent = 100;
  return (uint8_t)((percent * 255) / 100);
}

static dd_l298_dir_t percentToDir(int8_t percent)
{
  if (percent > 0) return DD_L298_DIR_FWD;
  if (percent < 0) return DD_L298_DIR_REV;
  return DD_L298_DIR_STOP;
}

static void applyToHardware(void)
{
  dd_l298_dir_t dir  = percentToDir(s_state.power_percent);
  uint8_t      duty = percentToDuty(s_state.power_percent);
  ddL298Set(dir, duty);
}

void srvDcMotorInit(void)
{
  ddL298Init();
  s_state.power_percent = 0;
  applyToHardware();
}

void srvDcMotorSetPower(int8_t percent)
{
  if (percent > 100)  percent = 100;
  if (percent < -100) percent = -100;
  s_state.power_percent = percent;
  applyToHardware();
}

void srvDcMotorStop(void)
{
  s_state.power_percent = 0;
  applyToHardware();
}

void srvDcMotorMax(void)
{
  if (s_state.power_percent > 0)
    s_state.power_percent = 100;
  else if (s_state.power_percent < 0)
    s_state.power_percent = -100;
  else
    s_state.power_percent = 100; // dacă era 0, alegem înainte

  applyToHardware();
}

void srvDcMotorInc(void)
{
  if (s_state.power_percent >= 0)
  {
    s_state.power_percent += MOTOR_STEP_PERCENT;
    if (s_state.power_percent > 100) s_state.power_percent = 100;
  }
  else
  {
    s_state.power_percent += MOTOR_STEP_PERCENT;
    if (s_state.power_percent > 0) s_state.power_percent = 0;
  }
  applyToHardware();
}

void srvDcMotorDec(void)
{
  if (s_state.power_percent <= 0)
  {
    s_state.power_percent -= MOTOR_STEP_PERCENT;
    if (s_state.power_percent < -100) s_state.power_percent = -100;
  }
  else
  {
    s_state.power_percent -= MOTOR_STEP_PERCENT;
    if (s_state.power_percent < 0) s_state.power_percent = 0;
  }
  applyToHardware();
}

srv_dc_motor_state_t srvDcMotorGetState(void)
{
  return s_state;
}

