#ifndef TM1637_H
#define TM1637_H

#include <xc.h>
#include "xtal_freq.h"

/*******************************************************************************
 * USER PINOUT CONFIGURATION
 * The user can change PORT / TRIS / PINO to be used.
 ******************************************************************************/
// CLK Pin configuration (Default: RB3)
#define TM1637_CLK_PORT       PORTBbits.RB3
#define TM1637_CLK_TRIS       TRISBbits.TRISB3

// DIO Pin configuration (Default: RB4)
#define TM1637_DIO_PORT       PORTBbits.RB4
#define TM1637_DIO_TRIS       TRISBbits.TRISB4

/*******************************************************************************
 * INTERNAL DRIVER MACROS (Do not change).
 ******************************************************************************/
#define us  2
#define SETPIN(PIN) (1 << (PIN))
#define GETPIN(PIN) (PORTA & PINSET(PIN))

#define CLK     TM1637_CLK_PORT
#define DIO     TM1637_DIO_PORT
#define DIOIO   TM1637_DIO_TRIS


/*******************************************************************************
 * TM1637 BRIGHTNESS LEVELS DEFINES
 ******************************************************************************/
#define DISPLAY_OFF     0x80 // TURN OFF DISPLAY
#define BRIGHTNESS_0    0x88 // BRIGHTNESS LEVEL 0 -> LOWEST
#define BRIGHTNESS_1    0x89 // BRIGHTNESS LEVEL 1 -> LIGHT LOW
#define BRIGHTNESS_2    0x8A // BRIGHTNESS LEVEL 2 -> LOW
#define BRIGHTNESS_3    0x8B // BRIGHTNESS LEVEL 3 -> LIGHT MID
#define BRIGHTNESS_4    0x8C // BRIGHTNESS LEVEL 4 -> MID
#define BRIGHTNESS_5    0x8D // BRIGHTNESS LEVEL 5 -> LIGHT HIGH
#define BRIGHTNESS_6    0x8E // BRIGHTNESS LEVEL 6 -> HIGH
#define BRIGHTNESS_7    0x8F // BRIGHTNESS LEVEL 7 -> HIGHEST

// TM1637 function prototypes

void tm1637_start(void);
void tm1637_stop(void);
void tm1637_write(unsigned char);
void tm1637_on(void);
inline void tm1637_display_number(unsigned int, unsigned char);
void tm1637_brightness(unsigned char);

#endif // TM1637_H