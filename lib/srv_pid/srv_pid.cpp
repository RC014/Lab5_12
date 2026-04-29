#include "srv_pid.h"

typedef struct
{
  float kp;
  float ki;
  float kd;
  float outMin;
  float outMax;
  float integral;
  float prevError;
  unsigned long prevTimeMs;
} pid_state_t;

static pid_state_t s_pid;

static float clampFloat(float value, float minValue, float maxValue)
{
  if (value < minValue)
  {
    return minValue;
  }
  if (value > maxValue)
  {
    return maxValue;
  }
  return value;
}

void srvPidInit(float kp, float ki, float kd, float outMin, float outMax)
{
  s_pid.kp = kp;
  s_pid.ki = ki;
  s_pid.kd = kd;
  s_pid.outMin = outMin;
  s_pid.outMax = outMax;
  s_pid.integral = 0.0f;
  s_pid.prevError = 0.0f;
  s_pid.prevTimeMs = millis();
}

float srvPidCompute(float setPoint, float processValue)
{
  const unsigned long nowMs = millis();
  float dt = (float)(nowMs - s_pid.prevTimeMs) / 1000.0f;
  if (dt <= 0.0f)
  {
    dt = (float)CONTROL_PERIOD_MS / 1000.0f;
  }

  const float error = setPoint - processValue;
  s_pid.integral += error * dt;

  const float derivative = (error - s_pid.prevError) / dt;
  float output = (s_pid.kp * error) + (s_pid.ki * s_pid.integral) + (s_pid.kd * derivative);

  output = clampFloat(output, s_pid.outMin, s_pid.outMax);
  if (output == s_pid.outMin || output == s_pid.outMax)
  {
    s_pid.integral -= error * dt;
  }

  s_pid.prevError = error;
  s_pid.prevTimeMs = nowMs;
  return output;
}
