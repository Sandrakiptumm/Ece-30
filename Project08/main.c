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
#include "string.h"

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
unsigned int j = RESET;
unsigned int k = RESET;

unsigned int startTransmit;

char adc_char[ARRAY5];

char USB_Char_Rx_A0[SMALL_RING_SIZE];
char USB_Char_Rx_A1[SMALL_RING_SIZE];
char USB_Char_Tx[SMALL_RING_SIZE];

char tempArray[SMALL_RING_SIZE];

char temp_Print[SMALL_RING_SIZE];

char ncsuTransmit[ARRAY9] = "NCSU  #1";

unsigned int usb_tx_ring_wr_A0;
unsigned int usb_tx_ring_wr_A1;
unsigned int usb_rx_ring_wr_A0;
unsigned int usb_rx_ring_wr_A1;
unsigned int usb_rx_ring_rd_A0;
unsigned int usb_rx_ring_rd_A1;
unsigned int usb_tx_ring_rd_A0;
unsigned int usb_tx_ring_rd_A1;

unsigned int temp0;
unsigned int temp1;

volatile unsigned int hereNull = RESET;
volatile unsigned int hereNullsec = RESET;


volatile unsigned int display_delay = RESET;

volatile unsigned int character_Recieved = RESET;

unsigned int trans_recieve_wait[SMALL_RING_SIZE];

volatile unsigned int time_delay;


char temp_test[SMALL_RING_SIZE];

unsigned int star_found = RESET;
int plus_found = RESET; 


volatile unsigned int password_Status = RESET;


volatile char transmit_2_pc_ok;

unsigned int driveTime;

char* star_pointer;

char* ip_pointer;

char ip_address[ARRAY33];
char ip_address_line1[ARRAY11];
char ip_address_line4[ARRAY4];


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
  
  
  
  five_msec_Delay(ZERO_ONE_SEC);
  PJOUT |= IOT_RESET;
  five_msec_Delay(QUARTER_SEC);
    
  ADC10CTL0 |= ADC10ENC;      // turn on ENC bit
  ADC10CTL0 |= ADC10ENC + ADC10SC;  // next sample
  
  
  // not working for some reason lol lcd_BIG_mid(); //big line display
  
  display_1 = "Scanning";
  lcd_out(display_1, LCD_HOME_L1, posL1);
//------------------------------------------------------------------------------
// Begining of the "While" Operating System
//------------------------------------------------------------------------------
 while(ALWAYS) {                           // Can the Operating system run
   
   //Switches_Process();

   five_msec_Delay(SEC);
   
   // searching for ip address
   if(plus_found) {
     ip_pointer = strstr(USB_Char_Rx_A1, "+WIND:24:WiFi");
     if(*(ip_pointer) == '+') {
       i = RESET;
       while(*(ip_pointer + i) != '\r') {
         ip_address[i]= USB_Char_Rx_A1[usb_rx_ring_rd_A1];
         usb_rx_ring_rd_A1++;
         if(usb_rx_ring_rd_A1 > SMALL_RING_SIZE_PLUS) {
           usb_rx_ring_rd_A1 = BEGINNING;
         }
         i++;
       }
       plus_found = DISABLE;
     }
   }
   
   j = RESET;
   
   // ip address found but now insert into two arrays for printing
   ip_pointer = strstr(ip_address, "1");
   if(*(ip_pointer) == '1') {
      while(j < ARRAY10) {
        ip_address_line1[j] = *(ip_pointer + j);
        j++;
      }
      ip_address_line1[ARRAY10] = RESET;
      ip_pointer += POINTER_OFFSET;
      j = RESET;
      while(j < ARRAY3) {
        ip_address_line4[j] = *(ip_pointer + j);
        j++;
      }
      ip_address_line4[ARRAY3] = RESET;
      five_msec_Delay(ZERO_ONE_SEC);
      Display_Process();
      display_1 = ip_address_line1;              //display ip address on line 1
      lcd_out(display_1, LCD_HOME_L1, posL1);
      display_4 = ip_address_line4;              //display ip address on line 2
      lcd_out(display_4, LCD_HOME_L4, posL4);
      ip_pointer = RESET;
   }  
   
   
       
   
   
   
   i = RESET;
   
   // searching for * which signifies start of password and commands
   if(star_found) {
     five_msec_Delay(ZERO_ONE_SEC);
     while(USB_Char_Rx_A1[usb_rx_ring_rd_A1] != LINEFEED) {
       temp_test[i] = USB_Char_Rx_A1[usb_rx_ring_rd_A1];
        usb_rx_ring_rd_A1++;
        if(usb_rx_ring_rd_A1 > SMALL_RING_SIZE_PLUS) {
          usb_rx_ring_rd_A1 = BEGINNING;
        }  
        i++;
     }
     star_found = RESET;
     star_pointer = strstr(temp_test, "*");
     five_msec_Delay(ZERO_ONE_SEC);
     commands(star_pointer);
   }  
   
  }  
    
}

