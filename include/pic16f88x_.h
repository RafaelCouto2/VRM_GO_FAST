#ifndef PIC16F88X__H
#define PIC16F88X__H

#include <xc.h>
#include "xtal_freq.h"
//#include <math.h>

#pragma config FOSC = INTRC_NOCLKOUT
#pragma config WDTE = OFF
#pragma config PWRTE = ON
#pragma config MCLRE = ON
#pragma config CP = OFF
#pragma config CPD = OFF
#pragma config BOREN = OFF
#pragma config LVP = OFF

#define us      2
#define FAN_25  0
#define FAN_50  1
#define FAN_75  2
#define FAN_100 3
#define STATUS_ 0x01
#define SET_FAN 0x02
#define SET_TARGET_TEMP 0x03
#define DEBUG_ 0x04

typedef union 
{
    struct {
        uint8_t cmd;
        uint8_t fan;
        uint8_t temp;
        uint8_t crc;
    } f;
    uint8_t raw[4];
} packet_t;

inline void porta_init(unsigned char trisa_, unsigned char porta_);
inline void portb_init(unsigned char trisb_, unsigned char portb_);
inline void portc_init(unsigned char trisc_, unsigned char portc_);
inline void ccp2con_init(unsigned char byte);
inline void tmr2_init(unsigned char byte);
inline void CM1CON0_init(unsigned char byte);
inline void CM2CON0_init(unsigned char byte);
inline void adcon_init(unsigned char byte);
inline void osc_init(unsigned char byte);
inline void anselL_init(unsigned char byte);
inline void anselH_init(unsigned char byte);
inline void uart_init(void);
inline void init_PWM2_(unsigned char byte);
inline void set_PWM2_Duty(unsigned int uint16_);
inline void adc_module_init(void);

inline uint8_t crcx(uint8_t * data, uint8_t len);
void set_fan_percent(unsigned char byte);
void send_byte(uint8_t byte);
void send_uint16(uint16_t uint16);
void send_uint32(uint32_t uint32);
#endif // PIC16F88X__H
