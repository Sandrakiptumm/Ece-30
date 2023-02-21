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

extern char USB_Char_Rx_A0[SMALL_RING_SIZE];
extern char USB_Char_Tx[SMALL_RING_SIZE];

extern unsigned int usb_tx_ring_wr_A0;
extern unsigned int usb_tx_ring_wr_A1;
extern unsigned int usb_rx_ring_wr_A0;
extern unsigned int usb_rx_ring_wr_A1;
extern unsigned int usb_rx_ring_rd_A0;
extern unsigned int usb_rx_ring_rd_A1;
extern unsigned int usb_tx_ring_rd_A0;
extern unsigned int usb_tx_ring_rd_A1;

extern unsigned int temp0;
extern unsigned int temp1;

extern volatile unsigned int Time_Sequence;

extern char adc_char[ARRAY5]; 

extern unsigned int trans_recieve_wait[SMALL_RING_SIZE];

extern volatile unsigned int character_Recieved;




// This function transmits a character using UCA0
void Transmit_UCA0(char c) {
    while(!(UCA0IFG & UCTXIFG));
    UCA0TXBUF = c;  
}

// This function transmits a character using UCA1
void Transmit_UCA1(char c) {
  while(!(UCA1IFG & UCTXIFG));
  UCA1TXBUF = c;
}








// This function takes care of recieving a character, printing the character
// and transmitting that same character incrumented by one. 
void recieve_A0() {
  /*
  if((trans_recieve_wait[usb_rx_ring_rd] < (Time_Sequence - SEC)) && (usb_rx_ring_wr != usb_rx_ring_rd)) {
    Transmit_UCA0(USB_Char_Rx_A0[usb_rx_ring_rd] + 1);
    HEXtoBCD(USB_Char_Rx_A0[usb_rx_ring_rd]);              // hex to BCD conversion 
    display_2 = "0000";  //clear
    lcd_out(display_2, LCD_HOME_L2, posL2); 
    display_2 = adc_char;                    // set display
    lcd_out(display_2, LCD_HOME_L2, posL2);   // print on display
      if (++usb_rx_ring_rd == SMALL_RING_SIZE){          // reset read index 
        usb_rx_ring_rd = BEGINNING;
      }
  }
  */

}