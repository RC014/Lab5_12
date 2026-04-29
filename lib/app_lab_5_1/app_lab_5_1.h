#ifndef APP_LAB_5_1_H
#define APP_LAB_5_1_H

#include <Arduino.h>

#include <stdio.h>

#include "../../include/config.h"
#include "../dd_serial_stdio/dd_serial_stdio.h"
#include "../dd_encoder/dd_encoder.h"
#include "../srv_pid/srv_pid.h"
#include "../srv_dc_motor/srv_dc_motor.h"

void app_lab_5_1_setup(void);
void app_lab_5_1_loop(void);

#endif /* APP_LAB_5_1_H */

