/**
 * 	@file 	board.h
 * 	@copyright Urheberrecht 2018-2023 ESoPe GmbH, Alle Rechte vorbehalten
 *
 * 	@author Tim Koczwara
 *
 *  @brief	Offers one function, that initializes all periphery that is assigned to the board inside board.c and board_specific.h.
 *
 *  @version  	1.02 (16.02.2013)
 *		- Converted comments in english.
 *  @version  	1.01 (03.04.2011)
 *		- board.h splitted to board_specific.h and board.h.
 *		- board.h contains only the board_init function.
 *  @version  	1.00
 *  	- Initial release
 *
 ******************************************************************************/
#ifndef BOARD_HEADER_FIRST_INCLUDE_GUARD
#define BOARD_HEADER_FIRST_INCLUDE_GUARD


#include "module_public.h"
#include "module_include_public.h"
#include "module/gui/eve/eve.h"

extern eve_hw_interface_t board_eve;

/**
 * @brief 		Initializes the mcu and all periphery assigned to the used board. Is automatically called in sys.c at first step of the main.
 */
void board_init(void);


#endif
