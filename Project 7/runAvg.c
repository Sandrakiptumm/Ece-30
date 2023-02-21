if(whiteCalibrate > 9) {
      whiteCalibrate = RESET;
    }
     switch(whiteCalibrate) {
      case 0:
        break;
      case 1:
        leftWhiteRunAvg[0] = ADC_Left_Detector;
        rightWhiteRunAvg[0] = ADC_Right_Detector;
        break;  
      case 2:
        leftWhiteRunAvg[1] = ADC_Left_Detector;
        rightWhiteRunAvg[1] = ADC_Right_Detector;
        break;
      case 3:
        leftWhiteRunAvg[2] = ADC_Left_Detector;
        rightWhiteRunAvg[2] = ADC_Right_Detector;
        break;
      case 4:
        leftWhiteRunAvg[3] = ADC_Left_Detector;
        rightWhiteRunAvg[3] = ADC_Right_Detector;
        break;
      case 5:
        leftWhiteRunAvg[4] = ADC_Left_Detector;
        rightWhiteRunAvg[4] = ADC_Right_Detector;
        break;
      case 6:
        leftWhiteRunAvg[5] = ADC_Left_Detector;
        rightWhiteRunAvg[5] = ADC_Right_Detector;
        break;
      case 7:
        leftWhiteRunAvg[6] = ADC_Left_Detector;
        rightWhiteRunAvg[6] = ADC_Right_Detector;
        break;
      case 8:
        leftWhiteRunAvg[7] = ADC_Left_Detector;
        rightWhiteRunAvg[7] = ADC_Right_Detector;
        i = RESET;
        while(i < 8) {
          sumWhiteLeft += leftWhiteRunAvg[i];
          sumWhiteRight += rightWhiteRunAvg[i]; 
          i++;
        }
        LeftWhite = (sumWhiteLeft >> 3);
        RightWhite = (sumWhiteRight >> 3);
        break;
      default:
        break;
    } 
    
    
    if(blackCalibrate > 9) {
      blackCalibrate = RESET;
    }
    switch(blackCalibrate) {
      case 0:
        break;
      case 1:
        leftBlackRunAvg[0] = ADC_Left_Detector;
        rightBlackRunAvg[0] = ADC_Right_Detector;
        break;  
      case 2:
        leftBlackRunAvg[1] = ADC_Left_Detector;
        rightBlackRunAvg[1] = ADC_Right_Detector;
        break;
     case 3:
       leftBlackRunAvg[2] = ADC_Left_Detector;
       rightBlackRunAvg[2] = ADC_Right_Detector;
       break;
     case 4:
       leftBlackRunAvg[3] = ADC_Left_Detector;
       rightBlackRunAvg[3] = ADC_Right_Detector;
       break;
     case 5:
       leftBlackRunAvg[4] = ADC_Left_Detector;
       rightBlackRunAvg[4] = ADC_Right_Detector;
       break;
     case 6:
       leftBlackRunAvg[5] = ADC_Left_Detector;
       rightBlackRunAvg[5] = ADC_Right_Detector;
       break;
     case 7:
       leftBlackRunAvg[6] = ADC_Left_Detector;
       rightBlackRunAvg[6] = ADC_Right_Detector;
       break;
     case 8:
       leftBlackRunAvg[7] = ADC_Left_Detector;
       rightBlackRunAvg[7] = ADC_Right_Detector;
       i = RESET;
       while(i < 8) {
          sumBlackLeft += leftBlackRunAvg[i];
          sumBlackRight += rightBlackRunAvg[i]; 
          i++;
       } 
       LeftBlack = (sumBlackLeft >> 3);
       RightBlack = (sumBlackRight >> 3);
       break;
     default:
       break;
  } 


    time_count++;
    if(time_count == 2) {
      pressed_SW1 = PRESSED_SW1;
      time_count = TIME_RESET;
    }
    
    
    
    if((((ADC_Right_Detector - ADC_Left_Detector) > 100)) && ((ADC_Right_Detector + ADC_Left_Detector) > 500)) {
      
        TB1CCR1 = 4000;
        TB1CCR2 = 4000;
    }

    if((ADC_Right_Detector - ADC_Left_Detector) > 100) {
        TB2CCR2 = OFF;
        TB1CCR1 = OFF;
        TB1CCR2 = 4500;
        TB1CCR2 = 4500;
    }
    
    if((ADC_Right_Detector - ADC_Left_Detector) < 100) {
        TB2CCR1 = OFF;
        TB1CCR2 = OFF;
        TB1CCR1 = 6000;
        TB2CCR2 = 6000;
      
    } 
    
    
    
       
   /*
  
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
  
  */