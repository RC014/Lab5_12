#ifndef SRV_DC_MOTOR_H_
#define SRV_DC_MOTOR_H_

#include <stdint.h>

typedef struct {
  int8_t power_percent;  // -100..100
} srv_dc_motor_state_t;

void srvDcMotorInit(void);
void srvDcMotorSetPower(int8_t percent);
void srvDcMotorStop(void);
void srvDcMotorMax(void);
void srvDcMotorInc(void);
void srvDcMotorDec(void);
srv_dc_motor_state_t srvDcMotorGetState(void);

#endif /* SRV_DC_MOTOR_H_ */

