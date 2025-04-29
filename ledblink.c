#include<xc.h>
#include<pic18f4550.h>

void delay(unsigned int time) {
    for (int i=0; i<time; i++) {
        for (int j=0; j<5000; j++) {

        }
    }
}
void main(void) {
    TRISD = 0x00;
    LATD = 0xFF;

    while (1) {
        LATD = ~ LATD;
        delay(100);
    }
    return ;
}