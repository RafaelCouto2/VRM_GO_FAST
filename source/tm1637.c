#include "tm1637.h"

static const unsigned char _hextable[10] = {
                                    0x3F, 0x06,
                                    0x5B, 0x4F,
                                    0x66, 0x6D,
                                    0x7D, 0x07,
                                    0x7F, 0x67};

void tm1637_start(void)
{
    CLK = 1;
    __delay_us(us);
    DIO = 1;
    __delay_us(us);
    DIO = 0;
    __delay_us(us);
    CLK = 0;
    //__delay_us(us);
    return;
}

void tm1637_stop(void)
{
    CLK = 0;
    __delay_us(us);
    DIO = 0;
    __delay_us(us);
    CLK = 1;
    __delay_us(us);
    DIO = 1;
    //__delay_us(us);

    return;
}

void tm1637_write(unsigned char data)
{
    unsigned char garbage = 0;
    
    for (unsigned char i = 0; i < 8; i++) 
    {
        DIO = (data & 0x01);
        __delay_us(us);
        CLK = 1;
        __delay_us(us);
        CLK = 0;
        data >>= 1;
        __delay_us(us);
    }
    DIO = 0;
    __delay_us(us);

    DIOIO = 1;
    __delay_us(us);

    CLK = 1;
    __delay_us(us);

    garbage = !DIO;
    //__delay_us(us);

    CLK = 0;
    __delay_us(us);

    DIOIO = 0;
    //__delay_us(us);

    return;
}

/**
 * Sends a number to be shown on the display. 
 * 
 * @param {number} - The number to be displayed.
 * @param {brightness_level} - The brightness level of the display.
 */
inline void tm1637_display_number(unsigned int number, unsigned char brightness_level)
{
    unsigned char tmdata[4];
    tmdata[0] = ((number / 1000) % 10);
    tmdata[1] = ((number / 100) % 10);
    tmdata[2] = ((number / 10) % 10);
    tmdata[3] = ((number / 1) % 10);

    tm1637_start();
    tm1637_write(0x40);
    tm1637_stop();
    
    tm1637_start();
    tm1637_write(0xC0);
    tm1637_write(_hextable[tmdata[0]]);
    tm1637_write(_hextable[tmdata[1]]);
    tm1637_write(_hextable[tmdata[2]]);
    tm1637_write(_hextable[tmdata[3]]);
    tm1637_stop();

    tm1637_brightness(brightness_level);
    return;
}

/**
 * @brief Sets the display brightness using the definitions in the TM1637.h header file.
 *
 * @note Example usage:
 *       @code
 *       tm1637_brightness(BRIGHTNESS_1); // Sets brightness level 1 (2/16)
 *       @endcode
 */
void tm1637_brightness(unsigned char brlvl)
{
    tm1637_start();
    tm1637_write(brlvl);
    tm1637_stop();
    return;
}