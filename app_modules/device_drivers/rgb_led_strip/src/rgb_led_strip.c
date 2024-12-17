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

#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/rmt.h"
#include "led_strip.h"
#include "rgb_led_strip.h"
#include "pin_config.h"

static const char *TAG = "Stomiyo";

#define RMT_TX_CHANNEL RMT_CHANNEL_0

#define CHASE_SPEED_MS (10)

#define CONFIG_STRIP_LED_NUMBER 14

/******************************************************************************/
/* PRIVATE DEFINITIONS                                                        */
/******************************************************************************/
uint32_t red = 0;
uint32_t green = 0;
uint32_t blue = 0;
uint16_t hue = 0;
uint16_t start_rgb = 0;

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
led_strip_t *strip = NULL;

/******************************************************************************/
/* PUBLIC FUNCTION DEFINITIONS                                                */
/******************************************************************************/
/**
 * @brief rgb_led_strip initialization function
 *
 */
void rgb_ledStrip_Init (void)
{
  rmt_config_t config = RMT_DEFAULT_CONFIG_TX(RGB_LED_STRIP_TX_GPIO, RMT_TX_CHANNEL);
  // set counter clock to 40MHz
  config.clk_div = 2;

  ESP_ERROR_CHECK(rmt_config(&config));
  ESP_ERROR_CHECK(rmt_driver_install(config.channel, 0, 0));

  // install ws2812 driver
  led_strip_config_t strip_config = LED_STRIP_DEFAULT_CONFIG(CONFIG_STRIP_LED_NUMBER, (led_strip_dev_t)config.channel);
  strip = led_strip_new_rmt_ws2812(&strip_config);
  if (!strip)
  {
      ESP_LOGE(TAG, "install WS2812 driver failed");
  }
  // Clear LED strip (turn off all LEDs)
  ESP_ERROR_CHECK(strip->clear(strip, 100));

}

/**
 * @brief rgb_led_strip set
 *
 */
void rgb_SetLedStrip (LED_STRIP_COLOR e_Color)
{
  if(e_Color == LED_COLOR_OFF)
  {
    // Clear LED strip (turn off all LEDs)
    ESP_ERROR_CHECK(strip->clear(strip, 100));
  }
  else
  {
    strip->clear(strip, 50);
    // Write RGB values to strip driver
    for (int led_Index = 0; led_Index < CONFIG_STRIP_LED_NUMBER; led_Index ++)
    {
      ESP_ERROR_CHECK(strip->set_pixel(strip, led_Index, st_ConfTab[e_Color].r, st_ConfTab[e_Color].g, st_ConfTab[e_Color].b));
    }
    // Flush RGB values to LEDs
    ESP_ERROR_CHECK(strip->refresh(strip, 100));
  }
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
  for (int i = 0; i < 3; i++) {
      for (int j = i; j < CONFIG_STRIP_LED_NUMBER; j += 3) {
          // Build RGB values
          hue = j * 360 / CONFIG_STRIP_LED_NUMBER + start_rgb;
          led_strip_hsv2rgb(hue, 100, 100, &red, &green, &blue);
          // Write RGB values to strip driver
          ESP_ERROR_CHECK(strip->set_pixel(strip, j, red, green, blue));
      }
      // Flush RGB values to LEDs
      ESP_ERROR_CHECK(strip->refresh(strip, 100));
      vTaskDelay(pdMS_TO_TICKS(CHASE_SPEED_MS));
      strip->clear(strip, 50);
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
