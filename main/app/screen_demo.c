/**
 * @file screen_demo.c
 **/

#include "screen_demo.h"
#include "module/convert/string.h"
#include "module/gui/eve_ui/button.h"
#include "module/util/assert.h"
#include "module/version/version.h"

//-----------------------------------------------------------------------------------------------------------------------------------------------------------
// Internal definitions
//-----------------------------------------------------------------------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------------------------------------------------------------------
// Internal structures and enums
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
typedef struct screen_demo_s
{
    /// Text object for the software version.
    text_t text_version;
    /// String for buffering the software version.
	char str_version[20];

    /// Text object for the text "Runtime:".
    text_t text_minutes_title;

    /// Text object for the runtime in minutes.
    text_t text_minutes;
    /// String for buffering the runtime in minutes.
	char str_minutes[15];

    /// Text object for the text "Counter:".
    text_t text_counter_title;

    /// Text object for the runtime in minutes.
    text_t text_counter;
    /// String for buffering the runtime in minutes.
	char str_counter[15];
    /// Current value of the counter. Is incremented on button press.
    uint16_t counter_value;

    /// Button object used to increase a counter and display a toast notification
    button_t button_increase_counter;

    /// Timestamp to update the screen every 60 seconds.
	uint32_t timestamp;
}screen_demo_t;

//-----------------------------------------------------------------------------------------------------------------------------------------------------------
// Prototypes
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
/**
 * Prepaint function is called directly before the screen is painted and used to modify the screen components.
 *
 * @param s				Pointer to the screen
 * @param option		Option of the screen.
 */
static void _prepaint(screen_t*, uint32_t);

/**
 * Handle function is called periodically and is used to update the shown information on the screen.
 *
 * @param s				Pointer to the screen
 * @param option		Option of the screen.
 **/
static void _handle(screen_t*, uint32_t);

/**
 * @brief Function that is called each time the button is pressed
 * 
 * @param btn Pointer to the button object that was pressed
 */
static void _button_pressed(button_t* btn);

//-----------------------------------------------------------------------------------------------------------------------------------------------------------
// Internal variables
//-----------------------------------------------------------------------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------------------------------------------------------------------
// External functions
//-----------------------------------------------------------------------------------------------------------------------------------------------------------

void screen_demo_init(screen_t* s, screen_device_t* dev)
{
    // Initialize the screen
	screen_init_object(s, color_get(GUI_CONFIG_DEFAULT_SCREEN_BACKCOLOR), _handle, _prepaint);
    screen_demo_t* scr = mcu_heap_calloc(1, sizeof(screen_demo_t));
    ASSERT_RET_NOT_NULL(scr, NO_ACTION, NO_RETURN);
    s->user = scr;

    uint16_t dev_w = screen_device_get_width(dev);
	uint16_t dev_h = screen_device_get_height(dev);

    text_init(&scr->text_version, dev_w - 10, 10, scr->str_version);
    text_set_horizontal_alignment(&scr->text_version, TEXT_H_ALIGNMENT_RIGHT);
    text_set_font(&scr->text_version, 18);
    screen_add_component(s, &scr->text_version.component);

    text_init(&scr->text_minutes_title, (dev_w / 2) - 10, (dev_h / 2) - 10, "Runtime:");
    text_set_horizontal_alignment(&scr->text_minutes_title, TEXT_H_ALIGNMENT_RIGHT);
    text_set_vertical_alignment(&scr->text_minutes_title, TEXT_V_ALIGNMENT_BOTTOM);
    screen_add_component(s, &scr->text_minutes_title.component);

    text_init(&scr->text_minutes, (dev_w / 2) + 10, (dev_h / 2) - 10, scr->str_minutes);
    text_set_horizontal_alignment(&scr->text_minutes, TEXT_H_ALIGNMENT_LEFT);
    text_set_vertical_alignment(&scr->text_minutes, TEXT_V_ALIGNMENT_BOTTOM);
    screen_add_component(s, &scr->text_minutes.component);

    text_init(&scr->text_counter_title, (dev_w / 2) - 10, (dev_h / 2) + 10, "Counter:");
    text_set_horizontal_alignment(&scr->text_counter_title, TEXT_H_ALIGNMENT_RIGHT);
    screen_add_component(s, &scr->text_counter_title.component);

    text_init(&scr->text_counter, (dev_w / 2) + 10, (dev_h / 2) + 10, scr->str_counter);
    text_set_horizontal_alignment(&scr->text_counter, TEXT_H_ALIGNMENT_LEFT);
    screen_add_component(s, &scr->text_counter.component);
    
    button_init(&scr->button_increase_counter, 3*dev_w / 8, dev_h - 50, dev_w / 4, 40, "Increase counter");
    button_set_action(&scr->button_increase_counter, _button_pressed);
    screen_add_component(s, &scr->button_increase_counter.component);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------
// Internal functions
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
static void _prepaint(screen_t* obj, uint32_t option)
{
	screen_demo_t* scr = obj->user;
	string_printf(scr->str_version, "Version: %s", version_get_string());
    strcpy(scr->str_minutes, "00:00 Minutes");
    strcpy(scr->str_counter, "0");
	scr->timestamp = system_get_tick_count();
}

static void _handle(screen_t* obj, uint32_t option)
{
	screen_demo_t* scr = obj->user;
	if( (system_get_tick_count() - scr->timestamp) >= 1000)
	{
		scr->timestamp = system_get_tick_count();
        uint32_t seconds = scr->timestamp / 1000;
        string_printf(scr->str_minutes, "%02d:%02d Minutes", seconds / 60, seconds % 60);
        screen_repaint(obj->screen_device);
	}
}

static void _button_pressed(button_t *btn)
{
    screen_t* s = screen_get_from_component((component_t*)btn);
    screen_demo_t* scr = s->user;
    
    scr->counter_value++;
    string_printf(scr->str_counter, "%d", scr->counter_value);

    screen_repaint(s->screen_device);
}
