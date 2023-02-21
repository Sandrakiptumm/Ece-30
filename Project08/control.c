// *********control.c*************
// 
// This file controls the motors.
// 
// Paul Svetlov
// ECE 306
// pvsvetlo@ncsu.edu
// September 19, 2016



#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"
#include  "functions.h"

extern volatile unsigned int Time_Sequence;


// makes the car go forward
void forward(void) {
    P3OUT |= L_FORWARD;         // turn left wheel on
    P3OUT |= R_FORWARD;         // turn right wheel on 
} 

// makes the car go reverse
void reverse(void) {
    P3OUT |= L_REVERSE;         // turn left wheel on
    P3OUT |= R_REVERSE;         // turn right wheel on 
} 


// makes the car spin clockwise
void clockwise(void) {
    P3OUT |= L_FORWARD;         // turn left wheel on
    P3OUT |= R_REVERSE;         // turn right wheel on 
}  

// makes the car spin counterclockwise
void counterclockwise(void) {
    P3OUT |= L_REVERSE;         // turn left wheel on
    P3OUT |= R_FORWARD;         // turn right wheel on 
} 


// makes the car stop
void stop(void) {
  P3OUT &= ~L_FORWARD;          // turn left wheel off
  P3OUT &= ~R_FORWARD;          // turn right wheel off
  P3OUT &= ~L_REVERSE;          // turn left wheel off
  P3OUT &= ~R_REVERSE;          // turn right wheel off
}



// this function makes a circle by turning a wheel on by a freq. pulse
void circle(void) {
  Time_Sequence = TIME_RESET;
  while(Time_Sequence < TWO_NINE_SEC) {
    forward();
    five_msec_Delay(ZERO_FIVE_SEC);
    P3OUT &= ~R_FORWARD;         // turn right wheel off
    five_msec_Delay(ZERO_ONE_SEC);
    Time_Sequence++;
  } 
  stop(); 
} 


// this function makes a figure 8 by making circles like circle() by driving between circles
void figure_eight(void) {
  Time_Sequence = TIME_RESET;
  while(Time_Sequence < TWO_NINE_SEC) {
    forward();
    five_msec_Delay(ZERO_FIVE_SEC);
    P3OUT &= ~R_FORWARD;         // turn right wheel off
    five_msec_Delay(ZERO_ONE_SEC);
    Time_Sequence++;
  } 
  stop();
  forward();
  five_msec_Delay(ONE_SEVEN_FIVE);
  stop();
  
  Time_Sequence = TIME_RESET;
  while(Time_Sequence < TWO_NINE_SEC) {
    forward();
    five_msec_Delay(ZERO_FIVE_SEC);
    P3OUT &= ~L_FORWARD;         // turn right wheel off
    five_msec_Delay(ZERO_ONE_SEC);
    Time_Sequence++;
  }
  stop();
  forward();
  five_msec_Delay(ONE_SEVEN_FIVE);
  stop(); 
} 



// this function makes a triangle by going forward then turning about 60 degrees then repeats this three times
void triangle(void) {
  Time_Sequence = TIME_RESET;
  forward();
  five_msec_Delay(POINT_SIX_SEC);
  stop();
  P3OUT |= R_FORWARD;         // turn right wheel on 
  five_msec_Delay(HALF_SEC);
  stop();
  five_msec_Delay(ZERO_ONE_SEC);
  
  forward();
  five_msec_Delay(POINT_SIX_SEC);
  stop();
  P3OUT |= R_FORWARD;         // turn right wheel on 
  five_msec_Delay(POINT_FOUR_SEC);
  stop();
  five_msec_Delay(ZERO_ONE_SEC);
 
  forward();
  five_msec_Delay(POINT_SIX_SEC);
  stop();
  P3OUT |= R_FORWARD;         // turn right wheel on 
  five_msec_Delay(POINT_FOUR_SEC);
  stop();
  five_msec_Delay(ZERO_ONE_SEC);
  forward();
  five_msec_Delay(POINT_TWO_SEC);
  stop();
  five_msec_Delay(ZERO_ONE_SEC);
}  





