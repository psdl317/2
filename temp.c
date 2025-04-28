#include <pic18f4550.h> 
#include <xc.h> 
#include <stdio.h>

#define LCD_EN LATAbits.LATA1
#define LCD_RS LATAbits.LATA0
#define LCDPORT LATB

unsigned char str[16];

void lcd_delay(unsigned int time) { 
    unsigned int i, j; 
    for(i = 0; i < time; i++) { 
        for(j = 0; j < 100; j++) { } 
    }
} 

void SendInstruction(unsigned char command) { 
    LCD_RS = 0; 
    LCDPORT = command; 
    LCD_EN = 1; 
    lcd_delay(10); 
    LCD_EN = 0; 
    lcd_delay(10); 
} 

void SendData(unsigned char lcddata) { 
    LCD_RS = 1; 
    LCDPORT = lcddata; 
    LCD_EN = 1; 
    lcd_delay(10); 
    LCD_EN = 0; 
    lcd_delay(10); 
} 

void InitLCD(void) { 
    ADCON1 = 0x0F;           // Configure all pins as digital
    TRISB = 0x00;            // LCD data port as output
    TRISAbits.RA0 = 0;       // RS pin as output
    TRISAbits.RA1 = 0;       // EN pin as output
    
    SendInstruction(0x38);   // 8-bit, 2 line
    SendInstruction(0x06);   // Entry mode
    SendInstruction(0x0C);   // Display ON, Cursor OFF
    SendInstruction(0x01);   // Clear display
    SendInstruction(0x80);   // Move cursor to home
}

void LCD_display(unsigned int row, unsigned int pos, unsigned char *ch) { 
    if (row == 1) {
        SendInstruction(0x80 | (pos - 1)); 
    } else {
        SendInstruction(0xC0 | (pos - 1)); 
    }
    while (*ch) { 
        SendData(*ch++); 
    } 
} 

void ADCInit(void) { 
    TRISEbits.RE2 = 1;        // AN7 input (Temperature sensor)
    ADCON1 = 0x0F;            // Configure analog pins
    ADCON2 = 0b10101110;      // ADC settings: Right justified, 12 TAD, Fosc/64
} 

unsigned short Read_Temp(void) { 
    ADCON0 = 0b00011101;      // Select channel AN7
    GO_DONE = 1;              // Start conversion
    while (GO_DONE == 1);     // Wait for conversion to complete
    return ADRES;             // Return ADC result
} 

void main(void) { 
    unsigned int temp; 
    
    InitLCD(); 
    ADCInit(); 
    
    LCD_display(1, 1, "Temp Hinjawadi");
    
    while (1) { 
        temp = Read_Temp(); 
        temp = ((temp * 500) / 1023); // Convert ADC value to temperature (approx)
        sprintf(str, "%d C", temp);   // Convert int to string
        
        LCD_display(2, 1, str);        // Show temp on 2nd line
        lcd_delay(9000);               // Delay
    } 
}
