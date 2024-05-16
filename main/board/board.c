/**
 * 	@file 	board.c
 * 	@copyright Urheberrecht 2018-2023 ESoPe GmbH, Alle Rechte vorbehalten
 *
 *	@brief 	Implements the function board_init from the board.h and initializes the variables declared in the board_specific.h
 **/

#include <string.h>
#include "board.h"
#include "mcu/sys.h"
#include "module/console/dbg/debug_console.h"

//-----------------------------------------------------------------------------------------------------------------------------------------------------------
// Internal definitions
//-----------------------------------------------------------------------------------------------------------------------------------------------------------

/// Macro for setting the pin as an external I/O of the expander instead of the internal.
#define EXPANDER_PIN(i)		(GPIO_EXTERNAL + (i))

#define EVE_SPI_MOSI		GPIO16

#define EVE_SPI_MISO		GPIO17

#define EVE_SPI_SCK			GPIO18

#define EVE_SPI_CS			GPIO15

#define EVE_SPI_CS2			GPIO7

#define EVE_SPI_CS3			GPIO6

#define EVE_IO_PD			GPIO4

#define EVE_IO_INT			GPIO5
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
// Internal structures and enums
//-----------------------------------------------------------------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------------------------------------------------------------
// Internal variables
//-----------------------------------------------------------------------------------------------------------------------------------------------------------

// GPIO_EXTERNAL

#if MODULE_ENABLE_COMM
/// Interface for debug prints and console.
static comm_t		_comm_debug;
#endif

//-----------------------------------------------------------------------------------------------------------------------------------------------------------
// External variables -> Contains the variables stated in the board_specific.h.
//-----------------------------------------------------------------------------------------------------------------------------------------------------------

eve_hw_interface_t board_eve;
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
// Function
//-----------------------------------------------------------------------------------------------------------------------------------------------------------

void board_init(void)
{
	// Initialize the mcu with an external clock on the maximum speed.
	mcu_init_max_internal();

#if MODULE_ENABLE_COMM
	// Create uarts and assign it to a comm handler.
	_comm_debug.device_handler = mcu_uart_init(0, GPIO1, GPIO3);
	mcu_uart_create_comm_handler(_comm_debug.device_handler, &_comm_debug);

	board_eve.spi = mcu_spi_init(2, EVE_SPI_MOSI, EVE_SPI_MISO, EVE_SPI_SCK, EVE_SPI_CS);
	board_eve.io_pd = EVE_IO_PD;
	mcu_io_set_pullup(EVE_IO_INT, true);
	board_eve.io_int = mcu_io_interrupt_init(0, EVE_IO_INT);
	board_eve.io_sound_enable.pin = PIN_NONE;
	board_eve.io_h_pwr.pin = PIN_NONE;

	// Set UART for debug
	mcu_uart_set_param(_comm_debug.device_handler, 500000, 8, 'N', 1);
	dbg_set_comm(&_comm_debug);
#endif

	// Enable Interrupts
	mcu_enable_interrupt();
}
