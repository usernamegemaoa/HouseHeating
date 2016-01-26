

#ifndef __STATE_H__
#define __STATE_H__

#include <stdint.h>

#define TEMPLATE_COUNT 8
#define PROGRAM_COUNT 10

/*
This structure defines a rule applied to the template.

duration - defines how many cycles within period (T = 16) this rule must be run.
	If duration = 0 the rule is inactive.

temp_sensor_a - temperature sensor index for the left side of comparison.
temp_sensor_b - temperature sensor index for the right side of comparison.
	If temp_sensor_a = temp_sensor_b - no temperature sensors are used.

temperature - temperature value to be used in the right side of comparison (insted of temp_sensor_b)
*/
typedef struct {
	uint8_t duration      : 4; // template running duration
	uint8_t temp_sensor_a : 2; // left side temp sensor in rule: A < B
	uint8_t temp_sensor_b : 2; // right side temp sensor in rule: A < B (if temperature == 0)
	uint8_t temperature;       // right side fixed temperature value: A < T
} rule_t;


typedef struct {
	rule_t rule[TEMPLATE_COUNT];
} program_t;


typedef struct {
	// bit maps for templates
	uint8_t bits[TEMPLATE_COUNT];
	
	// programs
	program_t program[PROGRAM_COUNT];
	
	uint8_t cp; // current program
	uint8_t cl; // current duration
	uint8_t cb; // current bits
} state_t;

extern state_t state;

void state_init();
void state_save_bits(uint8_t t, uint8_t bits);
void state_save_rule(uint8_t p, uint8_t t, rule_t rule);

#endif
