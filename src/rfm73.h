#ifndef __RFM73_H__
#define __RFM73_H__

#include <stdint.h>


/* RFM73 commands */
#define RFM73_R_REGISTER             0x00  // Read register command (combined with register number)
#define RFM73_W_REGISTER             0x20  // Write register command (combined with register number)
#define RFM73_R_RX_PLOAD             0x61  // Read RX payload
#define RFM73_W_TX_PLOAD             0xA0  // Write TX payload
#define RFM73_FLUSH_TX               0xE1  // Flush TX FIFO
#define RFM73_FLUSH_RX               0xE2  // Flush RX FIFO
#define RFM73_REUSE_TX_PL            0xE3  // Reuse TX payload
#define RFM73_ACTIVATE               0x50  // Activate command
#define RFM73_R_RX_PL_WID            0x60  // Read RX-payload width
#define RFM73_W_ACK_PAYLOAD          0xA8  // Write payload to be transmitted with ACK packet
#define RFM73_W_TX_PAYLOAD_NOACK     0xB0  // Disable AUTOACK on the specific packet
#define RFM73_NOP                    0xFF  // No Operation (might be used to read status register)

/* RFM73 registers */
#define RFM73_CONFIG                 0x00  // 'Config' register address
#define RFM73_EN_AA                  0x01  // 'Enable Auto Acknowledgment' register address
#define RFM73_EN_RXADDR              0x02  // 'Enabled RX addresses' register address
#define RFM73_SETUP_AW               0x03  // 'Setup address width' register address
#define RFM73_SETUP_RETR             0x04  // 'Setup Auto. Retrans' register address
#define RFM73_RF_CH                  0x05  // 'RF channel' register address
#define RFM73_RF_SETUP               0x06  // 'RF setup' register address
#define RFM73_STATUS                 0x07  // 'Status' register address
#define RFM73_OBSERVE_TX             0x08  // 'Observe TX' register address
#define RFM73_CD                     0x09  // 'Carrier Detect' register address
#define RFM73_RX_ADDR_P0             0x0A  // 'RX address pipe0' register address
#define RFM73_RX_ADDR_P1             0x0B  // 'RX address pipe1' register address
#define RFM73_RX_ADDR_P2             0x0C  // 'RX address pipe2' register address
#define RFM73_RX_ADDR_P3             0x0D  // 'RX address pipe3' register address
#define RFM73_RX_ADDR_P4             0x0E  // 'RX address pipe4' register address
#define RFM73_RX_ADDR_P5             0x0F  // 'RX address pipe5' register address
#define RFM73_TX_ADDR                0x10  // 'TX address' register address
#define RFM73_RX_PW_P0               0x11  // 'RX payload width, pipe0' register address
#define RFM73_RX_PW_P1               0x12  // 'RX payload width, pipe1' register address
#define RFM73_RX_PW_P2               0x13  // 'RX payload width, pipe2' register address
#define RFM73_RX_PW_P3               0x14  // 'RX payload width, pipe3' register address
#define RFM73_RX_PW_P4               0x15  // 'RX payload width, pipe4' register address
#define RFM73_RX_PW_P5               0x16  // 'RX payload width, pipe5' register address
#define RFM73_FIFO_STATUS            0x17  // 'FIFO Status Register' register address
#define RFM73_DYNPD                  0x1C  // 'Enable dynamic payload length' register address
#define RFM73_FEATURE                0x1D  // 'Feature' register address

/* RFM73_CONFIG register bit masks */
#define RFM73_MASK_RX_DR            0x40
#define RFM73_MASK_TX_DS            0x20
#define RFM73_MASK_MAX_RT           0x10
#define RFM73_EN_CRC                0x08
#define RFM73_CRC0                  0x04
#define RFM73_PWR_UP                0x02
#define RFM73_PRIM_RX               0x01

/* RFM73_STATUS register bit masks */
#define RFM73_RBANK                 0x80
#define RFM73_RX_DR                 0x40
#define RFM73_TX_DS                 0x20
#define RFM73_MAX_RT                0x10
#define RFM73_RX_P_NO               0x0E
#define RFM73_TX_FULL               0x01

