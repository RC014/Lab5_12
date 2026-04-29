#include "dd_relay.h"

static dd_relay_state_t s_state = DD_RELAY_STATE_OFF;

static inline void writeRelay(dd_relay_state_t state)
{
  const uint8_t pinLevelOn  = (RELAY_ACTIVE_HIGH ? HIGH : LOW);
  const uint8_t pinLevelOff = (RELAY_ACTIVE_HIGH ? LOW : HIGH);
  digitalWrite(RELAY_PIN, (state == DD_RELAY_STATE_ON) ? pinLevelOn : pinLevelOff);
}

void ddRelayInit(void)
{
  pinMode(RELAY_PIN, OUTPUT);
  s_state = DD_RELAY_STATE_OFF;
  writeRelay(s_state);
}

void ddRelayOn(void)
{
  s_state = DD_RELAY_STATE_ON;
  writeRelay(s_state);
}

void ddRelayOff(void)
{
  s_state = DD_RELAY_STATE_OFF;
  writeRelay(s_state);
}

dd_relay_state_t ddRelayGetState(void)
{
  return s_state;
}

