#include <avr/sleep.h>
#include <avr/interrupt.h>

#include "event.h"

static event_t queue[EVENT_QUEUE_SIZE];
static volatile event_t *q, *f; 

#define MOVE(ptr) if (++ptr == queue + EVENT_QUEUE_SIZE) { ptr = queue; }

void event_init(uint8_t sleep_mode) {
	set_sleep_mode(sleep_mode);
	sleep_enable();
	q = f = queue;
}

void event_queue(event_handler_t handler, uint8_t data) {
	uint8_t sreg = SREG;
	cli();
	q->handler = handler;
	q->data = data;
		
	MOVE(q);
	SREG = sreg;
}

void event_pump() {
	while (1) {
		cli();
		while (q == f) {
			sei();
			sleep_cpu();
			cli();
		}
		sei();

		(*(f->handler))(f->data);
		MOVE(f);
	}
}
