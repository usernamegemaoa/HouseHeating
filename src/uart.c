#include <avr/io.h>
#include <avr/sfr_defs.h>

#include "uart.h"

void uart_init_(uint16_t baud_rate) {
	/* Set baud rate */
	UBRR0H = (uint8_t) (baud_rate >> 8);
	UBRR0L = (uint8_t) (baud_rate);
	
	/* Enable RX and TX */
	UCSR0B |= _BV(RXEN0) | _BV(TXEN0);
	
	/* Set frame format: 8-N-1 */
	UCSR0C |= _BV(UCSZ01) | _BV(UCSZ00);
}

void uart_tx(uint8_t data) {
	/* Wait for empty TX buffer */
	loop_until_bit_is_set(UCSR0A, UDRE0);
	
	/* Put data into buffer, sends the data */
	UDR0 = data;
}
