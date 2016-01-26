#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/sleep.h>
#include <util/delay.h>

#include "config.h"
#include "uart.h"
#include "lcd.h"
#include "event.h"
#include "ui.h"
#include "spi.h"
#include "state.h"

int main(void) {
	CLKPR = (1 << CLKPCE);                                    // Enable prescaler change
	CLKPR = 0;                                                // Write new prescaler value - 1: Fio = 8MHz

/*	PORTB = DDRB = 0;                                         // All pins in Hi-Z state
	GIMSK = (1 << PCIE);                                      // Enable pin change interrupts

	TCCR0A = 0;                                               // Normal operation
	TCCR0B = (1 << CS00);                                     // Internal clock source/No prescaling
	TIMSK0 = (1 << TOIE0);                                    // Enable timer interrupts
	*/

	
	_delay_ms(200);
	
	spi_init(SPI_RATE_4);
	uart_init(1200);
//	rfm73_init()
	ui_init();
	state_init();
	event_init(SLEEP_MODE_IDLE);

	event_pump();
    return 0;
}
