#include <avr/pgmspace.h>

#include "rfm73.h"
#include "spi.h"
 
/* RFM73 initialization sequence */
const uint8_t PROGMEM RFM73_init_data[] = {
	0x50, 0x53,                   // switch to bank 1
	0x20, 0x40, 0x4B, 0x01, 0xE2, // R0 = 0x404B01E2
	0x21, 0xC0, 0x4B, 0x00, 0x00, // R1 = 0xC04B0000
	0x22, 0xD0, 0xFC, 0x8C, 0x02, // R2 = 0xD0FC8C02
	0x23, 0x99, 0x00, 0x39, 0x41, // R3 = 0x99003941
	0x24, 0xD9, 0x9E, 0x86, 0x0B, // R4 = 0xD99E860B
	0x25, 0x24, 0x06, 0x7F, 0xA6, // R5 = 0x24067FA6
	0x2C, 0x00, 0x12, 0x73, 0x00, // Rc = 0x00731200
	0x2D, 0x36, 0xB4, 0x80, 0x00, // Rd = 0x0080B436
	0x2E, 0x41, 0x20, 0x08, 0x04, 0x81, 0x20, 0xCF, 0xF7, 0xFE, 0xFF, 0xFF, // Re - RAMP curve
//	0x2E, 0x41, 0x10, 0x04, 0x82, 0x20, 0x08, 0x08, 0xF2, 0x7D, 0xEF, 0xFF, // Re - RAMP curve
	0x50, 0x53                    // switch to bank 0
};


void rfm73_init(uint8_t aw, const uint8_t *tx, const uint8_t *rx0, const uint8_t *rx1) {
	rfm73_write_pgm(RFM73_init_data);

	rfm73_write_reg(RFM73_SETUP_AW, aw - 2);
	rfm73_write_buf(RFM73_W_REGISTER | RFM73_TX_ADDR,    tx,  aw);
	rfm73_write_buf(RFM73_W_REGISTER | RFM73_RX_ADDR_P0, rx0, aw);
	rfm73_write_buf(RFM73_W_REGISTER | RFM73_RX_ADDR_P1, rx1, aw);
}

uint8_t rfm73_cmd(uint8_t cmd) {
	return spi_rw(cmd);
}

uint8_t rfm73_cmd_val(uint8_t cmd, uint8_t val) {
	spi_rw(cmd);
	return spi_rw(val);
}

uint8_t rfm73_write_buf(uint8_t cmd, const uint8_t *buf, uint8_t len) {
	uint8_t i, status = spi_rw(cmd);
	for (i = 0; i < len; i++)
		spi_rw(buf[i]);
	return status;
}

uint8_t rfm73_read_buf(uint8_t cmd, uint8_t *buf, uint8_t len) {
	uint8_t i, status = spi_rw(cmd);
	for (i = 0; i < len; i++)
		buf[i] = spi_rw(0);
	return status;
}

void rfm73_mode(uint8_t mode) {
	uint8_t config = rfm73_read_reg(RFM73_CONFIG);

	// flush FIFO
	if (config & RFM73_PWR_UP) {
		if (config & RFM73_PRIM_RX)
			rfm73_cmd(RFM73_FLUSH_RX);
		else
			rfm73_cmd(RFM73_FLUSH_TX);
	}
	
	// clear interrupt flags
	rfm73_clear_irq();
	
	// set new mode
	rfm73_write_reg(RFM73_CONFIG, (config & ~RFM73_MODE_MASK) | mode);
}

void rfm73_write_pgm_(const uint8_t *ptr, uint8_t len) {
	uint8_t i;
	for (i = 0; i < len; i++)
		spi_rw(pgm_read_byte(ptr + i));
}
