#include <xc.h>

//
void main(void) {
    int i, j, t;
    int a[] = {0x01, 0x03, 0x06, 0x04, 0x07, 0x02, 0x05, 0x08};

    
    for (i = 0; i < 7; i++) {
        for (j = 0; j < 7 - i; j++) {
            if (a[j] > a[j + 1]) {
                t = a[j];
                a[j] = a[j + 1];
                a[j + 1] = t;
            }
        }
    }

    TRISD = 0; 

    while (1) {
        for (i = 0; i < 8; i++) {
            PORTD = a[i];
            for (int n = 0; n < 1000; n++) {
                for (int k = 0; k < 100; k++) {
                    
                }
            }
        }
    }
}
