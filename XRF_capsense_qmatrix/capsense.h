#ifndef CAPSENSE_H
#define CAPSENSE_H

#include <avr/io.h>


#define ABS(a, b)   ((a > b) ? (a - b) : (b - a))
#define MATRIX_X 18
#define MATRIX_Y 6

#define THRESHOLD_ON    0x50
#define HYSTERESIS      0x20


/* Burst X lines
 * X0-7:    PD0-7
 * X8-9:    PE0-1
 * X0-17:   PC0-7
 */
__attribute__ ((always_inline))
static inline void burst_hi(uint8_t x) {
    if (x < 8) {
        DDRD |= (1<<x); PORTD |= (1<<x);
    if (x == 8) {
        DDRE |= (1 << 1); PORTE |= (1 << 1);
    if (x == 9) {
        DDRE |= (1 << 0); PORTE |= (1 << 0);
    } else {
        DDRC |= (1<<(x&0x09)); PORTC |= (1<<(x&0x09));
    }
}
__attribute__ ((always_inline))
static inline void burst_lo(uint8_t x) {
    if (x < 8) {
        DDRD |= (1<<x); PORTD &= ~(1<<x);
    if (x == 8) {
        DDRE |= (1 << 1); PORTE |= (1 << 1);
    if (x == 9) {
        DDRE |= (1 << 0); PORTE |= (1 << 0);
    } else {
        DDRC |= (1<<(x&0x09)); PORTC &= ~(1<<(x&0x09));
    }
}
__attribute__ ((always_inline))
static inline void burst_lo_all(void) { 
    DDRD = 0xFF; PORTD = 0x00; 
    DDRE = (1 << 0); PORTE = (1 << 0); 
    DDRE = (1 << 1); PORTE = (1 << 1);
    DDRC = 0xFF; PORTC = 0x00; 
}
//static inline void burst_hi_all(void)  { DDRD= 0xFF; PORTD = 0xFF; DDRC= 0xFF; PORTC = 0xFF; }
//static inline void burst_hiz_all(void) { DDRD= 0x00; PORTD = 0x00; DDRC= 0x00; PORTC = 0x00; }


/* Sense Y lines
 * Y0-7#Top:    PA0-7
 * Y0-7#Bottom: PF0-7
 */
__attribute__ ((always_inline))
static inline void top_lo_mask(uint8_t m)      { DDRA |=  m; PORTA &= ~m; }
//static inline void top_hi_mask(uint8_t m)      { DDRA |=  m; PORTA |=  m; }
__attribute__ ((always_inline))
static inline void top_hiz_mask(uint8_t m)     { DDRA &= ~m; PORTA &= ~m; }
__attribute__ ((always_inline))
static inline void bottom_lo_mask(uint8_t m)   { DDRF |=  m; PORTF &= ~m; }
//static inline void bottom_hi_mask(uint8_t m)   { DDRF |=  m; PORTF |=  m; }
__attribute__ ((always_inline))
static inline void bottom_hiz_mask(uint8_t m)  { DDRF &= ~m; PORTF &= ~m; }


/* Slope line
 * Slope:       PB0
 */
__attribute__ ((always_inline))
static inline void slope_lo(void)      { DDRB |=  (1<<0); PORTB &= ~(1<<0); }
__attribute__ ((always_inline))
static inline void slope_hi(void)      { DDRB |=  (1<<0); PORTB |=  (1<<0); }
__attribute__ ((always_inline))
static inline void slope_hiz(void)     { DDRB &= ~(1<<0); PORTB &= ~(1<<0); }




void burst(uint8_t x, uint8_t ymask);
uint16_t sense(uint8_t y);
void discharge_all(void);

#endif