/* RFM73 mode */
#define RFM73_MODE_MASK             0x03
#define RFM73_MODE_OFF              0x00
#define RFM73_MODE_TX               0x02
#define RFM73_MODE_RX               0x03

#define RFM73_PAYLOAD_SIZE            32

/**
 * Initializes RFM73 module.
 * Call this function after at least 200ms after power on.
 *
 * @param aw - address width: 3..5
 * @param tx - TX address
 * @param rx0 - pipe 0 RX address
 * @param rx1 - pipe 1 RX address
 */
void rfm73_init(uint8_t aw, const uint8_t *tx, const uint8_t *rx0, const uint8_t *rx1);

/**
 * Executes command w/o arguments.
 *
 * @param cmd - command
 * @return status
 */
uint8_t rfm73_cmd(uint8_t cmd);

/**
 * Executes command with one-byte data.
 *
 * @param cmd - command
 * @param val - value
 * @return command value
 */
uint8_t rfm73_cmd_val(uint8_t cmd, uint8_t val);

/**
 * Executes command with data to be sent from the buffer.
 *
 * @param cmd - command
 * @param buf - buffer address
 * @param len - buffer length
 * @return status
 */
uint8_t rfm73_write_buf(uint8_t cmd, const uint8_t *buf, uint8_t len);

/**
 * Executes command with data to be read into the buffer.
 *
 * @param cmd - command
 * @param buf - buffer address
 * @param len - buffer length
 * @return status
 */
uint8_t rfm73_read_buf(uint8_t cmd, uint8_t *buf, uint8_t len);


/**
 * Sets the RFM73 module mode.
 *
 * @param mode - one of RFM73_MODE_xxx constants: OFF, TX, RX
 */
void rfm73_mode(uint8_t mode);

/**
 * Writes data to RFM73 module from program memory.
 *
 * @param ptr - program memory address
 * @param len - data length
 */
void rfm73_write_pgm_(const uint8_t *ptr, uint8_t len);


/**
 * Gets current RFM73 status.
 *
 * @return status register value
 */
#define rfm73_status() \
		rfm73_cmd(RFM73_NOP)

/**
 * Sets RF channel: F = 2400 + channel (in MHz)
 *
 * @param channel - value from 0 to 83
 */
#define rfm73_set_channel(channel) \
		rfm73_cmd_val(RFM73_W_REGISTER | RFM73_RF_CH, channel)

/**
 * Clears IRQ flags in the status register.
 */
#define rfm73_clear_irq() \
		rfm73_write_reg(RFM73_STATUS, rfm73_read_reg(RFM73_STATUS))

/**
 * Returns RX pipe number for reading RX payload.
 */
#define rfm73_rx_pipe() \
		((rfm73_status() >> 1) & 0x07)

/**
 * Reads RX payload into the buffer.
 *
 * @param buf - buffer address
 * @param len - buffer length/payload width
 * @return status
 */
#define rfm73_rx_data(buf, len) \
		rfm73_read_buf(RFM73_R_RX_PLOAD, buf, len)

/**
 * Writes TX payload from the buffer.
 *
 * @param buf - buffer address
 * @param len - buffer length/payload width
 * @return status
 */
#define rfm73_tx_data(buf, len) \
		rfm73_write_buf(RFM73_W_TX_PLOAD, buf, len)

/**
 * Reads register value.
 *
 * @param reg - register address
 * @return register value
 */		
#define rfm73_read_reg(reg) \
		rfm73_cmd_val(RFM73_R_REGISTER | reg, 0)

/**
 * Reads register value.
 *
 * @param reg - register address
 * @param val - value
 * @return register value
 */		
#define rfm73_write_reg(reg, val) \
		rfm73_cmd_val(RFM73_W_REGISTER | reg, val)

/**
 * Writes program memory block to the RFM73 module.
 *
 * @param data - constant byte array
 */
#define rfm73_write_pgm(data) \
 		rfm73_write_pgm_(data, sizeof(data))

#endif
