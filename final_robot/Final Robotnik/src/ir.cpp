#include "ir.h"
#include "pins.h"

const int NUM_IR_SENSORS=8;
int ir_values[8]={0,0,0,0,0,0,0,0};

void readIR() {
    for (int i = 0; i < NUM_IR_SENSORS; i++) {
        ir_values[i] = digitalRead(IRSensorPins[i]);
    }
}
