#include "dd_serial_stdio.h"

int ddSerialGetChar(FILE *f)
{
    while (!Serial.available()) // asteptam pana cand sunt date disponibile
    {
        // Evită busy-wait agresiv; pe FreeRTOS va ceda CPU-ul către alte task-uri.
        delay(1);
    }

    int c = Serial.read();

    // Unele terminale trimit doar CR la Enter; stdio (fgets) așteaptă LF.
    if (c == '\r')
        c = '\n';

    return c; // returnam caracterul citit
}
int ddSerialPutChar(char ch, FILE *f)

{
    return Serial.write(ch); // scriem caracterul pe seriala
}
void ddSerialStdioSetup()
{
    Serial.begin(SERIAL_BAUDRATE);
    FILE *srv_serial_stream = fdevopen(ddSerialPutChar,
                                       ddSerialGetChar); // asociem functiile de citire/scriere cu un flux
    stdin = srv_serial_stream;                           // redirectionam intrarea standard
    stdout = srv_serial_stream;                          // redirectionam iesirea standard
    printf("\r\nsrvSerial Started\n");
}