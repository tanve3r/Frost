/*******************************************************************************
 *  Copyright (c) 2025 Bangalore,
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
#include "esp_check.h"


/******************************************************************************/
/* PRIVATE DEFINITIONS                                                        */
/******************************************************************************/
static led_strip_handle_t led_strip;
const static char *TAG = "led";
/******************************************************************************/
/* PRIVATE TYPE DEFINITIONS                                                   */
/******************************************************************************/
/**
 * @brief RGB configuration table structure
 */
typedef struct LedStrip_ConfigTable_Stuct
{
  LED_STRIP_COLOR  e_Colortype;
  uint8_t r;
  uint8_t g;
  uint8_t b;
}LedStrip_ConfigTable_Stuct;


static LedStrip_ConfigTable_Stuct st_ConfTab[LED_MAX_COLORS] =
{
 //   color type               red_comp  green_comp   blue_comp
   { LED_COLOR_OFF,               0,         0,            0    },
   { LED_COLOR_RED ,            255,         0,            0    },
   { LED_COLOR_GREEN,             0,       255,            0    },
   { LED_COLOR_BLUE,              0,         0,          255    },
   { LED_COLOR_YELLOW,          255,       255,            0    },
   { LED_COLOR_CYAN,              0,       255,          255    },
   { LED_COLOR_MAGENTA,         255,         0,          255    },
   { LED_COLOR_ORANGE,          255,       125,            0    },
   { LED_COLOR_YELLOW_GREEN,    125,       255,            0    },
   { LED_COLOR_CYAN_GREEN,        0,       255,          125    },
   { LED_COLOR_CYAN_BLUE,         0,       125,          255    },
   { LED_COLOR_BLUE_MAGENTA,    125,         0,          255    },
   { LED_COLOR_RED_MAGENTA,     255,       255,          125    },
   { LED_COLOR_WHITE,           255,       255,          125    },
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
    // LED strip general initialization, according to your led board design
    led_strip_config_t strip_config = {
        .strip_gpio_num = RGB_LED_STRIP_TX_GPIO, // The GPIO that connected to the LED strip's data line
        .max_leds = LED_MAX_NUM,      // The number of LEDs in the strip,
        .led_model = LED_MODEL_WS2812,        // LED strip model
        // set the color order of the strip: GRB
        .color_component_format = {
            .format = {
                .r_pos = 1, // red is the second byte in the color data
                .g_pos = 0, // green is the first byte in the color data
                .b_pos = 2, // blue is the third byte in the color data
                .num_components = 3, // total 3 color components
            },
        },
        .flags = {
            .invert_out = false, // don't invert the output signal
        }
    };

    // LED strip backend configuration: SPI
    led_strip_spi_config_t spi_config = {
        .clk_src = SPI_CLK_SRC_DEFAULT, // different clock source can lead to different power consumption
        .spi_bus = SPI2_HOST,           // SPI bus ID
        .flags = {
            .with_dma = true, // Using DMA can improve performance and help drive more LEDs
        }
    };

    ESP_ERROR_CHECK(led_strip_new_spi_device(&strip_config, &spi_config, &led_strip));
    ESP_LOGI(TAG, "Created LED strip object with SPI backend");
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
     
}

/**
 * @brief this api is used to set individual color for each led
 *
 */
void rgb_setLed( LED_STRIP_NUM LedNum,LED_STRIP_COLOR Led_Color)
{
	esp_err_t error = ESP_OK;
    // Write RGB values to strip driver
	error = led_strip_set_pixel(led_strip, LedNum, 
	                     st_ConfTab[Led_Color].r, st_ConfTab[Led_Color].g, st_ConfTab[Led_Color].b);
	                     
	if(error != ESP_OK)
	ESP_LOGI(TAG, "err:%d \n", error);                     

	 /* Refresh the strip to send data */
   error =  led_strip_refresh(led_strip);
     
     if(error != ESP_OK)
	ESP_LOGI(TAG, "err:%d \n", error);        
     
}

/******************************************************************************/
/* PRIVATE FUNCTION DEFINITIONS                                               */
/******************************************************************************/

