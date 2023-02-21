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

extern volatile char USB_Char_Rx[SMALL_RING_SIZE];
extern volatile char USB_Char_Tx[SMALL_RING_SIZE];

extern volatile unsigned int usb_tx_ring_wr;
extern volatile unsigned int usb_rx_ring_wr;
extern volatile unsigned int usb_rx_ring_rd;
extern volatile unsigned int usb_tx_ring_rd;

extern volatile unsigned int hereNull;
extern volatile unsigned int hereNullsec;


extern volatile unsigned int temp;

extern volatile unsigned int times[SMALL_RING_SIZE]; 

extern volatile unsigned int trans_recieve_wait[SMALL_RING_SIZE];

extern volatile unsigned int Time_Sequence;

extern volatile unsigned int time_delay;

extern volatile unsigned int character_Recieved;
//------------------------------------------------------------------------------
#pragma vector = USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void){
  
  switch(__even_in_range(UCA0IV,0x08)){
    case 0: // Vector 0 - no interrupt
      break;
    case 2: // Vector 2 - RXIFG
      temp = usb_rx_ring_wr; 
      trans_recieve_wait[temp] = time_delay;
      USB_Char_Rx[temp] = UCA0RXBUF; // RX -> USB_Char_Rx character
      if (++usb_rx_ring_wr >= (SMALL_RING_SIZE)){
        usb_rx_ring_wr = BEGINNING; // Circular buffer back to beginning
      }
      character_Recieved = TRUE;
      break;
    case 4: // Vector 4 – TXIFG
      break;
    default: break;
  }
  if(USB_Char_Rx[usb_rx_ring_wr] == '\0') {
        hereNull = SET1;
  }  
   
  
}
//------------------------------------------------------------------------------




//------------------------------------------------------------------------------
#pragma vector = USCI_A1_VECTOR
__interrupt void USCI_A1_ISR(void){
  unsigned int temp;
  switch(__even_in_range(UCA1IV,0x08)){
    case 0: // Vector 0 - no interrupt
      break;
    case 2: // Vector 2 - RXIFG
      temp = usb_rx_ring_wr;
      USB_Char_Rx[temp] = UCA1RXBUF; // RX -> USB_Char_Rx character
      if (++usb_rx_ring_wr >= (SMALL_RING_SIZE)){
        usb_rx_ring_wr = BEGINNING; // Circular buffer back to beginning
      }
      break;
    case 4: // Vector 4 – TXIFG
      break;
    default: break;
  }
  if(USB_Char_Rx[usb_rx_ring_wr] == '\0') {
        hereNullsec = SET1;
  } 
}
//------------------------------------------------------------------------------
