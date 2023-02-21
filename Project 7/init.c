// ************init.c***********
//
// This file sets the initial conditions of the display and interrupts.
// Paul Svetlov
// ECE 306
// pvsvetlo@ncsu.edu
// September 16, 2016



#include  "msp430.h"
#include "macros.h"
#include "functions.h"


extern char display_line_1[LCD_WIDTH];
extern char display_line_2[LCD_WIDTH];
extern char display_line_3[LCD_WIDTH];
extern char display_line_4[LCD_WIDTH];

extern char *display_1;
extern char *display_2;
extern char *display_3;
extern char *display_4;

extern char posL1;
extern char posL2;
extern char posL3;
extern char posL4;

extern volatile char USB_Char_Rx[11];
extern volatile char USB_Char_Tx[11];

extern volatile unsigned int usb_tx_ring_wr;
extern volatile unsigned int usb_rx_ring_wr;
extern volatile unsigned int usb_rx_ring_rd;
extern volatile unsigned int usb_tx_ring_rd;

extern volatile unsigned int temp;

extern volatile unsigned int Time_Sequence;

extern char adc_char[ARRAY5]; 

extern volatile unsigned int trans_recieve_wait[SMALL_RING_SIZE];

extern volatile unsigned int character_Recieved;


void Init_Conditions(void){
//------------------------------------------------------------------------------
// Initializations Configurations
//------------------------------------------------------------------------------
// Interrupts are disabled by default, enable them.
  enable_interrupts();
  display_1 = &display_line_1[LCD_POS_ONE];
  display_2 = &display_line_2[LCD_POS_ONE];
  display_3 = &display_line_3[LCD_POS_ONE];
  display_4 = &display_line_4[LCD_POS_ONE];

//------------------------------------------------------------------------------
}

void Display_Process(void){
  ClrDisplay();
  lcd_out(display_1, LCD_HOME_L1, posL1);
  lcd_out(display_2, LCD_HOME_L2, posL2);
  lcd_out(display_3, LCD_HOME_L3, posL3);
  lcd_out(display_4, LCD_HOME_L4, posL4);
}

//------------------------------------------------------------------------------
// Configure ADC10_B
void Init_ADC(void){
 ADC10CTL0 = RESET_STATE; // Clear ADC10CTL0
 ADC10CTL0 |= ADC10SHT_2; // 16 ADC clocks
 ADC10CTL0 &= ~ADC10MSC; // Single Sequence
 ADC10CTL0 |= ADC10ON; // ADC ON - Core Enabled
 ADC10CTL1 = RESET_STATE; // Clear ADC10CTL1
 ADC10CTL1 |= ADC10SHS_0; // ADC10SC bit
 ADC10CTL1 |= ADC10SHP; // SAMPCON signal sourced from sampling timer
 ADC10CTL1 &= ~ADC10ISSH; // The sample-input signal is not inverted.
 ADC10CTL1 |= ADC10DIV_0; // ADC10_B clock divider – Divide by 1.
 ADC10CTL1 |= ADC10SSEL_0; // MODCLK
 ADC10CTL1 |= ADC10CONSEQ_0; // Single-channel, single-conversion
 ADC10CTL2 = RESET_STATE; // Clear ADC10CTL2
 ADC10CTL2 |= ADC10DIV_0; // Pre-divide by 1
 ADC10CTL2 |= ADC10RES; // 10-bit resolution
 ADC10CTL2 &= ~ADC10DF; // Binary unsigned
 ADC10CTL2 &= ~ADC10SR; // supports up to approximately 200 ksps
 ADC10MCTL0 = RESET_STATE; // Clear ADC10MCTL0
 ADC10MCTL0 |= ADC10SREF_0; // V(R+) = AVCC and V(R-) = AVSS
 ADC10MCTL0 |= ADC10INCH_0; // Channel A3 Right 
 ADC10IE |= ADC10IE0; // Enable ADC conversion complete interrupt
}




//Init_Serial_UCA0(); // Initialize Serial Port for USB

