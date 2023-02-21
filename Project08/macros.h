// **************macros.h*************
// 
// This file contains specific defined values that are used throughout the program.
// 
// 
// 
// Paul Svetlov
// ECE 306
// pvsvetlo@ncsu.edu
// September 16, 2016




// Required defines
// In the event the universe no longer exists, this bit will reset
#define ALWAYS                  (1)
#define CNTL_STATE_INDEX        (3) // Control States
#define LED1                 (0x01) // LED 1
#define LED2                 (0x02) // LED 2
#define LED3                 (0x04) // LED 3
#define LED4                 (0x08) // LED 4
#define LED5                 (0x10) // LED 5
#define LED6                 (0x20) // LED 6
#define LED7                 (0x40) // LED 7
#define LED8                 (0x80) // LED 8
#define SW1                  (0x01) // Switch 1
#define SW2                  (0x02) // Switch 2
#define CNTL_STATE_INDEX        (3)
// LCD
#define LCD_HOME_L1	          0x80
#define LCD_HOME_L2         	0xA0
#define LCD_HOME_L3         	0xC0
#define LCD_HOME_L4         	0xE0





//MACROS========================================================================
#define FLLN_BITS          (0x03ffu)
#define FLLN_255           (0x00ffu)
#define CSLOCK                  (0x01) // Any incorrect password locks registers





//***************ports.c********************
// Port J Pins
#define XINR                 (0x10) // XINR
#define XOUTR                (0x20) // XOUTR
#define CLEAR_REGISTER     (0X0000)



#define V_DETECT_R (0x01) // Voltage from Right Detector
#define V_DETECT_L (0x02) // Voltage from Right Detector
#define LCD_BACKLITE (0x04) // Control Signal for LCD_BACKLITE
#define V_THUMB (0x08) // Voltage from Thumb Wheel
#define SPI_CS_LCD (0x10) // LCD Chip Select
#define RESET_LCD (0x20) // LCD Reset
#define SIMO_B (0x40) // SPI mode- slave in/master out of USCI_B0
#define SOMI_B (0x80) // SPI mode- slave out/master in of USCI_B0
//------------------------------------------------------------------------------

//port 2
#define USB_TXD (0x01) // tranmits data
#define USB_RXD (0x02) // recieves data
#define SPI_SCK (0x04)
#define UNKNOWN1 (0x08)
#define UNKNOWN2 (0x10)
#define CPU_TXD (0x20)
#define CPU_RXD (0x40)
#define UNKNOWN3 (0x80)

//port 3
#define X (0x01)
#define Y (0x02)
#define ZE (0x04)
#define IR_LED (0x08)
#define R_FORWARD (0x10)
#define L_FORWARD (0x20)
#define R_REVERSE (0x40)
#define L_REVERSE (0x80)

//port 4
#define SW1 (0x01)
#define SW2 (0x02)

// Port J Pins
#define IOT_WAKEUP (0x01) // 
#define IOT_FACTORY (0x02) // 
#define IOT_STA_MINIAP (0x04) // 
#define IOT_RESET (0x08) // 
#define XINR (0x10) // 
#define XOUTR (0x20) // XOUTR




//**************init.c******************
#define LCD_WIDTH (11)
#define LCD_POS_ONE (0)

#define RESET_PORT (0x00)



#define SPACES1 (1)
#define SPACES2 (2)
#define SPACES3 (3)
#define SPACES6 (6)
#define QUARTER_SEC (50)   //.25 sec
#define QUARTER_SEC_PLUS (75)
#define HALF_SEC (100)
#define THREE_QUARTER_SEC (150)
#define SEC (200)
#define SEC_HALF (300)
#define TWO_SEC (400)
#define THREE_SEC (600)
#define ONE_AND_FOURTH_SEC (250)   //1.25 sec
#define FIVE_SEC (1000)
#define INCREMENT_TIME (1)
#define INCREMENT (1)
#define TIME_RESET (0)
#define TIME_SET (1)
#define TS_START (0)
#define SIZE_RESET5 (5)
#define SIZE_RESET (0)
#define BIG (1)
#define LITTLE (0)
#define RESET_REGISTER (0x00)
#define NO_MOVEMENT (0x00)
#define MOVEMENT (1)
#define START (1)
#define MOVING_SEC_ONE (1)
#define MOVING_SEC_TWO (2)
#define TWO_NINE_SEC (580)
#define ZERO_FIVE_SEC (10)
#define ZERO_ONE_SEC (20)
#define ONE_SEVEN_FIVE (35)
#define TWO_EIGHT_SEC (560)
#define POINT_SIX_SEC (120)
#define POINT_FOUR_SEC (80)
#define POINT_TWO_SEC (40)
#define ZERO_SHAPE (0)
#define LAST_SHAPE (3)
#define FIRST_SHAPE (1)
#define SEC_SHAPE (2)
#define TA0CCR0_INTERVAL (25000)
#define TA0CCR1_INTERVAL (25000)
#define TA0CCR1_5MSEC (2500)
#define PRESSED_SW1 (2)
#define PRESSED_SW2 (4)
#define TA0_100 (50000)
#define DEBOUNCE (50000)
#define PRESS_RESET (0)
#define RESET (0)
#define CYCLE10 (10)
#define CHANNEL_A01 (1)
#define CHANNEL_A02 (2)
#define CHANNEL_A03 (3)
#define RESET_STATE (0)
#define WHITE (100)
#define BLACK (500)
#define NULL (0)
#define POS00 (0)
#define POS01 (1)
#define POS02 (2)
#define POS03 (3)
#define POS04 (4)
#define ARRAY3 (3)
#define ARRAY4 (4)
#define ARRAY5 (5)
#define ARRAY10 (10)
#define ARRAY11 (11)
#define ARRAY33 (33)
#define BASE (0x30)
#define THOUSANDS_PLACE (999)
#define OFF (0)
#define ON (1)
#define WHEEL_PERIOD (10000)
#define WHEEL10PERCENT (1000)
#define WHEEL20PERCENT (2000)
#define WHEEL30PERCENT (3000)
#define WHEEL40PERCENT (4000)
#define WHEEL50PERCENT (5000)
#define WHEEL60PERCENT (6000)
#define WHEEL70PERCENT (7000)
#define WHEEL80PERCENT (8000)
#define WHEEL90PERCENT (9000)
#define WHEEL100PERCENT (10000)
#define ARRAY8 (8)
#define ARRAY9 (9)
#define STARTDETECT (50)
#define DIVIDE8 (3)
#define LEDOFF (800)

#define BEGINNING (0)
#define SMALL_RING_SIZE (38)
#define SMALL_RING_SIZE_PLUS (39)
#define LARGE_RING_SIZE (38)

#define BAUD_9600 (52)
#define BAUD_115200 (4)
#define UCA0MCTLW_BAUD_9600 (0x4911)
#define UCA0MCTLW_BAUD_115200 (0x5551)
#define SET1 (1)
#define TRUE (1)
#define FALSE (0)
#define ZERO (0)
#define DISABLE (-1)
#define LINEFEED (0x0A)
#define POINTER_OFFSET (12)
