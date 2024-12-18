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
#include "driver/rmt_tx.h"
#include "led_strip_encoder.h"
#include "rgb_led_strip.h"
#include "pin_config.h"

static const char *TAG = "Frost";

#define RMT_LED_STRIP_RESOLUTION_HZ 10000000 // 10MHz resolution, 1 tick = 0.1us (led strip needs a high resolution)

#define CHASE_SPEED_MS (10)


/******************************************************************************/
/* PRIVATE DEFINITIONS                                                        */
/******************************************************************************/
static uint8_t led_strip_pixels[LED_MAX_NUM * 3];

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
void led_strip_hsv2rgb(uint32_t h, uint32_t s, uint32_t v, uint32_t *r, uint32_t *g, uint32_t *b);
void rgb_led_strip_Process (void);

/******************************************************************************/
/* EXTERN VARIABLE DEFINTIONS                                                 */
/******************************************************************************/

/******************************************************************************/
/* PRIVATE DATA DEFINTIONS                                                    */
/******************************************************************************/
//led_strip_t *strip = NULL;
 rmt_channel_handle_t led_chan = NULL;
 rmt_encoder_handle_t led_encoder = NULL;
 rmt_transmit_config_t tx_config = {
	.loop_count = 0, // no transfer loop
    };
 
/******************************************************************************/
/* PUBLIC FUNCTION DEFINITIONS                                                */
/******************************************************************************/
/**
 * @brief rgb_led_strip initialization function
 *
 */
void rgb_ledStrip_Init (void)
{
  ESP_LOGI(TAG, "Create RMT TX channel");

  rmt_tx_channel_config_t tx_chan_config = {
      .clk_src = RMT_CLK_SRC_DEFAULT, // select source clock
      .gpio_num = RGB_LED_STRIP_TX_GPIO,
      .mem_block_symbols = 64, // increase the block size can make the LED less flickering
      .resolution_hz = RMT_LED_STRIP_RESOLUTION_HZ,
      .trans_queue_depth = 4, // set the number of transactions that can be pending in the background
  };
  ESP_ERROR_CHECK(rmt_new_tx_channel(&tx_chan_config, &led_chan));
  
  ESP_LOGI(TAG, "Install led strip encoder");
  led_strip_encoder_config_t encoder_config = {
      .resolution = RMT_LED_STRIP_RESOLUTION_HZ,
  };
  ESP_ERROR_CHECK(rmt_new_led_strip_encoder(&encoder_config, &led_encoder));

  ESP_LOGI(TAG, "Enable RMT TX channel");
  ESP_ERROR_CHECK(rmt_enable(led_chan));

}

/**
 * @brief rgb_led_strip set
 *
 */
void rgb_SetLedStrip (LED_STRIP_COLOR e_Color)
{
  // clear strip
  memset(led_strip_pixels, 0, sizeof(led_strip_pixels));
  // Flush RGB values to LEDs
  ESP_ERROR_CHECK(rmt_transmit(led_chan, led_encoder, led_strip_pixels, sizeof(led_strip_pixels), &tx_config));
  ESP_ERROR_CHECK(rmt_tx_wait_all_done(led_chan, portMAX_DELAY));
            
  // Write RGB values to strip driver
  for (int led_Index = 0; led_Index < LED_MAX_NUM; led_Index ++)
  {
	led_strip_pixels[led_Index * 3 + 0] = st_ConfTab[e_Color].g;
	led_strip_pixels[led_Index * 3 + 1] = st_ConfTab[e_Color].b;
	led_strip_pixels[led_Index * 3 + 2] = st_ConfTab[e_Color].r;
	  
	ESP_ERROR_CHECK(rmt_transmit(led_chan, led_encoder, led_strip_pixels, sizeof(led_strip_pixels), &tx_config));
    ESP_ERROR_CHECK(rmt_tx_wait_all_done(led_chan, portMAX_DELAY));

  }
}

/**
 * @brief this api is used to set individual color for each led
 *
 */
