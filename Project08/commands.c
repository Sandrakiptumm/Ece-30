// ************init.c***********
//
// This file transmits or recieves with UCA0 or UCA1
// Paul Svetlov
// ECE 306
// pvsvetlo@ncsu.edu
// November 12, 2016



#include  "msp430.h"
#include "macros.h"
#include "functions.h"

extern char *display_1;
extern char *display_2;
extern char *display_3;
extern char *display_4;

extern char posL1;
extern char posL2;
extern char posL3;
extern char posL4;

extern unsigned int usb_tx_ring_wr_A0;
extern unsigned int usb_tx_ring_wr_A1;
extern unsigned int usb_rx_ring_wr_A0;
extern unsigned int usb_rx_ring_wr_A1;
extern unsigned int usb_rx_ring_rd_A0;
extern unsigned int usb_rx_ring_rd_A1;
extern unsigned int usb_tx_ring_rd_A0;
extern unsigned int usb_tx_ring_rd_A1;




extern char USB_Char_Rx_A0[SMALL_RING_SIZE];
extern char USB_Char_Tx_A0[SMALL_RING_SIZE];

extern char tempArray[SMALL_RING_SIZE];

extern unsigned int temp0;
extern unsigned int temp1;

extern unsigned int driveTime;







void commands(char* dot_pointer) {
  int i = RESET;
  if(*dot_pointer == '*') {
     display_2 = "*";  
     lcd_out(display_2, LCD_HOME_L2, posL2);
     if((*(dot_pointer + 1) == '1') && (*(dot_pointer + 2) == '2') && (*(dot_pointer + 3) == '3') && (*(dot_pointer + 4) == '4')) {
       display_2 = "Pass";  
       lcd_out(display_2, LCD_HOME_L2, posL2);
       five_msec_Delay(ZERO_FIVE_SEC);     
       
       if(*(dot_pointer + 5) == '0') {
          driveTime = QUARTER_SEC_PLUS;
       } 
       if(*(dot_pointer + 5) == '1') {
          driveTime = HALF_SEC;
       } 
       if(*(dot_pointer + 5) == '2') {
          driveTime = SEC;
       }
       if(*(dot_pointer + 5) == '3') {
          driveTime = SEC_HALF;
       }
       if(*(dot_pointer + 5) == '4') {
          driveTime = TWO_SEC;
       }
       if(*(dot_pointer + 5) == '5') {
          driveTime = THREE_SEC;
       }
     
       while(*(dot_pointer + i) != '\r') {
           if(*(dot_pointer + i) == 'F') {
              display_2 = "Forward";  
              lcd_out(display_2, LCD_HOME_L2, posL2);
              TB1CCR1 = OFF;    //forward right wheel off
              TB1CCR2 = OFF;    //forward left wheel off
              TB2CCR1 = OFF;    //reverse right wheel off
              TB2CCR2 = OFF;    //reverse left wheel off
              TB1CCR1 = WHEEL70PERCENT;  //forward right wheel on at 50%
              TB1CCR2 = WHEEL70PERCENT;  //forward left wheel on at 50%
              five_msec_Delay(driveTime);  //delay
              TB1CCR1 = OFF;    //forward right wheel off
              TB1CCR2 = OFF;    //forward left wheel off
              TB2CCR1 = OFF;    //reverse right wheel off
              TB2CCR2 = OFF;    //reverse left wheel off
              five_msec_Delay(ZERO_FIVE_SEC);
           }
           if(*(dot_pointer + i) == 'B') {
              display_2 = "Reverse";  
              lcd_out(display_2, LCD_HOME_L2, posL2);
              TB1CCR1 = OFF;    //forward right wheel off
              TB1CCR2 = OFF;    //forward left wheel off
              TB2CCR1 = OFF;    //reverse right wheel off
              TB2CCR2 = OFF;    //reverse left wheel off
              TB2CCR1 = WHEEL70PERCENT;  //forward right wheel on at 50%
              TB2CCR2 = WHEEL70PERCENT;  //forward left wheel on at 50%
              five_msec_Delay(driveTime);  //delay
              TB1CCR1 = OFF;    //forward right wheel off
              TB1CCR2 = OFF;    //forward left wheel off
              TB2CCR1 = OFF;    //reverse right wheel off
              TB2CCR2 = OFF;    //reverse left wheel off
              five_msec_Delay(ZERO_FIVE_SEC);
           }
           if(*(dot_pointer + i) == 'L') {
              display_2 = "Left";  
              lcd_out(display_2, LCD_HOME_L2, posL2);
              TB1CCR1 = OFF;    //forward right wheel off
              TB1CCR2 = OFF;    //forward left wheel off
              TB2CCR1 = OFF;    //reverse right wheel off
              TB2CCR2 = OFF;    //reverse left wheel off
              TB1CCR1 = WHEEL70PERCENT;  //forward right wheel on at 50%
              TB2CCR2 = WHEEL70PERCENT;  //forward left wheel on at 50%
              five_msec_Delay(driveTime);  //delay
              TB1CCR1 = OFF;    //forward right wheel off
              TB1CCR2 = OFF;    //forward left wheel off
              TB2CCR1 = OFF;    //reverse right wheel off
              TB2CCR2 = OFF;    //reverse left wheel off
              five_msec_Delay(ZERO_FIVE_SEC);
           }
           if(*(dot_pointer + i) == 'R') {
              display_2 = "Right";  
              lcd_out(display_2, LCD_HOME_L2, posL2);
              TB1CCR1 = OFF;    //forward right wheel off
              TB1CCR2 = OFF;    //forward left wheel off
              TB2CCR1 = OFF;    //reverse right wheel off
              TB2CCR2 = OFF;    //reverse left wheel off
              TB2CCR1 = WHEEL70PERCENT;  //forward right wheel on at 50%
              TB1CCR2 = WHEEL70PERCENT;  //forward left wheel on at 50%
              five_msec_Delay(driveTime);  //delay
              TB1CCR1 = OFF;    //forward right wheel off
              TB1CCR2 = OFF;    //forward left wheel off
              TB2CCR1 = OFF;    //reverse right wheel off
              TB2CCR2 = OFF;    //reverse left wheel off
              five_msec_Delay(ZERO_FIVE_SEC);
           }
           five_msec_Delay(ZERO_FIVE_SEC);
           Display_Process();
           i++;
       }   
     } 
   }  
   clearArray();
}

void clearArray() {
  int i = RESET;
  while(i < SMALL_RING_SIZE) {
    tempArray[i] = RESET;
    i++;
  }  
}  




