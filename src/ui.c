#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sfr_defs.h>

#include "config.h"
#include "ui.h"
#include "lcd.h"
#include "event.h"
#include "state.h"

static void ui_draw_bits(uint8_t bits);

uint8_t ui_state = 0;
uint8_t ui_program;


void ui_init() {
	lcd_init(LCD_DISP_ON);
	lcd_clrscr();
	lcd_home();
	
	// pull-up button pins
	BUTTON_PORT |= _BV(BUTTON_1_PIN) | _BV(BUTTON_2_PIN) | _BV(BUTTON_3_PIN);
	
	// enable pin change interrupts for buttons
	PCICR |= _BV(BUTTON_PCIE);
	BUTTON_PCMSK |= _BV(BUTTON_1_PIN) | _BV(BUTTON_2_PIN) | _BV(BUTTON_3_PIN);
}

void ui_update() {
	if (ui_state == 0) {
		lcd_gotoxy(0, 0);
		lcd_putc('P');
		
		if (state.cp < PROGRAM_COUNT)
			lcd_putc('0' + state.cp);
		else
			lcd_putc('-');
		
		lcd_gotoxy(3, 0);
		lcd_putc('L');
		lcd_putc('0' + state.cl / 10);
		lcd_putc('0' + state.cl % 10);
		
		ui_draw_bits(state.cb);
	}
	else if (ui_state == 1) {
		lcd_gotoxy(0, 0);
		lcd_putc('P');
		
		if (state.cp < PROGRAM_COUNT)
			lcd_putc('0' + state.cp);
		else
			lcd_putc('-');
		
		lcd_gotoxy(3, 0);
		lcd_putc('L');
		lcd_putc('0' + state.cl / 10);
		lcd_putc('0' + state.cl % 10);
		
		ui_draw_bits(state.cb);
		
	}
}

void ui_draw_bits(uint8_t bits) {
	uint8_t dg;
	
	lcd_gotoxy(0, 1);
	for (dg = '1'; dg <= '8'; dg++) {
		if (bits & 1)
			lcd_putc(dg);
		else
			lcd_putc(' ');
		bits >>= 1;
	}
}

void ui_button(uint8_t data) {
	
}

ISR(BUTTON_PCINT_vect)
{
	event_queue(ui_button, 0);
	reti();
}

