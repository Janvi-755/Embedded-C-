 * Aim:
 * Toggle LED2 and LED8 depending on Interrupt Switch state
 */

//---------------------------------- HEADER FILES -----------------------------------------------------
#include "firebird_simulation.h"
#include <util/delay.h>
#include <stdbool.h>

//---------------------------------- FUNCTIONS ----------------------------------------------------------

/**
 * Configure LED2, LED6, LED8 as output
 * Initially turn ON LED2
 */
void bar_graph_led_pins_config(void)
{
	// Make LED2, LED6, LED8 pins output
	bar_graph_led_ddr_reg |= (1 << bar_graph_led_2_pin) |
							 (1 << bar_graph_led_6_pin) |
							 (1 << bar_graph_led_8_pin);

	// Turn ON only LED2 initially
	bar_graph_led_port_reg |= (1 << bar_graph_led_2_pin);
}


/**
 * Configure interrupt switch pin as input with pull-up
 */
void interrupt_sw_pin_config(void)
{
	// Set PE7 as input
	interrupt_sw_ddr_reg &= ~(1 << interrupt_sw_pin);

	// Enable internal pull-up
	interrupt_sw_port_reg |= (1 << interrupt_sw_pin);
}


/**
 * Check if switch is pressed
 */
bool interrupt_switch_pressed(void)
{
	// Switch pressed → logic LOW
	if (!(PINE & (1 << interrupt_sw_pin)))
	{
		return true;
	}
	else
	{
		return false;
	}
}


/**
 * Turn ON selected LED
 */
void turn_on_bar_graph_led(unsigned char led_pin)
{
	bar_graph_led_port_reg |= (1 << led_pin);
}


/**
 * Turn OFF selected LED
 */
void turn_off_bar_graph_led(unsigned char led_pin)
{
	bar_graph_led_port_reg &= ~(1 << led_pin);
}


//---------------------------------- MAIN ----------------------------------------------------------------

int main(void)
{
	bar_graph_led_pins_config();
	interrupt_sw_pin_config();

	turn_on_bar_graph_led(bar_graph_led_6_pin);

	while (1)
	{
		if ( interrupt_switch_pressed() )
		{
			turn_off_bar_graph_led(bar_graph_led_2_pin);
			turn_on_bar_graph_led(bar_graph_led_8_pin);

			_delay_ms(50);
		}
		else
		{
			turn_on_bar_graph_led(bar_graph_led_2_pin);
			turn_off_bar_graph_led(bar_graph_led_8_pin);
		}
	}
}