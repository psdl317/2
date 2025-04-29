#include <xc.h>

// CONFIGURATION BITS (important!)
#pragma config FOSC = INTOSCIO_EC  // Internal Oscillator, port function on RA6 and RA7
#pragma config WDT = OFF            // Watchdog Timer 
#pragma config LVP = OFF            // Low Voltage Programming OFF
#pragma config PBADEN = OFF         // PortB Analog input disabled

// Define internal clock frequency
#define _XTAL_FREQ 8000000   // 8 MHz (default internal oscillator frequency)

void main(void) {
    OSCCON = 0x70;   // Set internal oscillator to 8 MHz (SCS bits select internal oscillator)

    TRISD0 = 0;      // Set RD0 as output

    while (1) {
        LATDbits.LATD0 = 1;  // LED ON
        __delay_ms(500);     // Delay 500ms

        LATDbits.LATD0 = 0;  // LED OFF
        __delay_ms(500);     // Delay 500ms
    }
}
