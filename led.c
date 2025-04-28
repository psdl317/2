#include <xc.h> 

void delay(unsigned int time) { 
    unsigned int i, j; 
    for (i = 0; i < time; i++) { 
        for (j = 0; j < 5000; j++) { 
            // crude delay
        } 
    } 
} 

void main(void) { 
    TRISD = 0x00;    
    LATD = 0xFF;     
    
    while (1) { 
        LATD = ~LATD;  
        delay(1000);   
    } 
}
