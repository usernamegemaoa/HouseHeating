#ifndef __SPI_H__
#define __SPI_H__

#include <stdint.h>

#define SPI_RATE_4   0
#define SPI_RATE_16  1
#define SPI_RATE_64  2
#define SPI_RATE_128 3

void spi_init(uint8_t rate);
uint8_t spi_rw(uint8_t data);

#endif // __SPI_H__
