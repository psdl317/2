#include <xc.h>
#include <p18f4550.h>

#define LCD_EN LATAbits.LATA1
#define LCD_RS LATAbits.LATA0
#define LCDPORT LATB

void lcd_delay(unsigned int time) {
    unsigned int i, j;
    for(i = 0; i < time; i++) {
        for(j = 0; j < 100; j++) {}
    }
}

void SendInstruction(unsigned char command) {
    LCD_RS = 0;          // Instruction Register
    LCDPORT = command;   
    LCD_EN = 1;          
    lcd_delay(10);
    LCD_EN = 0;
    lcd_delay(10);
}

void SendData(unsigned char LcdData) {
    LCD_RS = 1;          // Data Register
    LCDPORT = LcdData;   
    LCD_EN = 1;
    lcd_delay(10);
    LCD_EN = 0;
    lcd_delay(10);
}

void initLCD(void) {
    ADCON1 = 0x0F;         // Configure all pins as digital
    TRISB = 0x00;          // LCD data port as output
    TRISAbits.TRISA0 = 0;  // RS pin as output
    TRISAbits.TRISA1 = 0;  // EN pin as output

    SendInstruction(0x38); // 8-bit mode, 2 line, 5x7 dots
    SendInstruction(0x06); // Entry mode
    SendInstruction(0x0C); // Display ON, Cursor OFF
    SendInstruction(0x01); // Clear Display
    SendInstruction(0x80); // Force cursor to beginning
}

void main(void) {
    unsigned char *string1 = "Microchip";
    unsigned char *string2 = "PIC18F4550";

    initLCD();

    while (*string1) {
        SendData(*string1);
        string1++;
    }

    SendInstruction(0xC0); // Move cursor to 2nd line

    while (*string2) {
        SendData(*string2);
        string2++;
    }

    while (1);
}
