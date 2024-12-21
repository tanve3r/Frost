/*******************************************************************************
 *  Copyright (c) 2024 Bangalore,
 *
 *  All rights reserved. This program and the accompanying materials
 *  are protected by international copyright laws.
 *  Please contact copyright holder for licensing information.
 *
 *
 *  @author Tanveer
 *
 *******************************************************************************
 *  PROJECT              FROST
 *  File Name          : rgb_led_strip
 *  Description        : Code for rgb_led_strip
 ******************************************************************************/


/******************************************************************************/
/* INCLUDES                                                                   */
/******************************************************************************/

#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "led_strip.h"
#include "rgb_led_strip.h"
#include "pin_config.h"



/******************************************************************************/
/* PRIVATE DEFINITIONS                                                        */
/******************************************************************************/
static led_strip_handle_t led_strip;

/******************************************************************************/
/* PRIVATE TYPE DEFINITIONS                                                   */
/******************************************************************************/
/**
 * @brief RGB configuration table structure
 */
typedef struct LedStrip_ConfigTable_Stuct
{
  LED_STRIP_COLOR  e_Colortype;
  uint32_t r;
  uint32_t g;
  uint32_t b;
}LedStrip_ConfigTable_Stuct;


static LedStrip_ConfigTable_Stuct st_ConfTab[LED_MAX_COLORS] =
{
 //   color type               red_comp  green_comp   blue_comp
   { LED_COLOR_OFF,               0,         0,            0    },
   { LED_COLOR_RED ,            16,         0,            0    },
   { LED_COLOR_GREEN,             0,       16,            0    },
   { LED_COLOR_BLUE,              0,         0,          16    },
   { LED_COLOR_YELLOW,          16,       16,            0    },
   { LED_COLOR_CYAN,              0,       16,          16    },
   { LED_COLOR_MAGENTA,         16,         0,          16    },
   { LED_COLOR_ORANGE,          16,       8,            0    },
   { LED_COLOR_YELLOW_GREEN,    8,       16,            0    },
   { LED_COLOR_CYAN_GREEN,        0,       16,          8    },
   { LED_COLOR_CYAN_BLUE,         0,       8,          16    },
   { LED_COLOR_BLUE_MAGENTA,    8,         0,          16    },
   { LED_COLOR_RED_MAGENTA,     16,       16,          8    },
   { LED_COLOR_WHITE,           16,       16,          8    },
};

/******************************************************************************/
/* PRIVATE FUNCTION DECLARATIONS AND PRIVATE MACRO FUNCTION DEFINITIONS       */
/******************************************************************************/

/******************************************************************************/
/* EXTERN VARIABLE DEFINTIONS                                                 */
/******************************************************************************/

/******************************************************************************/
/* PRIVATE DATA DEFINTIONS                                                    */
/******************************************************************************/
 
/******************************************************************************/
/* PUBLIC FUNCTION DEFINITIONS                                                */
/******************************************************************************/
/**
 * @brief rgb_led_strip initialization function
 *
 */
void rgb_ledStrip_Init (void)
{
    /* LED strip initialization with the GPIO and pixels number*/
    led_strip_config_t strip_config = {
        .strip_gpio_num = RGB_LED_STRIP_TX_GPIO,
        .max_leds = LED_MAX_NUM, // at least one LED on board
    };

    led_strip_rmt_config_t rmt_config = {
        .resolution_hz = 10 * 1000 * 1000, // 10MHz
        .flags.with_dma = false,
    };
    ESP_ERROR_CHECK(led_strip_new_rmt_device(&strip_config, &rmt_config, &led_strip));

    /* Set all LED off to clear all pixels */
    led_strip_clear(led_strip);

}

/**
 * @brief rgb_led_strip set
 *
 */
void rgb_SetLedStrip (LED_STRIP_COLOR e_Color)
{
	if(e_Color == LED_COLOR_OFF)
	{
      // clear strip
      led_strip_clear(led_strip);		
	}
         
    // Write RGB values to strip driver
	led_strip_set_pixel(led_strip, 0, 
	                     st_ConfTab[e_Color].r, st_ConfTab[e_Color].g, st_ConfTab[e_Color].b);
	led_strip_set_pixel(led_strip, 1, 
	                    st_ConfTab[e_Color].r, st_ConfTab[e_Color].g, st_ConfTab[e_Color].b); 
	led_strip_set_pixel(led_strip, 2,
	                    st_ConfTab[e_Color].r, st_ConfTab[e_Color].g, st_ConfTab[e_Color].b);
	 /* Refresh the strip to send data */
     led_strip_refresh(led_strip);
     
     vTaskDelay(100 / portTICK_PERIOD_MS);
}

/**
 * @brief this api is used to set individual color for each led
 *
 */
void rgb_setLed(LED_STRIP_COLOR Led1_Color, 
                LED_STRIP_COLOR Led2_Color, 
                LED_STRIP_COLOR Led3_Color)
{
    // Write RGB values to strip driver
	led_strip_set_pixel(led_strip, 0, 
	                     st_ConfTab[Led1_Color].r, st_ConfTab[Led1_Color].g, st_ConfTab[Led1_Color].b);
	led_strip_set_pixel(led_strip, 1, 
	                    st_ConfTab[Led2_Color].r, st_ConfTab[Led2_Color].g, st_ConfTab[Led2_Color].b); 
	led_strip_set_pixel(led_strip, 2,
	                    st_ConfTab[Led3_Color].r, st_ConfTab[Led3_Color].g, st_ConfTab[Led3_Color].b);
	 /* Refresh the strip to send data */
     led_strip_refresh(led_strip);
     
     vTaskDelay(100 / portTICK_PERIOD_MS);
}

/******************************************************************************/
/* PRIVATE FUNCTION DEFINITIONS                                               */
/******************************************************************************/

