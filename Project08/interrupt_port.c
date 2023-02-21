//***********Homework_06**********************
//***************main.c*************************
//
//  Description: This file contains the interupts for the timer and the switches
//
//  Paul Svetlov
// ECE 306
//  Septemper 30, 2016
//  Built with IAR Embedded Workbench Version: V7.3.1.3987 (6.40.1)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

#include "macros.h"
#include  "msp430.h"
#include "functions.h"

extern volatile unsigned int SW1_Pressed;
extern volatile unsigned int SW2_Pressed;
extern volatile unsigned int pressed_SW1;
extern volatile unsigned int pressed_SW2;

// this interrupt deals with SW1 and SW2
#pragma vector = PORT4_VECTOR

__interrupt void switch_interrupt(void){
// Switch 1
  if (P4IFG & SW1) {
    SW1_Pressed = PRESSED_SW1;
    pressed_SW1 = PRESSED_SW1;
    P4IE &= ~SW1;               // disable SW1 interrupt
    P4IFG &= ~SW1;              //sw1 interrupt flag cleared
    //display_1 = "SW1";
    //Display_Process();
    //P1OUT |= LCD_BACKLITE;               //turn on backlite
    //P3OUT |= IR_LED;            // LED ON
  

        
    TA0CCR1 = TA0R + DEBOUNCE;     // every 100 msec
    TA0CCTL1 |= CCIE;                    // enable timer interrupt
    
    
      
  }
  // Switch 2
  if (P4IFG & SW2) {
    SW2_Pressed = PRESSED_SW2;
    pressed_SW2 = PRESSED_SW2;
    //display_1 = "SW2";
    //Display_Process();
    P4IE &= ~SW2;               // disable SW2 interrupt
    P4IFG &= ~SW2;
    //P1OUT &= ~LCD_BACKLITE;             //turn off backlite
    //P3OUT &= ~IR_LED;           // LED OFF
   
   
    TA0CCR2 = TA0R + DEBOUNCE;     // every 100 msec
    TA0CCTL2 |= CCIE;                     // enable timer interrupt
    
  }
}