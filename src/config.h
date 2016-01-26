/*
 * pins.h - pin layout definitions
 *
 */

#ifndef __PINS_H__
#define __PINS_H__

#define LCD_CONTROLLER_KS0073 0

#define LCD_PORT PORTD
#define LCD_DATA0_PIN 4
#define LCD_DATA1_PIN 5
#define LCD_DATA2_PIN 6
#define LCD_DATA3_PIN 7

#define LCD_RS_PORT PORTB
#define LCD_RS_PIN 7

#define LCD_RW_PORT PORTB
#define LCD_RW_PIN 6

#define LCD_E_PORT PORTB
#define LCD_E_PIN 0

#define TERM_PORT PORTB
#define TERM_PIN 2

#define BUTTON_PORT PORTC
#define BUTTON_1_PIN 2
#define BUTTON_2_PIN 1
#define BUTTON_3_PIN 0
#define BUTTON_PCMSK PCMSK1
#define BUTTON_PCIE 1
#define BUTTON_PCINT_vect PCINT1_vect

#define BUS_PORT PORTC
#define BUS_OE 3
#define BUS_ST_CP 4
#define BUS_MR 5

#define RFM_PORT PORTB
#define RFM_CSN 1

#define SPI_DDR  DDRB
#define SPI_SCK  DDB5
#define SPI_MISO DDB4
#define SPI_MOSI DDB3

#endif

