// ***********functions.h****************** 
// 
// This file contains the function declarations for the entire program
// 
// 
// Paul Svetlov
// ECE 306
// pvsvetlo@ncsu.edu
// September 16, 2016



// Function prototypes main
void main(void);
void Init_Conditions(void);
void Switches_Process(void);
void Init_Timers(void);
void Init_LEDs(void);
void Display_Process(void);
void five_msec_Delay(unsigned int fivemsec);
void Timer_code(void);

// Function prototypes clocks
void Init_Clocks(void);

// Function prototypes systems
void enable_interrupts(void);

// Function prototypes
__interrupt void Timer2_B0_ISR(void);
 __interrupt void TIMER2_B1_ISR(void);
void Init_Timer_A0(void);
void Init_Timer_B2(void);
void measure_delay(void);
void usleep10(unsigned int usec);

// Function prototypes ports
void Init_Ports(void);
void Init_Port1(void);
void Init_Port2(void);
void Init_Port3(void);
void Init_Port4(void);
void Init_PortJ(void);

// LCD
void Init_LCD(void);
void WriteIns(char instruction);
void WriteData(char data);
void ClrDisplay(void);
void SetPostion(char pos);
void DisplayOnOff(char data);
void lcd_BIG_mid(void);
void lcd_4line(void);
void lcd_out(char *s, char line, char position);

void grab_a_character(void);
int wait_for_character(void);
void menu(void);

// SPI
void Init_SPI_B0(void);
void SPI_B0_write(char byte);

// Switches
void Init_Switches(void);
void switch_control(void);
void enable_switch_SW1(void);
void enable_switch_SW2(void);
void disable_switch_SW1(void);
void disable_switch_SW2(void);
void Switches_Process(void);

// moving and stop

void forward(void);
void stop(void);
void circle(void);
void figure_eight(void);
void triangle(void);
void reverse(void);
void clockwise(void);
void counterclockwise(void);

// other

void Init_ADC(void);
void HEXtoBCD(int hex_value);
void Init_Timer_B1(void);
void Init_Timer_B2(void);

void Init_Serial_UCA0(int baud, int hexVal);
void Init_Serial_UCA1(int baud, int hexVal);
void Transmit_UCA0(char c);
void Transmit_UCA1(char c);
void recieve_A0();