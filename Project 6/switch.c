// ******switch.c***********
//  
// This file displays text on the LCD display using switches.
//
// Paul Svetlov
// ECE 306
// pvsvetlo@ncsu.edu
// September 16, 2016



#include  "msp430.h"
#include "macros.h"
#include "functions.h"

extern char *display_1;
extern char *display_2;
extern char *display_3;
extern char *display_4;

extern char posL1;
extern char posL2;
extern char posL3;
extern char posL4;

extern char start_moving;
extern int shape;

extern volatile unsigned int SW1_Pressed;
extern volatile unsigned int SW2_Pressed;

extern volatile unsigned int SW1_Count;
extern volatile unsigned int SW2_Count;

void Switches_Process(void){
//------------------------------------------------------------------------------
  
  //if(SW1_Pressed) {
    //P1OUT |= LCD_BACKLITE;          // turn on backlight
    //SW1_Pressed = PRESS_RESET;       // reset
    //SW1_Count++;

    //display_1 = "SW1";
    //Display_Process();
    
  //}
  
  //if(SW2_Pressed){
    //P1OUT &= ~LCD_BACKLITE;          // turn off backlight
    //SW2_Pressed = PRESS_RESET;        // reset 
    //SW2_Count++;

    //display_1 = "SW2";
    //Display_Process();
  //}
  /*
  if (!(P4IN & SW1)){ 
    display_1 = "";
    display_2 = "";
    display_3 = "";
    Display_Process();
    five_msec_Delay(SEC);
    forward();
    display_1 = "forward";
    Display_Process();
    five_msec_Delay(SEC);
    stop();
    five_msec_Delay(SEC);
    reverse();
    display_1 = "reverse";
    Display_Process();
    five_msec_Delay(TWO_SEC);
    stop();
    five_msec_Delay(SEC);
    forward();
    display_1 = "forward";
    Display_Process();
    five_msec_Delay(SEC);
    stop();
    five_msec_Delay(SEC);
    clockwise(); 
    display_1 = "clockwise";
    Display_Process();
    five_msec_Delay(SEC);
    stop();
    five_msec_Delay(SEC);
    counterclockwise(); 
    display_1 = "C_clockwise";
    Display_Process();
    five_msec_Delay(SEC);
    stop();
    five_msec_Delay(SEC);
    display_1 = "Done";
    Display_Process();
    five_msec_Delay(SEC);
    display_1 = "Hello";
    display_2 = "Press a";
    display_3 = "Button";
    Display_Process();
  }
  if (!(P4IN & SW2)){
    display_1 = "LED OFF";
    Display_Process(); 
  }    
  */
  
  /*
  switch(shape) {
    case ZERO_SHAPE:
      if (!(P4IN & SW1)){
        display_1 = "Circle";
        Display_Process();
        five_msec_Delay(ZERO_ONE_SEC);
        shape++;
      }
  
      break;
    case FIRST_SHAPE:
      if (!(P4IN & SW2)){
          five_msec_Delay(QUARTER_SEC);
          circle();
          five_msec_Delay(QUARTER_SEC);
          circle();
          five_msec_Delay(ZERO_ONE_SEC);
      } 
      if (!(P4IN & SW1)){
        display_1 = "Fiqure 8";
        Display_Process();
        five_msec_Delay(ZERO_ONE_SEC);
        shape++;
      }
      break;
    case SEC_SHAPE:
      if (!(P4IN & SW2)){
          five_msec_Delay(QUARTER_SEC);
          figure_eight();
          five_msec_Delay(ZERO_ONE_SEC);
          figure_eight();
          five_msec_Delay(ZERO_ONE_SEC);
      }
      if (!(P4IN & SW1)){
        display_1 = "Triangle";
        Display_Process();
        five_msec_Delay(ZERO_ONE_SEC);
        shape++;
      }
      break;
    case LAST_SHAPE: 
      if (!(P4IN & SW2)){
          five_msec_Delay(QUARTER_SEC  );
          triangle();
          five_msec_Delay(ZERO_ONE_SEC);
      }
      if (!(P4IN & SW1)){
          display_1 = "Select";
          Display_Process();
          five_msec_Delay(ZERO_ONE_SEC);
          shape++;
      }
  }
  if(shape > LAST_SHAPE) {
    shape = ZERO_SHAPE;
  }
  */
  

  //if (!(P4IN & SW1)){
    //start_moving = START;
    //display_1 = "UNCA";
    //posL1 = SPACES3;
    //display_2 = "NCSU";
    //posL2 = SPACES3;
    //display_3 = "ECE306";
    //posL3 = SPACES2;
    //display_4 = "P Svetlov";
    //posL4 = SPACES1;
    
    
  //}
  //if (!(P4IN & SW2)) {
    //display_1 = "Embedded";
    //posL1 = SPACES1;
    //display_2 = "Systems";
    //posL2 = SPACES2;
    //display_3 = "Rock!";
    //posL3 = SPACES3;
    //display_4 = "Go Pack!";
    //posL4 = SPACES1;
  //}
//------------------------------------------------------------------------------
}