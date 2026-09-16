
#include "pic16f88x_.h"

inline void anselL_init(unsigned char byte)
{
    ANSEL = byte;
    return;
}
inline void anselH_init(unsigned char byte)
{
    ANSELH = byte;
    return;
}
inline void CM1CON0_init(unsigned char byte)
{
    CM1CON0 = byte;
    return;
}

inline void CM2CON0_init(unsigned char byte)
{
    CM2CON0 = byte;
    return;
}

inline void porta_init(unsigned char trisa_byte, unsigned char porta_byte)
{
    TRISA   =   trisa_byte; 
    PORTA   =   porta_byte; // Clear PORTA
    return;
}
inline void portb_init(unsigned char trisb_byte, unsigned char portb_byte)
{
    TRISB   =   trisb_byte;
    PORTB   =   portb_byte; // Clear PORTB
    return;
}
inline void portc_init(unsigned char trisc_byte, unsigned char portc_byte)
{
    TRISC   =   trisc_byte;
    PORTC   =   portc_byte;
    return;
}
inline void adcon_init(unsigned char byte)
{

    return;
}
inline void ccp2con_init(unsigned char byte)
{
    CCP2CON = byte;
    return;
}

inline void tmr2_init(unsigned char byte)
{
    T2CON = byte;
    return;
}

inline void osc_init(unsigned char byte)
{
    OSCCON  =  byte;
    return;
}


inline void uart_init(void)
{
    TXSTAbits.BRGH = 1;
    BAUDCTLbits.BRG16 = 0;
    TXSTAbits.SYNC = 0;
    //SPBRGH = 0;
    SPBRG = 51;
    RCSTAbits.SPEN = 1;
    TXSTAbits.TXEN = 1;
    return;
}

void send_byte(uint8_t byte)
{
    while(!PIR1bits.TXIF);
    TXREG = (byte);
    while(!TXSTAbits.TRMT);
    return;
}

void send_uint16(uint16_t uint16)
{
    for(uint8_t i = 0; i < 2; i++)
    {    
        while(!PIR1bits.TXIF);
        TXREG = (uint16 & 0xFF);
        uint16 >>= 8;
        while(!TXSTAbits.TRMT);
    }
    return;
}
void send_uint32(uint32_t uint32)
{
    for(uint8_t i = 0; i < 4; i++)
    {
        while(!PIR1bits.TXIF);
        TXREG = (uint32 & 0xFF);
        uint32 >>= 8;
        while(!TXSTAbits.TRMT);
    }
    return;
}

inline void init_PWM2_(unsigned char pr2_) {
    
    TRISCbits.TRISC1 = 1;
    PR2 = pr2_;
    CCP2CON = 0b00001100;
    CCPR2L = 0;

    PIR1bits.TMR2IF = 0;
    T2CON = 0b00000100;
    //T2CONbits.TMR2ON = 1;
    while(!PIR1bits.TMR2IF);
    PIR1bits.TMR2IF = 0;
    TRISCbits.TRISC1 = 0;
}

inline void set_PWM2_Duty(unsigned int duty) {
    if(duty >= 319) duty = 319;
    CCPR2L = duty >> 2;
    CCP2CON = (CCP2CON & 0xCF) | ((duty & 0x03) << 4);
}

void set_fan_percent(unsigned char percent) {
    if(percent > 100) percent = 100;
    unsigned int _duty = ((unsigned long)percent * 319UL) / 100;
    set_PWM2_Duty(_duty);
}

inline void adc_module_init(void)
{   
    ADCON0 = 0x81;
    ADCON1 = 0x80;
    ADCON0bits.ADON = 1;
    __delay_ms(1);
    return;
}

inline uint8_t crcx(uint8_t * data, uint8_t len)
{
    uint8_t crcx_ = 0;
    for (uint8_t i = 0; i < len; i++)
    {
        crcx_ ^= data[i];
    }
    return crcx_;
}