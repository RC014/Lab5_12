#ifndef DD_RELAY_H_
#define DD_RELAY_H_

#include <stdint.h>
#include <Arduino.h>

#include "../../include/config.h"

typedef enum {
  DD_RELAY_STATE_OFF = 0,
  DD_RELAY_STATE_ON  = 1
} dd_relay_state_t;

void ddRelayInit(void);
void ddRelayOn(void);
void ddRelayOff(void);
dd_relay_state_t ddRelayGetState(void);

#endif /* DD_RELAY_H_ */

