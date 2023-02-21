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
volatile unsigned int SW1_Pressed;
volatile unsigned int SW2_Pressed;
volatile unsigned int pressed_SW1;
volatile unsigned int pressed_SW2;
volatile unsigned int Press;
volatile unsigned int SW1_Count;
volatile unsigned int SW2_Count;
volatile unsigned int channel;
unsigned int ADC_Left_Detector;
unsigned int ADC_Right_Detector;
volatile unsigned int ADC_Thumb;
unsigned int time;
unsigned int right_forward_rate;
unsigned int left_forward_rate;
unsigned int right_reverse_rate;
unsigned int left_reverse_rate;
unsigned int leftBlackCalibrate;
unsigned int rightBlackCalibrate;
unsigned int leftWhiteCalibrate;
unsigned int rightWhiteCalibrate;

int leftRunAvg[ARRAY8];
int rightRunAvg[ARRAY8];



volatile unsigned int sumLeft;
volatile unsigned int sumRight;
unsigned int left;
unsigned int right;
unsigned int i = RESET;
unsigned int lineDetect = RESET;


char adc_char[ARRAY5];


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
 // five_msec_sleep(QUARTER_SEC);                      // 250 msec delay for the clock to settle
  Init_LCD();                               // Initialize LCD
  Init_ADC();
  

//             1234567890
  //display_1 = "UNCA";
  //posL1 = SPACES3;
  //display_2 = "NCSU";
  //posL2 = SPACES3;
  //display_3 = "ECE306";
  //posL3 = SPACES2;
  //display_4 = "P Svetlov";
  //posL4 = SPACES1;
  //big = LITTLE;
  //Display_Process();
  
  start_moving = NO_MOVEMENT;
  moving = NO_MOVEMENT;  
  shape = ZERO_SHAPE;
  time_count = TIME_RESET;
  press_count = RESET;
 
  
  SW1_Pressed = RESET;
  SW2_Pressed = RESET;
  
  pressed_SW1 = RESET;
  pressed_SW2 = RESET;
  

  
  
  SW1_Count = RESET;
  SW2_Count = RESET;
  
  //display_1 = "Hello";
  //display_2 = "Press a";
  //display_3 = "Button";
  //Display_Process();
  
  
  
  ADC10CTL0 |= ADC10ENC;      // turn on ENC bit
  ADC10CTL0 |= ADC10ENC + ADC10SC;  // next sample
  
  //blackCalibrate = RESET;
  //whiteCalibrate = RESET;
  

  //right_forward_rate = ON;
  //left_forward_rate = ON;
  TB1CCR1 = OFF; // P3.4 Right Forward OFF
  TB1CCR2 = OFF; // P3.5 Left Forward OFF
  TB2CCR1 = OFF; // P3.4 Right Reverse OFF
  TB2CCR2 = OFF; // P3.5 Left Reverse OFF
  //TB1CCR1 = 8000; // P3.4 Right Forward PWM duty cycle
  //TB1CCR2 = 3000; // P3.5 Left Forward PWM duty cycle 
  //TB2CCR1 = WHEEL_PERIOD; 
  //TB2CCR2 = WHEEL_PERIOD; 

 
  //TB2CCR1 = 8000; // P3.4 Right Reverse PWM duty cycle
  //TB2CCR2 = 8000; // P3.5 Left Reverse PWM duty cycle 
    

  
