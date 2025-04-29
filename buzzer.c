#include <xc.h>
#include <pic18f4550.h>

// CONFIG BITS (you may adjust these in MPLAB X GUI if not here)
#pragma config FOSC = INTOSC_EC   // Using internal oscillator
#pragma config WDT = OFF
#pragma config LVP = OFF
#pragma config PBADEN = OFF

#define _XTAL_FREQ 8000000        // Define system clock (8 MHz)
#define Buzzer LATAbits.LATA5     // Buzzer connected to RA5

unsigned int count = 0;

// ---- Interrupt Service Routine ----
void __interrupt() Timer1_ISR(void) {
    if (TMR1IF) {
        TMR1L = 0x20;             // Reload Timer1
        TMR1H = 0xD1;
        count++;
        if (count >= 1000) {      // Toggle every 1 second
            Buzzer ^= 1;          // Toggle RA5
            count = 0;
        }
        TMR1IF = 0;               // Clear Timer1 interrupt flag
    }
}

void main(void) {
    OSCCON = 0x72;                // Set internal oscillator to 8 MHz

    TRISAbits.TRISA5 = 0;         // Set RA5 as output
    TRISB = 0xFF;                 // Port B as input (optional)

    Buzzer = 0;                   // Buzzer initially off

    // ---- Timer1 Configuration ----
    T1CON = 0x20;                 // Prescaler 1:4, internal clock (Fosc/4)
    TMR1L = 0x20;                 // Load Timer1 low byte
    TMR1H = 0xD1;                 // Load Timer1 high byte
    TMR1IF = 0;                   // Clear interrupt flag
    TMR1IE = 1;                   // Enable Timer1 interrupt

    PEIE = 1;                     // Enable peripheral interrupts
    GIE = 1;                      // Enable global interrupts

    TMR1ON = 1;                   // Start Timer1

    while (1);                    // Infinite loop; ISR handles buzzer
}
