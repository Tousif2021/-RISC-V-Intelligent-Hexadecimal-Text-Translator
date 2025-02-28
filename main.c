#include "gd32vf103.h"
#include "drivers.h"
#include "adc.h"
#include "lcd.h"
#include "usart.h"

int main(void) {
    int ms=0, s=0, key, pKey=-1, c=0, idle=0;
    int lookUpTbl[16]={1,4,7,14,2,5,8,0,3,6,9,15,10,11,12,13};
    int hexBuffer[2] = {0, 0};  
    int hexCount = 0;          
    int hexValue = 0;           
    int rxCol = 10;             
    char rxBuffer[16] = {0};
    int rxCount = 0;
    t5omsi();                   // Initialize timer5 1kHz
    colinit();                  // Initialize column toolbox
    l88init();                  // Initialize 8*8 led toolbox
    keyinit();                  // Initialize keyboard toolbox
    ADC3powerUpInit(1);         // Initialize ADC0, Ch3
    Lcd_SetType(LCD_NORMAL);    // or use LCD_INVERTED!
    Lcd_Init();
    LCD_Clear(DARKBLUE);
    LCD_ShowStr(10, 10, "Lab #5 By T. Dewan", WHITE, TRANSPARENT);
    LCD_ShowStr(10, 30, "Input: ", YELLOW, TRANSPARENT);
    
    u0init(1);
    eclic_global_interrupt_enable();  // !!! INTERRUPT ENABLED !!!
    
    while (1) {
        idle++;                       // Manage Async events
        LCD_WR_Queue();               // Manage LCD com queue!
        u0_TX_Queue();                // Manage U(S)ART TX Queue!
        
        if (usart_flag_get(USART0, USART_FLAG_RBNE)) {
            char receivedChar = usart_data_receive(USART0);
            
            rxBuffer[rxCount % 16] = receivedChar;
            LCD_FillRectangle(rxCol, 50, 20, 30, DARKBLUE);
            LCD_ShowChar(rxCol, 50, receivedChar, TRANSPARENT, GREEN);
            LCD_WR_Queue();
            rxCol += 15;
            
            if (rxCol > 150) {
                rxCol = 60;
                LCD_ShowStr(10, 30, "RX: ", WHITE, TRANSPARENT);
                LCD_ShowStr(60, 30, "                    ", BLUE, TRANSPARENT);
                LCD_FillRectangle(60, 30, 100, 30, DARKBLUE); 
                LCD_WR_Queue();
            }
            
            rxCount++;
        }
        
        if (t5expq()) {               // Manage periodic tasks
            l88row(colset());         // ...8*8LED and Keyboard
            ms++;                     // ...One second heart beat
            
            if (ms == 1000) {
                ms = 0;
                l88mem(0, s++);
            }
            
            if ((key = keyscan()) >= 0) {
                if (pKey != key) {
                    pKey = key;
                    
                    int hexDigit = lookUpTbl[key];
                    
                    if (key == 14) hexDigit = 0xE;  // * key
                    if (key == 13) hexDigit = 0xF;  // # key
                    
                    if (hexCount < 2) {
                        hexBuffer[hexCount] = hexDigit;
                        LCD_FillRectangle(70 + (hexCount * 15), 30, 20, 30, DARKBLUE);
                        char hexChar = (hexDigit < 10) ? ('0' + hexDigit) : ('A' + hexDigit - 10);
                        LCD_ShowChar(70 + (hexCount * 15), 30, hexChar, OPAQUE, CYAN);
                        LCD_WR_Queue();
                        l88mem(1, hexDigit);
                        
                        hexCount++;
                        if (hexCount == 2) {
                            hexValue = (hexBuffer[0] << 4) | hexBuffer[1];

                            if (hexValue >= 0x20 && hexValue <= 0x7F) {
                                usart_data_transmit(USART0, hexValue);
                                LCD_FillRectangle(70, 70, 30, 20, DARKBLUE);
                                // Display status
                                LCD_ShowStr(10, 70, "Sent: 0x    ", WHITE, TRANSPARENT);
                                LCD_ShowChar(70, 70, (hexBuffer[0] < 10) ? ('0' + hexBuffer[0]) : ('A' + hexBuffer[0] - 10), OPAQUE, WHITE);
                                LCD_ShowChar(80, 70, (hexBuffer[1] < 10) ? ('0' + hexBuffer[1]) : ('A' + hexBuffer[1] - 10), OPAQUE, WHITE);
                            } 
                            // Reset for next input
                            hexCount = 0;
                            LCD_FillRectangle(70, 50, 30, 20, DARKBLUE);
                        }
                    }
                }
            } else {
                pKey = -1;  // No key pressed
            }
            
            l88mem(2, idle >> 8);
            l88mem(3, idle); idle = 0;
            adc_software_trigger_enable(ADC0, ADC_REGULAR_CHANNEL);
        }
    }
}