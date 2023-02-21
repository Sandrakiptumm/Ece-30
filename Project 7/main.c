//***********Homework_06**********************
//***************main.c*************************
//
//  Description: This file contains the Main Routine - "While" Operating System
// It is responible for running the main program, and it is responsible for 
// running all the functions.
//
//  Paul Svetlov
// ECE 306
//  Septemper 30, 2016
//  Built with IAR Embedded Workbench Version: V7.3.1.3987 (6.40.1)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"


// Global Variables
volatile unsigned char control_state[CNTL_STATE_INDEX];
volatile unsigned int Time_Sequence;
char led_smclk;
volatile char one_time;
volatile unsigned int five_msec_count;
extern char display_line_1[LCD_WIDTH];
extern char display_line_2[LCD_WIDTH];
extern char display_line_3[LCD_WIDTH];
extern char display_line_4[LCD_WIDTH];
extern char *display_1;
extern char *display_2;
extern char *display_3;
extern char *display_4;
char posL1;
char posL2;
char posL3;
char posL4;
char size_count;
char big;
char start_moving;   // 1 or 0
char moving;   // 
int shape;
int time_count;
int press_count;
volatile unsigned int SW1_Pressed = RESET;
volatile unsigned int SW2_Pressed = RESET;
volatile unsigned int pressed_SW1 = RESET;
volatile unsigned int pressed_SW2 = RESET;
volatile unsigned int Press;
volatile unsigned int channel;
unsigned int ADC_Left_Detector;
unsigned int ADC_Right_Detector;
volatile unsigned int ADC_Thumb;
unsigned int time;
unsigned int right_forward_rate;
unsigned int left_forward_rate;
unsigned int right_reverse_rate;
unsigned int left_reverse_rate;

unsigned int i = RESET;

unsigned int startTransmit;

char adc_char[ARRAY5];

volatile char USB_Char_Rx[SMALL_RING_SIZE];
volatile char USB_Char_Tx[SMALL_RING_SIZE];

char temp_Print[SMALL_RING_SIZE];

char ncsuTransmit[ARRAY9] = "NCSU  #1";

volatile unsigned int usb_tx_ring_wr;
volatile unsigned int usb_rx_ring_wr;
volatile unsigned int usb_rx_ring_rd;
volatile unsigned int usb_tx_ring_rd;

volatile unsigned int temp;

volatile unsigned int hereNull = RESET;
volatile unsigned int hereNullsec = RESET;


volatile unsigned int display_delay = RESET;

volatile unsigned int character_Recieved = RESET;

volatile unsigned int trans_recieve_wait[SMALL_RING_SIZE];

volatile unsigned int time_delay;

void main(void){
//------------------------------------------------------------------------------
// Main Program
// This is the main routine for the program. Execution of code starts here.
// The operating system is Back Ground Fore Ground.
//
//------------------------------------------------------------------------------
   Init_Ports();                             // Initialize Ports
  Init_Clocks();                            // Initialize Clock System
  Init_Conditions();
//  PJOUT |= LED1;                            // Turn LED 1 on to indicate boot
  Time_Sequence = TS_START;                        //
  Init_Timers();                            // Initialize Timers
   // 250 msec delay for the clock to settle
  Init_LCD();                               // Initialize LCD
  Init_ADC();
  Init_Serial_UCA0(BAUD_9600, UCA0MCTLW_BAUD_9600);
  Init_Serial_UCA1(BAUD_9600, UCA0MCTLW_BAUD_9600);
  
  display_1 = "Init";
  lcd_out(display_1, LCD_HOME_L1, posL1);
  
  
  five_msec_Delay(QUARTER_SEC);
    
  ADC10CTL0 |= ADC10ENC;      // turn on ENC bit
  ADC10CTL0 |= ADC10ENC + ADC10SC;  // next sample
   
//------------------------------------------------------------------------------
// Begining of the "While" Operating System
//------------------------------------------------------------------------------
 while(ALWAYS) {                           // Can the Operating system run
      
   //Switches_Process();

   
   // if pressed start new character transmit
   if(pressed_SW1 == PRESSED_SW1){
     pressed_SW1 = RESET;
     Transmit_UCA0(1);              // transmit the first character
     display_1 = "0000";
     Display_Process();                 // Display initial 0000
   }
   
   // if character recieved continue with increment and retransmit
   //if(character_Recieved == TRUE) {
     recieve_A0();
   //}  
   
  }  
    
}

