// ***********ports.c************
// 
// Configures and initializes all input and output ports
// Parameters: none
// Return: none
// 
// Paul Svetlov
// ECE 306
// pvsvetlo@ncsu.edu
// September 16, 2016


#include "macros.h"
#include  "msp430.h"
#include "functions.h"

void Init_Ports(void) {
  
  Init_Port1();
  Init_Port2();
  Init_Port3();
  Init_Port4();
  Init_PortJ();
  
}  

void Init_Port1(void){
// Configure Port 1 -------------------------------------------------------------

P1SEL0 = RESET_PORT; // P1 set as I/0
P1SEL1 = RESET_PORT; // P1 set as I/0

P1SEL0 = RESET_REGISTER; // P1 set as I/0
P1SEL1 = RESET_REGISTER; // P1 set as I/0
P1DIR = RESET_REGISTER; // Set P1 direction to input
P1SEL0 |= V_DETECT_R; // V_DETECT_R selected
P1SEL1 |= V_DETECT_R; // V_DETECT_R selected
P1SEL0 |= V_DETECT_L; // V_DETECT_L selected
P1SEL1 |= V_DETECT_L; // V_DETECT_L selected
P1SEL0 &= ~LCD_BACKLITE; // LCD_BACKLITE GPI/O selected
P1SEL1 &= ~LCD_BACKLITE; // LCD_BACKLITE GPI/O selected
P1OUT |= LCD_BACKLITE; // LCD_BACKLITE Port Pin set high
P1DIR |= LCD_BACKLITE; // Set LCD_BACKLITE direction to output
P1SEL0 |= V_THUMB; // V_THUMB selected
P1SEL1 |= V_THUMB; // V_THUMB selected
P1SEL0 &= ~SPI_CS_LCD; // SPI_CS_LCD GPI/O selected
P1SEL1 &= ~SPI_CS_LCD; // SPI_CS_LCD GPI/O selected
P1OUT |= SPI_CS_LCD; // SPI_CS_LCD Port Pin set high
P1DIR |= SPI_CS_LCD; // Set SPI_CS_LCD output direction
P1SEL0 &= ~RESET_LCD; // RESET_LCD GPI/O selected
P1SEL1 &= ~RESET_LCD; // RESET_LCD GPI/O selected
P1OUT &= ~RESET_LCD; // RESET_LCD Port Pin set low
P1DIR |= RESET_LCD; // Set RESET_LCD output direction
P1SEL0 &= ~SIMO_B; // SIMO_B selected
P1SEL1 |= SIMO_B; // SIMO_B selected
P1DIR |= SIMO_B; // SIMO_B set to Output
P1SEL0 &= ~SOMI_B; // SOMI_B is used on the LCD
P1SEL1 |= SOMI_B; // SOMI_B is used on the LCD
P1OUT |= SOMI_B; // SOMI_B Port Pin set for Pull-up
P1DIR &= ~SOMI_B; // SOMI_B set to Input
P1REN |= SOMI_B; // Enable pullup resistor
//------------------------------------------------------------------------------
}

void Init_Port2(void) {
//-------------------------------------------------------
// Port 2 Pins
P2SEL0 &= ~USB_TXD;
P2SEL1 |= USB_TXD;
P2OUT &= ~USB_TXD;
P2DIR |= USB_TXD;   

P2SEL0 &= ~USB_RXD;
P2SEL1 |= USB_RXD;
P2OUT &= ~USB_RXD;
P2DIR |= USB_RXD;
P2REN &= ~USB_RXD;

P2SEL0 &= ~SPI_SCK;
P2SEL1 |= SPI_SCK;  
P2OUT |= SPI_SCK; 
P2DIR |= SPI_SCK;

P2SEL0 &= ~UNKNOWN1;
P2SEL1 &= ~UNKNOWN1;  
P2OUT &= ~UNKNOWN1;  
P2DIR |= UNKNOWN1;
P2REN &= ~UNKNOWN1;

P2SEL0 &= ~UNKNOWN2;
P2SEL1 &= ~UNKNOWN2;  
P2OUT &= ~UNKNOWN2;  
P2DIR |= UNKNOWN2;
P2REN &= ~UNKNOWN2;

P2SEL0 &= ~CPU_TXD;
P2SEL1 |= CPU_TXD;  
P2OUT &= ~CPU_TXD;  
P2DIR |= CPU_TXD;

P2SEL0 &= ~CPU_RXD;
P2SEL1 |= CPU_RXD;  
P2OUT &= ~CPU_RXD;   
P2DIR |= CPU_RXD;
P2REN &= ~CPU_RXD;

P2SEL0 &= ~UNKNOWN3;
P2SEL1 &= ~UNKNOWN3;  
P2OUT &= ~UNKNOWN3;  
P2DIR |= UNKNOWN3;
P2REN &= ~UNKNOWN3;
  
}  

