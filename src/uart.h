
#include <stdint.h>

/**
 * Initializes UART for specified baud: 1200, 9600, etc.
 */
#define uart_init(boud) \
		uart_init_(F_CPU / (16 * boud) - 1)

/**
 * Initializes UART for specified baud rate.
 *
 * @param baud_rate - use UART_BOUD_RATE() to compute proper value
 */
void uart_init_(uint16_t baud_rate);

/**
 * Sends byte over UART.
 *
 * @param data - data to send
 */
void uart_tx(uint8_t data);
