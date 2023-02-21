// ECE 306
//  October 27, 2016
//  Built with IAR Embedded Workbench Version: V7.3.1.3987 (6.40.1)
//------------------------------------------------------------------------------
//  Paul Svetlov
//
//  This file contains the interrupts for the serial ports.
//------------------------------------------------------------------------------

#include "macros.h"
#include  "msp430.h"
#include "functions.h"

extern char USB_Char_Rx_A0[SMALL_RING_SIZE];
extern char USB_Char_Rx_A1[SMALL_RING_SIZE];
extern char USB_Char_Tx[SMALL_RING_SIZE];

extern unsigned int usb_tx_ring_wr_A0;
extern unsigned int usb_tx_ring_wr_A1;
extern unsigned int usb_rx_ring_wr_A0;
extern unsigned int usb_rx_ring_wr_A1;
extern unsigned int usb_rx_ring_rd_A0;
extern unsigned int usb_rx_ring_rd_A1;
extern unsigned int usb_tx_ring_rd_A0;
extern unsigned int usb_tx_ring_rd_A1;

extern volatile unsigned int hereNull;
extern volatile unsigned int hereNullsec;


extern unsigned int temp0;
extern unsigned int temp1;

extern unsigned int times[SMALL_RING_SIZE]; 

extern unsigned int trans_recieve_wait[SMALL_RING_SIZE];

extern volatile unsigned int Time_Sequence;

extern volatile unsigned int time_delay;

extern volatile unsigned int character_Recieved;

extern volatile unsigned int password_Status;

extern volatile char transmit_2_pc_ok;

extern unsigned int star_found;
extern int plus_found; 


//------------------------------------------------------------------------------
#pragma vector = USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void){
  
  switch(__even_in_range(UCA0IV,0x08)){
    case 0: // Vector 0 - no interrupt
      break;
    case 2: // Vector 2 - RXIFG
     
      character_Recieved = TRUE;
      transmit_2_pc_ok = TRUE;
      temp0 = usb_rx_ring_wr_A0; 
      trans_recieve_wait[temp0] = time_delay;
      USB_Char_Rx_A0[temp0] = UCA0RXBUF; // RX -> USB_Char_Rx character
      Transmit_UCA1(USB_Char_Rx_A0[temp0]);
      
      if (++usb_rx_ring_wr_A0 >= (SMALL_RING_SIZE)){
        usb_rx_ring_wr_A0 = BEGINNING; // Circular buffer back to beginning
      }
       
      
      break;
    case 4: // Vector 4 – TXIFG
      break;
    default: break;
  }
  //if(USB_Char_Rx_A0[usb_rx_ring_wr] == '\0') {
        //hereNull = SET1;
 // }  
 // Transmit_UCA0(USB_Char_Rx[temp]);
   password_Status++;
  
   
}
//------------------------------------------------------------------------------




//------------------------------------------------------------------------------
#pragma vector = USCI_A1_VECTOR
__interrupt void USCI_A1_ISR(void){
  //unsigned int temp;
  switch(__even_in_range(UCA1IV,0x08)){
    case 0: // Vector 0 - no interrupt
      break;
    case 2: // Vector 2 - RXIFG
      character_Recieved = TRUE;
      if(character_Recieved) {
        temp1 = usb_rx_ring_wr_A1;
        USB_Char_Rx_A1[temp1] = UCA1RXBUF; // RX -> USB_Char_Rx character
        Transmit_UCA0(USB_Char_Rx_A1[temp1]);
        if (++usb_rx_ring_wr_A1 >= (SMALL_RING_SIZE)){
          usb_rx_ring_wr_A1 = BEGINNING; // Circular buffer back to beginning
        }
        if(transmit_2_pc_ok) {
          UCA0TXBUF = USB_Char_Rx_A1[temp1];
        } 
        
        if(USB_Char_Rx_A1[temp1] == '*') {
          star_found = temp1;
          usb_rx_ring_rd_A1 = temp1;
        }
        if((USB_Char_Rx_A1[temp1] == '+') && (plus_found != -1)) {
          plus_found = temp1;
          usb_rx_ring_rd_A1 = temp1;
        } 
      }  
      
      break;
    case 4: // Vector 4 – TXIFG
      break;
    default: break;
  }
  if(USB_Char_Rx_A1[usb_rx_ring_wr_A1] == '\0') {
        hereNullsec = SET1;
  } 
}
//------------------------------------------------------------------------------