void rgb_setLed(LED_STRIP_COLOR Led1_Color, 
                LED_STRIP_COLOR Led2_Color, 
                LED_STRIP_COLOR Led3_Color)
{
  // clear strip
  memset(led_strip_pixels, 0, sizeof(led_strip_pixels));
  // Flush RGB values to LEDs
  ESP_ERROR_CHECK(rmt_transmit(led_chan, led_encoder, led_strip_pixels, sizeof(led_strip_pixels), &tx_config));
  ESP_ERROR_CHECK(rmt_tx_wait_all_done(led_chan, portMAX_DELAY));
  
  led_strip_pixels[LED_1 * 3 + 0] = st_ConfTab[Led1_Color].g;
  led_strip_pixels[LED_1 * 3 + 1] = st_ConfTab[Led1_Color].b;
  led_strip_pixels[LED_1 * 3 + 2] = st_ConfTab[Led1_Color].r;
    
  ESP_ERROR_CHECK(rmt_transmit(led_chan, led_encoder, led_strip_pixels, sizeof(led_strip_pixels), &tx_config));
  ESP_ERROR_CHECK(rmt_tx_wait_all_done(led_chan, portMAX_DELAY));
  
  led_strip_pixels[LED_2 * 3 + 0] = st_ConfTab[Led2_Color].g;
  led_strip_pixels[LED_2 * 3 + 1] = st_ConfTab[Led2_Color].b;
  led_strip_pixels[LED_2 * 3 + 2] = st_ConfTab[Led2_Color].r;
    
  ESP_ERROR_CHECK(rmt_transmit(led_chan, led_encoder, led_strip_pixels, sizeof(led_strip_pixels), &tx_config));
  ESP_ERROR_CHECK(rmt_tx_wait_all_done(led_chan, portMAX_DELAY));
  
  led_strip_pixels[LED_3 * 3 + 0] = st_ConfTab[Led3_Color].g;
  led_strip_pixels[LED_3 * 3 + 1] = st_ConfTab[Led3_Color].b;
  led_strip_pixels[LED_3 * 3 + 2] = st_ConfTab[Led3_Color].r;
    
  ESP_ERROR_CHECK(rmt_transmit(led_chan, led_encoder, led_strip_pixels, sizeof(led_strip_pixels), &tx_config));
  ESP_ERROR_CHECK(rmt_tx_wait_all_done(led_chan, portMAX_DELAY));
}

/******************************************************************************/
/* PRIVATE FUNCTION DEFINITIONS                                               */
/******************************************************************************/
/**
 * @brief rgb_led_strip process
 *
 */
void rgb_led_strip_Process (void)
{
  uint32_t red = 0;
  uint32_t green = 0;
  uint32_t blue = 0;
  uint16_t hue = 0;
  uint16_t start_rgb = 0;
  
  for (int i = 0; i < 3; i++) 
  {
	for (int j = i; j < LED_MAX_NUM; j += 3) {
		// Build RGB pixels
		hue = j * 360 / LED_MAX_NUM + start_rgb;
		led_strip_hsv2rgb(hue, 100, 100, &red, &green, &blue);
		led_strip_pixels[j * 3 + 0] = green;
		led_strip_pixels[j * 3 + 1] = blue;
		led_strip_pixels[j * 3 + 2] = red;
	}
	// Flush RGB values to LEDs
	ESP_ERROR_CHECK(rmt_transmit(led_chan, led_encoder, led_strip_pixels, sizeof(led_strip_pixels), &tx_config));
	ESP_ERROR_CHECK(rmt_tx_wait_all_done(led_chan, portMAX_DELAY));
	vTaskDelay(pdMS_TO_TICKS(CHASE_SPEED_MS));
	memset(led_strip_pixels, 0, sizeof(led_strip_pixels));
	ESP_ERROR_CHECK(rmt_transmit(led_chan, led_encoder, led_strip_pixels, sizeof(led_strip_pixels), &tx_config));
	ESP_ERROR_CHECK(rmt_tx_wait_all_done(led_chan, portMAX_DELAY));
	vTaskDelay(pdMS_TO_TICKS(CHASE_SPEED_MS));
  }
  start_rgb += 60;
}


/******************************************************************************/
/* PRIVATE FUNCTION DEFINITIONS                                               */
/******************************************************************************/
/**
 * @brief Simple helper function, converting HSV color space to RGB color space
 *
 * Wiki: https://en.wikipedia.org/wiki/HSL_and_HSV
 *
 */
void led_strip_hsv2rgb(uint32_t h, uint32_t s, uint32_t v, uint32_t *r, uint32_t *g, uint32_t *b)
{
    h %= 360; // h -> [0,360]
    uint32_t rgb_max = v * 2.55f;
    uint32_t rgb_min = rgb_max * (100 - s) / 100.0f;

    uint32_t i = h / 60;
    uint32_t diff = h % 60;

    // RGB adjustment amount by hue
    uint32_t rgb_adj = (rgb_max - rgb_min) * diff / 60;

    switch (i) {
    case 0:
        *r = rgb_max;
        *g = rgb_min + rgb_adj;
        *b = rgb_min;
        break;
    case 1:
        *r = rgb_max - rgb_adj;
        *g = rgb_max;
        *b = rgb_min;
        break;
    case 2:
        *r = rgb_min;
        *g = rgb_max;
        *b = rgb_min + rgb_adj;
        break;
    case 3:
        *r = rgb_min;
        *g = rgb_max - rgb_adj;
        *b = rgb_max;
        break;
    case 4:
        *r = rgb_min + rgb_adj;
        *g = rgb_min;
        *b = rgb_max;
        break;
    default:
        *r = rgb_max;
        *g = rgb_min;
        *b = rgb_max - rgb_adj;
        break;
    }
}
