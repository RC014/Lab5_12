#ifndef DD_L298_H_
#define DD_L298_H_

#include <stdint.h>

typedef enum {
  DD_L298_DIR_STOP = 0,
  DD_L298_DIR_FWD  = 1,
  DD_L298_DIR_REV  = -1
} dd_l298_dir_t;

void ddL298Init(void);
void ddL298Set(dd_l298_dir_t dir, uint8_t duty); // duty = 0..255

#endif /* DD_L298_H_ */

