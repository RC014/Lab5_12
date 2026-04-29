#ifndef DD_SERIAL_STDIO_H_
#define DD_SERIAL_STDIO_H_

#include <stdio.h>
#include <Arduino.h>

#include "../../include/config.h"

int ddSerialPutChar(char ch, FILE *f);
int ddSerialGetChar(FILE *f);
void ddSerialStdioSetup();
#endif // SRV_SERIAL_STDIO_H_