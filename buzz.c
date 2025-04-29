#include <xc.h> 
#include <pic18f4550.h>
#define Buzzer LATAbits.LATA5

unsigned int count = 0;

void interrupt Timer1_ISR(void) { 
    if (TMR1IF == 1) { 
        TMR1L = 0x20; 
        TMR1H = 0xD1;  
        count++; 
        if (count >= 1000) { 
            Buzzer = ~Buzzer;  
            count = 0;
        } 
        TMR1IF = 0;  
    } 
} 

void main(void) { 
    TRISB = 0x00;              
    TRISAbits.TRISA5 = 0;       

    GIE = 1;                   // Global Interrupt Enable
    PEIE = 1;                  // Peripheral Interrupt Enable
    TMR1IE = 1;                // Timer1 Interrupt Enable
    TMR1IF = 0;                // Clear interrupt flag

    T1CON = 0x20;              // Timer1 ON, prescaler 1:4, internal cloc
    TMR1L = 0x20;              // Load Timer1 low byte
    TMR1H = 0xD1;              // Load Timer1 high byte
    TMR1ON = 1;                // Turn ON Timer1

    while (1);
}
