#ifndef __EVENT_H__
#define __EVENT_H__

#include <stdint.h>

#include "config.h"

#ifndef EVENT_QUEUE_SIZE
#define EVENT_QUEUE_SIZE 8
#endif

typedef void (*event_handler_t)(uint8_t data);

typedef struct {
	event_handler_t handler;
	uint8_t data;
	uint8_t dummy;
} event_t;


/**
 * Initializes event queue.
 * Sets default sleep mode for event loop. The sleep mode constants are defined in <avr/sleep.h>
 * and depend on particular MCU. The most common is SLEEP_MODE_IDLE.
 *
 * @param sleep_mode - one of SLEEP_MODE_XXXX constants
 */
void event_init(uint8_t sleep_mode);

/**
 * Queues new event.
 *
 * @param handler - event handler function pointer
 * @param data - event data
 */
void event_queue(event_handler_t handler, uint8_t data);

/**
 * Pumps events and invokes appropriate event handlers.
 */
void event_pump();


#endif