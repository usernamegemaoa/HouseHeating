
#include "state.h"

state_t state;

void state_init() {
	// TODO: read EEPROM
	state.cp = 0xFF;
}

void state_save_bits(uint8_t t, uint8_t bits) {
	// TODO: write EEPROM
	state.bits[t] = bits;
}

void state_save_rule(uint8_t p, uint8_t t, rule_t rule) {
	// TODO: write EEPROM
	state.program[p].rule[t] = rule;
}