//----------------------------------------------------------------------------
void Init_Serial_UCA0(int baud, int hexVal){
   int i;
   for(i=0; i<SMALL_RING_SIZE; i++){
      USB_Char_Rx[i] = 0x00; // USB Rx Buffer
   }
   usb_rx_ring_wr = BEGINNING;
   usb_rx_ring_rd = BEGINNING;

   for(i=0; i<LARGE_RING_SIZE; i++){ // May not use this
     USB_Char_Tx[i] = 0x00; // USB Tx Buffer
   }
   usb_tx_ring_wr = BEGINNING;
   usb_tx_ring_rd = BEGINNING;
   // Configure UART 0
   UCA0CTLW0 = 0; // Use word register
   UCA0CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
   UCA0CTLW0 |= UCSWRST; // Set Software reset enable
   //***** Continued on next slide
   // ***** Continuation from previous slide
   // 9,600 Baud Rate
   // 1. Calculate N = fBRCLK / Baudrate
   // N = SMCLK / 9,600 => 8,000,000 / 9,600 = 833.3333333
   // if N > 16 continue with step 3, otherwise with step 2
   // 2. OS16 = 0, UCBRx = INT(N)
   // continue with step 4
   // 3. OS16 = 1,
   // UCx = INT(N/16),
   // = INT(N/16) = 833.333/16 => 52
   // UCFx = INT([(N/16) – INT(N/16)] × 16)
   //= ([833.333/16-INT(833.333/16)]*16)
   //= (52.08333333-52)*16
   //= 0.083*16 = 1
   // 4. UCSx is found by looking up the fractional part of N (= N-INT(N)) in table Table 18-4
   // Decimal of SMCLK / 8,000,000 / 9,600 = 833.3333333 => 0.333 yields 0x49 [Table]
   // 5. If OS16 = 0 was chosen, a detailed error calculation is recommended to be performed
   // TX error (%) RX error (%)
   // BRCLK Baudrate UCOS16 UCBRx UCFx UCSx neg pos neg pos
   // 8000000 9600 1 52 1 0x49 -0.08 0.04 -0.10 0.14
   UCA0BRW = baud; // 9,600 Baud
   // UCA0MCTLW = UCSx concatenate UCFx concatenate UCOS16;
   // UCA0MCTLW = 0x49 concatenate 1 concatenate 1;
   UCA0MCTLW = hexVal;
   UCA0CTL1 &= ~UCSWRST; // Release from reset
   UCA0IE |= UCRXIE; // Enable RX interrupt
}

//----------------------------------------------------------------------------
void Init_Serial_UCA1(int baud, int hexVal){
   int i;
   for(i=0; i<SMALL_RING_SIZE; i++){
      USB_Char_Rx[i] = 0x00; // USB Rx Buffer
   }
   usb_rx_ring_wr = BEGINNING;
   usb_rx_ring_rd = BEGINNING;

   for(i=0; i<LARGE_RING_SIZE; i++){ // May not use this
     USB_Char_Tx[i] = 0x00; // USB Tx Buffer
   }
   usb_tx_ring_wr = BEGINNING;
   usb_tx_ring_rd = BEGINNING;
   // Configure UART 0
   UCA0CTLW0 = 0; // Use word register
   UCA0CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
   UCA0CTLW0 |= UCSWRST; // Set Software reset enable
   //***** Continued on next slide
   // ***** Continuation from previous slide
   // 9,600 Baud Rate
   // 1. Calculate N = fBRCLK / Baudrate
   // N = SMCLK / 9,600 => 8,000,000 / 9,600 = 833.3333333
   // if N > 16 continue with step 3, otherwise with step 2
   // 2. OS16 = 0, UCBRx = INT(N)
   // continue with step 4
   // 3. OS16 = 1,
   // UCx = INT(N/16),
   // = INT(N/16) = 833.333/16 => 52
   // UCFx = INT([(N/16) – INT(N/16)] × 16)
   //= ([833.333/16-INT(833.333/16)]*16)
   //= (52.08333333-52)*16
   //= 0.083*16 = 1
   // 4. UCSx is found by looking up the fractional part of N (= N-INT(N)) in table Table 18-4
   // Decimal of SMCLK / 8,000,000 / 9,600 = 833.3333333 => 0.333 yields 0x49 [Table]
   // 5. If OS16 = 0 was chosen, a detailed error calculation is recommended to be performed
   // TX error (%) RX error (%)
   // BRCLK Baudrate UCOS16 UCBRx UCFx UCSx neg pos neg pos
   // 8000000 9600 1 52 1 0x49 -0.08 0.04 -0.10 0.14
   UCA0BRW = baud; // 9,600 Baud 52  or 4 115200
   // UCA0MCTLW = UCSx concatenate UCFx concatenate UCOS16;
   // UCA0MCTLW = 0x49 concatenate 1 concatenate 1;
   UCA0MCTLW = hexVal;
   UCA0CTL1 &= ~UCSWRST; // Release from reset
   UCA0IE |= UCRXIE; // Enable RX interrupt
}


// This function transmits a character using UCA0
void Transmit_UCA0(char c) {
  while(UCA0STATW & UCBUSY);
  UCA0TXBUF = c;
}

// This function transmits a character using UCA1
void Transmit_UCA1(char c) {
  while(UCA1STATW & UCBUSY);
  UCA1TXBUF = c;
}


// This function takes care of recieving a character, printing the character
// and transmitting that same character incrumented by one. 
void recieve_A0() {
  if((trans_recieve_wait[usb_rx_ring_rd] < (Time_Sequence - SEC)) && (usb_rx_ring_wr != usb_rx_ring_rd)) {
    Transmit_UCA0(USB_Char_Rx[usb_rx_ring_rd] + 1);
    //character_Recieved = RESET;
    HEXtoBCD(USB_Char_Rx[usb_rx_ring_rd]);              // hex to BCD conversion 
    display_2 = "0000";  //clear
    lcd_out(display_2, LCD_HOME_L2, posL2); 
    display_2 = adc_char;                    // set display
    lcd_out(display_2, LCD_HOME_L2, posL2);   // print on display
      if (++usb_rx_ring_rd == SMALL_RING_SIZE){          // reset read index 
      usb_rx_ring_rd = BEGINNING;
  }
  }

}  
  