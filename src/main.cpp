#include <Arduino.h>
#include "../include/config.h"

#if ACTIVE_APP_LAB == 51
#include "../lib/app_lab_5_1/app_lab_5_1.h"
#elif ACTIVE_APP_LAB == 52
#include "../lib/app_lab_5_2/app_lab_5_2.h"
#endif

void setup(void)
{
#if ACTIVE_APP_LAB == 51
  app_lab_5_1_setup();
#elif ACTIVE_APP_LAB == 52
  app_lab_5_2_setup();
#endif
}

void loop(void)
{
#if ACTIVE_APP_LAB == 51
  app_lab_5_1_loop();
#elif ACTIVE_APP_LAB == 52
  app_lab_5_2_loop();
#endif
}
