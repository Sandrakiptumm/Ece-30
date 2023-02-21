//------------------------------------------------------------------------------
//******************************************************************************
// Hex to BCD Conversion
// Convert a Hex number to a BCD for display on an LCD or monitor
// Paul Svetlov
// October 11, 2016
//
//------------------------------------------------------------------------------

#include "macros.h"
#include  "msp430.h"
#include "functions.h"



extern char adc_char[ARRAY5]; 

void HEXtoBCD(int hex_value){
 adc_char[POS00] = '0';
 adc_char[POS01] = '0';
 adc_char[POS02] = '0';
 adc_char[POS03] = '0';
 adc_char[POS04] = NULL;
 
 int value;
 
 if (hex_value > THOUSANDS_PLACE){
  hex_value = hex_value - THOUSANDS_PLACE;
  adc_char[POS00] = '1';
 }
 value = RESET;
 while (hex_value > 99){
  hex_value = hex_value - 100;
  value = value + INCREMENT;
  adc_char[POS01] = BASE + value;
 }
 value = RESET;
 while (hex_value > 9){
  hex_value = hex_value - 10;
  value = value + INCREMENT;
  adc_char[POS02] = BASE + value;
 }
 adc_char[POS03] = BASE + hex_value;
}
//******************************************************************************
//------------------------------------------------------------------------------

