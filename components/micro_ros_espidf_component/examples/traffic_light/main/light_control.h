#ifndef LIGHT_CONTROL_H
#define LIGHT_CONTROL_H

#include <stdbool.h>
#include <stddef.h>

// Function declarations
void led_control(int led, bool state);
void delay_seconds(float seconds);
void initialize_traffic_lights(const int *traffic_lights, size_t count);
void run_traffic_light_sequence(const int *traffic_lights, const float *timeouts, size_t count);

// Global variables
extern const int traffic_lights[];
extern float traffic_light_timeout[];
extern const size_t light_count;

#endif // LIGHT_CONTROL_H