void Init_Port3(void) {
//-------------------------------------------------------
// Port 3 Pins
P3SEL0 &= ~X;
P3SEL1 &= ~X;
P3OUT &= ~X;
P3DIR |= X;
P3REN &= ~X;

P3SEL0 &= ~Y;
P3SEL1 &= ~Y;
P3OUT &= ~Y;
P3DIR |= Y;
P3REN &= ~Y;

P3SEL0 &= ~ZE;
P3SEL1 &= ~ZE;
P3OUT &= ~ZE;
P3DIR |= ZE;
P3REN &= ~ZE;

P3SEL0 &= ~IR_LED;
P3SEL1 &= ~IR_LED;
P3OUT &= ~IR_LED;
P3DIR |= IR_LED;

P3SEL0 |= R_FORWARD;
P3SEL1 &= ~R_FORWARD;
P3DIR |= R_FORWARD;

P3SEL0 |= L_FORWARD;
P3SEL1 &= ~L_FORWARD;
P3DIR |= L_FORWARD;

P3SEL0 |= R_REVERSE;
P3SEL1 &= ~R_REVERSE;
P3DIR |= R_REVERSE;

P3SEL0 |= L_REVERSE;
P3SEL1 &= ~L_REVERSE;
P3DIR |= L_REVERSE;

}


void Init_Port4(void) {
//-------------------------------------------------------
// Port 4 Pins
  
P4SEL0 = RESET_PORT;   // P4 set as I/O  
P4SEL1 = RESET_PORT;   // P4 set as I/O
P4DIR = RESET_PORT;    // Set P4 direction to input

P4SEL0 &= ~SW1;
P4SEL1 &= ~SW1;
P4OUT |= SW1;
P4DIR &= ~SW1;
P4REN |= SW1;

P4IES |= SW1; // SW1 Hi/Lo edge interrupt
P4IFG &= ~SW1; // IFG SW1 cleared
P4IE |= SW1; // SW1 interrupt Enabled

P4SEL0 &= ~SW2;
P4SEL1 &= ~SW2;
P4OUT |= SW2;
P4DIR &= ~SW2;
P4REN |= SW2;

P4IES |= SW2; // SW2 Hi/Lo edge interrupt
P4IFG &= ~SW2; // IFG SW2 cleared
P4IE |= SW2; // SW2 interrupt enabled

  
} 

//------------------------------------------------------
// Ports J Pins

void Init_PortJ(void){

PJSEL0 = RESET_REGISTER; // PJ set as I/0
PJSEL1 = RESET_REGISTER; // PJ set as I/0
PJDIR = RESET_REGISTER; // Set PJ direction to output

PJSEL0 &= ~IOT_WAKEUP;
PJSEL1 &= ~IOT_WAKEUP;
PJOUT &= ~IOT_WAKEUP;
PJDIR |= IOT_WAKEUP; // Set PJ Pin 1 direction to output

PJSEL0 &= ~IOT_FACTORY;
PJSEL1 &= ~IOT_FACTORY;
PJOUT &= ~IOT_FACTORY;
PJDIR |= IOT_FACTORY; // Set PJ Pin 2 direction to output

PJSEL0 &= ~IOT_STA_MINIAP;
PJSEL1 &= ~IOT_STA_MINIAP;
PJOUT |= IOT_STA_MINIAP;
PJDIR |= IOT_STA_MINIAP; // Set PJ Pin 3 direction to output

PJSEL0 &= ~IOT_RESET;
PJSEL1 &= ~IOT_RESET;
PJDIR |= IOT_RESET; // Set P3 Pin 4 direction to output
PJOUT &= ~IOT_RESET;
// XT1 Setup
//PJSEL0 |= XINR;
//PJSEL0 |= XOUTR;
//------------------------------------------------------------------------------
}