//------------------------------------------------------------------------------
// Begining of the "While" Operating System
//------------------------------------------------------------------------------
 while(ALWAYS) {                            // Can the Operating system run
    
  
   
   
   
   //Switches_Process();

  //if ((ADC_Left_Detector < WHITE) && (ADC_Right_Detector < WHITE)) {
    //display_1 = "white   ";
    //lcd_out(display_1, LCD_HOME_L1, posL1);
  //}
  //else {
    //display_1 = "black   ";
    //lcd_out(display_1, LCD_HOME_L1, posL1);
  //}  
  
  HEXtoBCD(ADC_Left_Detector); 
  display_1 = adc_char;
  posL1 = SPACES3;
  lcd_out(display_1, LCD_HOME_L1, posL1);
  
  HEXtoBCD(ADC_Right_Detector);
  
  display_2 = adc_char;
  posL2 = SPACES3;
  lcd_out(display_2, LCD_HOME_L2, posL2);
  
  HEXtoBCD(ADC_Thumb); 
  
  display_3 = adc_char;
  posL3 = SPACES3;
  lcd_out(display_3, LCD_HOME_L3, posL3);
  
  
  
  
  
  
  
  
  
  
  
  // if switch one pressed calibrate for white
  if(pressed_SW1 == PRESSED_SW1) {
    pressed_SW1 = RESET;
    display_4 = "Calib W";
    lcd_out(display_4, LCD_HOME_L4, posL4);
    leftWhiteCalibrate = ADC_Left_Detector;
    rightWhiteCalibrate = ADC_Right_Detector;
    
  }

  // if switch two pressed calibrate for black
  if(pressed_SW2 == PRESSED_SW2) {
    display_4 = "Calib B";
    lcd_out(display_4, LCD_HOME_L4, posL4);
    leftBlackCalibrate = ADC_Left_Detector;
    leftBlackCalibrate = ADC_Right_Detector; 
  }  
    
        
  // if thumb wheel is greater than 50 then start line detect
  HEXtoBCD(ADC_Thumb); 
  if(ADC_Thumb > STARTDETECT) {
    P3OUT |= IR_LED;            // LED ON
    display_4 = "       ";
    lcd_out(display_4, LCD_HOME_L4, posL4);
    
    if(lineDetect == RESET) {
        TB1CCR1 = WHEEL40PERCENT; // P3.4 Right Forward PWM duty cycle
        TB1CCR2 = WHEEL80PERCENT; // P3.5 Left Forward PWM duty cycle    
     
        if ((ADC_Left_Detector >  (leftWhiteCalibrate+10)) || (ADC_Right_Detector > ( rightWhiteCalibrate+10))) {
            TB1CCR1 = OFF;
            TB1CCR2 = OFF;
       
            TB2CCR1 = WHEEL80PERCENT; // P3.4 Right Reverse PWM duty cycle
            TB2CCR2 = WHEEL80PERCENT; // P3.5 Left Reverse PWM duty cycle
            
            five_msec_Delay(5);
        
            TB2CCR1 = OFF;
            TB2CCR2 = OFF;
            
            five_msec_Delay(ONE_AND_FOURTH_SEC);
        
            TB1CCR1 = WHEEL40PERCENT;
            TB2CCR2 = WHEEL40PERCENT;
        
            five_msec_Delay(SEC);
            
            
        
            TB1CCR1 = OFF;
            TB1CCR2 = OFF;
            TB2CCR1 = OFF;
            TB2CCR2 = OFF;
            
            five_msec_Delay(SEC);
        
            lineDetect++;
  
        }
        
    }
    i = RESET;
    
    
    // running average
    while(i < ARRAY8) {
      leftRunAvg[i] = ADC_Left_Detector;
      rightRunAvg[i] = ADC_Right_Detector;
      i++;
    }
    i = RESET;
    while(i < ARRAY8) {
      sumLeft += leftRunAvg[i];     //sum
      sumRight += rightRunAvg[i];   //sum
      i++;
    }
    i = RESET;
    left = (sumLeft >> DIVIDE8);     // divide by 8
    right = (sumRight >> DIVIDE8);  // divide by 8
    
    
  
    
   // forward 
   if(((((right - left) > WHITE)) && ((right + left) > BLACK)) && (lineDetect > RESET)) {
      
         TB1CCR1 = OFF;
         TB1CCR2 = OFF;
         TB2CCR1 = OFF;
         TB2CCR2 = OFF;
            
        TB1CCR1 = WHEEL40PERCENT;   // P3.4 Right Forward PWM duty cycle
        TB1CCR2 = WHEEL40PERCENT;  // P3.5 Left Forward PWM duty cycle
    }
      // forward 
   if(((((left - right) > WHITE)) && ((right + left) > BLACK)) && (lineDetect > RESET)) {
      
        TB1CCR1 = OFF;
        TB1CCR2 = OFF;
        TB2CCR1 = OFF;
        TB2CCR2 = OFF;
            
        TB1CCR1 = WHEEL40PERCENT;   // P3.4 Right Forward PWM duty cycle
        TB1CCR2 = WHEEL40PERCENT;  // P3.5 Left Forward PWM duty cycle
    }
   
   
   
    // small forward correction
    if(((right - left) > WHITE) && (lineDetect > RESET)) {
        
        TB1CCR1 = OFF;
        TB1CCR2 = OFF;
        TB2CCR1 = OFF;
        TB2CCR2 = OFF;
            
        TB1CCR2 = WHEEL50PERCENT;
        TB1CCR2 = WHEEL50PERCENT;
    }
      
    // small forward correction
    if(((right - left) < WHITE) && (lineDetect > RESET)) {
        
        TB1CCR1 = OFF;
        TB1CCR2 = OFF;
        TB2CCR1 = OFF;
        TB2CCR2 = OFF;
            
        TB1CCR2 = WHEEL80PERCENT;
        TB1CCR2 = WHEEL80PERCENT;
    }
   
   

    
   
    // big correction
    if(((right - left) < WHITE) && (lineDetect > RESET)) {
        TB1CCR1 = OFF;
        TB1CCR2 = OFF;
        TB2CCR1 = OFF;
        TB2CCR2 = OFF;
            
        TB1CCR1 = WHEEL50PERCENT;
        TB2CCR2 = WHEEL60PERCENT;
       
    }  
       // big correction
    if(((left - right) < WHITE) && (lineDetect > RESET)) {
        TB1CCR1 = OFF;
        TB1CCR2 = OFF;
        TB2CCR1 = OFF;
        TB2CCR2 = OFF;
            
        TB2CCR1 = WHEEL60PERCENT;
        TB1CCR2 = WHEEL50PERCENT;
       
    } 
   

   


     
    
    
   
 
   
   
   
   
    
        
  // turn off LED when thumb wheel is greater than 800
  if(ADC_Thumb > LEDOFF) {
    P3OUT &= ~IR_LED;            // LED OFF
  }  
   
  pressed_SW1 = RESET;
  pressed_SW2 = RESET;
  
  sumRight = RESET;
  sumLeft = RESET;
  
  left = RESET;
  right = RESET;

 }
//------------------------------------------------------------------------------
}
}



