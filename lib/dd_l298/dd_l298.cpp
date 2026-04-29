#include "dd_l298.h"

void ddL298Init(void)
{
  pinMode(L298_ENA_PIN, OUTPUT);
  pinMode(L298_IN1_PIN, OUTPUT);
  pinMode(L298_IN2_PIN, OUTPUT);

  digitalWrite(L298_IN1_PIN, LOW);
  digitalWrite(L298_IN2_PIN, LOW);
  analogWrite(L298_ENA_PIN, 0);
}

void ddL298Set(dd_l298_dir_t dir, uint8_t duty)
{
  switch (dir)
  {
    case DD_L298_DIR_FWD:
      digitalWrite(L298_IN1_PIN, HIGH);
      digitalWrite(L298_IN2_PIN, LOW);
      break;
    case DD_L298_DIR_REV:
      digitalWrite(L298_IN1_PIN, LOW);
      digitalWrite(L298_IN2_PIN, HIGH);
      break;
    default:
      digitalWrite(L298_IN1_PIN, LOW);
      digitalWrite(L298_IN2_PIN, LOW);
      duty = 0;
      break;
  }

  analogWrite(L298_ENA_PIN, duty);
}

