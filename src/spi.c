#include <avr/io.h>

#include "config.h"
#include "spi.h"

void spi_init(uint8_t rate) {
	/* Set MOSI and SCK as output */
	SPI_DDR |=  (1 << SPI_SCK) | (1 << SPI_MOSI);
	
	/* Enable SPI master and set SPI clock rate */
	SPCR = (1 << SPE) | (1 << MSTR) | (1 << rate); 
}

uint8_t spi_rw(uint8_t data) {
	/* Start transmission */
	SPDR = data;

	/* Wait for transmission complete */
	while (!(SPSR & (1 << SPIF)))
		;

	return SPDR;
}
