#include <xc.h>
#include <pic18f4550.h>

// CONFIG bits setting (if required), else set externally

#define _XTAL_FREQ 8000000  // 8 MHz oscillator frequenc

void timer2Init(void) {
    T2CON = 0b00000100; // Timer2 ON, Prescaler 1:1
    PR2 = 0x95;         // Set period register for PWM
}

void delay(unsigned int time) {
    unsigned int i, j;
    for(i = 0; i < time; i++) {
        for(j = 0; j < 1000; j++);
    }
}

void main(void) {
    unsigned int i;

    TRISCbits.TRISC1 = 0;   // CCP2 output pin
    TRISCbits.TRISC2 = 0;   // CCP1 output pin (PWM output)
    LATCbits.LATC1 = 0;     // Clear output initially

    CCP1CON = 0b00001100;   // PWM mode for CCP1
    CCPR1L = 0x0F;          // Initial PWM duty cycle low

    timer2Init();           // Initialize Timer2
    T2CONbits.TMR2ON = 1;   // Start Timer2

    while (1) {
        // Gradually increase duty cycle
        for(i = 15; i < 150; i++) {
            CCPR1L = i;
            delay(100);
        }

        // Gradually decrease duty cycle
        for(i = 150; i > 15; i--) {
            CCPR1L = i;
            delay(100);
        }
    }
}
