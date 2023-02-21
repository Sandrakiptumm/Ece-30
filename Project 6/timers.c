// *********timers.c*************
// 
// This file initializes and configures the timers throughout the program.
// 
// Paul Svetlov
// ECE 306
// pvsvetlo@ncsu.edu
// September 16, 2016




#include  "msp430.h"
#include "macros.h"
#include "functions.h"


extern volatile char one_time;
extern volatile unsigned int five_msec_count;
extern volatile unsigned int Time_Sequence;
extern unsigned int time;

extern volatile unsigned int SW1_Pressed;
extern volatile unsigned int SW2_Pressed;


extern unsigned int right_forward_rate;
extern unsigned int left_forward_rate;
extern unsigned int right_reverse_rate;
extern unsigned int left_reverse_rate;


void Init_Timers(void){
//------------------------------------------------------------------------------
// Timer Configurations
//------------------------------------------------------------------------------
  Init_Timer_A0(); 
  //Init_Timer_A1(); //
  //Init_Timer_B0(); //
  Init_Timer_B1(); //
  Init_Timer_B2();   //  Required for provided compiled code to work
//------------------------------------------------------------------------------
}


//void Timer_code(void){
//------------------------------------------------------------------------------
// Timer A0 interrupt code
//------------------------------------------------------------------------------
  //Time_Sequence++;
  //one_time = TIME_SET;
  //if (five_msec_count < FIVE_SEC){
    //five_msec_count++;
  //}
//------------------------------------------------------------------------------
//}

// this function delays for five milliseconds seconds for every one passed in
void five_msec_Delay(unsigned int fivemsec){
//------------------------------------------------------------------------------
  time = Time_Sequence;
  while(Time_Sequence < (time + fivemsec));  
//------------------------------------------------------------------------------
}

//------------------------------------------------------------------------------
// Timer A0 initialization sets up both A0_0 and A0_1-A0_2
void Init_Timer_A0(void) {
TA0CTL = TASSEL__SMCLK; // SMCLK source
TA0CTL |= TACLR; // Resets TA0R, clock divider, count direction
TA0CTL |= MC__CONTINOUS; // Continuous up //from x0000 to xffff over and over
TA0CTL |= ID__2; // Divide clock by 2
TA0CTL &= ~TAIE; // Disable Overflow Interrupt
TA0CTL &= ~TAIFG; // Clear Overflow Interrupt flag
TA0EX0 = TAIDEX_7; // Divide clock by an additional 8
TA0CCR0 = TA0CCR0_INTERVAL; // CCR0
TA0CCTL0 |= CCIE; // CCR0 enable interrupt
// TA0CCR1 = TA0CCR1_INTERVAL; // CCR1
// TA0CCTL1 |= CCIE; // CCR1 enable interrupt
// TA0CCR2 = TA0CCR2_INTERVAL; // CCR2
// TA0CCTL2 |= CCIE; // CCR2 enable interrupt
}
//------------------------------------------------------------------------------



// this interrupt is a 5 ms timer       **move to timers
#pragma vector = TIMER0_A0_VECTOR

__interrupt void timer_0_A0(void) {
  
   TA0CCR0 += TA0CCR1_5MSEC;
   Time_Sequence++;
} 

// this interrupt interrupts the switches to reenable SW1 and SW2  **move to timers
#pragma vector = TIMER0_A1_VECTOR

__interrupt void timer_1_A1(void){
  //make switches work
  
  switch(__even_in_range(TA0IV,14)){
    case 0: break; // No interrupt
    // CCR1 not used
    case 2:
        P4IE |= SW1;               // enable SW1 interrupt
        TA0CCTL1 &= ~CCIE;                     // disable timer interrupt
        SW1_Pressed = RESET;
      TA0CCR1 += TA0CCR1_INTERVAL; // Add Offset to TACCR1
      break;
    // CCR2 not used
    case 4: 
     
        P4IE |= SW2;               // enable SW2 interrupt
        
        TA0CCTL2 &= ~CCIE;                     // disable timer interrupt
        SW2_Pressed = RESET;
      
      TA0CCR2 += TA0CCR1_INTERVAL; // Add Offset to TACCR2
      break;
    case 14: // overflow
    //...... Add What you need happen in the interrupt ......
    break;
    default: break;
}
  
}

void Init_Timer_B1(void) {
//------------------------------------------------------------------------------
// SMCLK source, up count mode
//------------------------------------------------------------------------------
TB1CTL = TBSSEL__SMCLK; // SMCLK
TB1CTL |= MC_1; // Up Mode
TB1CTL |= TBCLR; // Clear TAR
right_forward_rate = OFF; // Set Right Forward Off
left_forward_rate = OFF; // Set Left Forward Off
TB1CCR0 = WHEEL_PERIOD; // PWM Period
TB1CCTL1 = OUTMOD_7; // CCR1 reset/set
TB1CCR1 = OFF; // P3.4 Right Forward PWM duty cycle
TB1CCTL2 = OUTMOD_7; // CCR2 reset/set
TB1CCR2 = OFF; // P3.5 Left Forward PWM duty cycle
//------------------------------------------------------------------------------
}

void Init_Timer_B2(void) {
//------------------------------------------------------------------------------
// SMCLK source, up count mode
//------------------------------------------------------------------------------
TB2CTL = TBSSEL__SMCLK; // SMCLK
TB2CTL |= MC_1; // Up Mode
TB2CTL |= TBCLR; // Clear TAR
right_reverse_rate = OFF; // Set Right Reverse Off
left_reverse_rate = OFF; // Set Left Reverse Off
TB2CCR0 = WHEEL_PERIOD; // PWM Period
TB2CCTL1 = OUTMOD_7; // CCR1 reset/set
TB2CCR1 = OFF; // P3.4 Right Reverse PWM duty cycle
TB2CCTL2 = OUTMOD_7; // CCR2 reset/set
TB2CCR2 = OFF; // P3.5 Left Reverse PWM duty cycle
//------------------------------------------------------------------------------
}

