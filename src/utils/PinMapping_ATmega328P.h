#ifndef PIN_MAPPING_ATMEGA328P_H
#define PIN_MAPPING_ATMEGA328P_H

// ATmega328PとArduino Unoのピン番号対応
// Digital Pins
#define PD0_PIN 0  // ATmega328P Pin PD0 -> Digital Pin 0 (RX)
#define PD1_PIN 1  // ATmega328P Pin PD1 -> Digital Pin 1 (TX)
#define PD2_PIN 2  // ATmega328P Pin PD2 -> Digital Pin 2 (INT0)
#define PD3_PIN 3  // ATmega328P Pin PD3 -> Digital Pin 3 (OC2B/INT1)
#define PD4_PIN 4  // ATmega328P Pin PD4 -> Digital Pin 4 (T0/XCK)
#define PD5_PIN 5  // ATmega328P Pin PD5 -> Digital Pin 5 (T1)
#define PD6_PIN 6  // ATmega328P Pin PD6 -> Digital Pin 6 (OC0A)
#define PD7_PIN 7  // ATmega328P Pin PD7 -> Digital Pin 7 (OC0B)
#define PB0_PIN 8  // ATmega328P Pin PB0 -> Digital Pin 8 (ICP1)
#define PB1_PIN 9  // ATmega328P Pin PB1 -> Digital Pin 9 (OC1A)
#define PB2_PIN 10 // ATmega328P Pin PB2 -> Digital Pin 10 (SS/OC1B)
#define PB3_PIN 11 // ATmega328P Pin PB3 -> Digital Pin 11 (MOSI/OC2A)
#define PB4_PIN 12 // ATmega328P Pin PB4 -> Digital Pin 12 (MISO)
#define PB5_PIN 13 // ATmega328P Pin PB5 -> Digital Pin 13 (SCK)

// Analog Pins
#define PC0_PIN 14 // ATmega328P Pin PC0 -> Analog Pin A0 (ADC0)
#define PC1_PIN 15 // ATmega328P Pin PC1 -> Analog Pin A1 (ADC1)
#define PC2_PIN 16 // ATmega328P Pin PC2 -> Analog Pin A2 (ADC2)
#define PC3_PIN 17 // ATmega328P Pin PC3 -> Analog Pin A3 (ADC3)
#define PC4_PIN 18 // ATmega328P Pin PC4 -> Analog Pin A4 (ADC4/SDA)
#define PC5_PIN 19 // ATmega328P Pin PC5 -> Analog Pin A5 (ADC5/SCL)

//
#define RX_PIN PD0_PIN
#define TX_PIN PD1_PIN

#endif // PIN_MAPPING_ATMEGA328P_H

/*
                 ATmega328P Pinout
     -----------------○-----------------------------
    | PC6 (RESET)  1      28 PC5 (ADC5/SCL/PCINT13) |
    | PD0 (RXD)    2      27 PC4 (ADC4/SDA/PCINT12) |
    | PD1 (TXD)    3      26 PC3 (ADC3/PCINT11)     |
    | PD2 (INT0)   4      25 PC2 (ADC2/PCINT10)     |
    | PD3 (INT1)   5      24 PC1 (ADC1/PCINT9)      |
    | PD4 (T0)     6      23 PC0 (ADC0/PCINT8)      |
    | VCC          7      22 GND                    |
    | GND          8      21 AREF                   |
    | PB6 (XTAL1)  9      20 AVCC                   |
    | PB7 (XTAL2) 10      19 PB5 (SCK/PCINT5)       |
    | PD5 (T1)    11      18 PB4 (MISO/PCINT4)      |
    | PD6 (AIN0)  12      17 PB3 (MOSI/OC2A/PCINT3) |
    | PD7 (AIN1)  13      16 PB2 (SS/OC1B/PCINT2)   |
    | PB0 (ICP1)  14      15 PB1 (OC1A/PCINT1)      |
     -----------------------------------------------
*/
