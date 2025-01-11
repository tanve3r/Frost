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
 *  File Name          : flash_nvs
 *  Description        : Code for flash
 ******************************************************************************/


/******************************************************************************/
/* INCLUDES                                                                   */
/******************************************************************************/

#include <stdio.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "flash_nvs.h"

/******************************************************************************/
/* PRIVATE DEFINITIONS                                                        */
/******************************************************************************/
#define DEFAULT_DRINKTIMER_VALUE 60000  // 60 seconds
#define DEFAULT_PLACETIMER_VALUE 50000  // 50 seconds
#define DEFAULT_CLEANTIMER_VALUE 50000  // 50 seconds

//#define PrintEN

/******************************************************************************/
/* PRIVATE TYPE DEFINITIONS                                                   */
/******************************************************************************/

/******************************************************************************/
/* PRIVATE FUNCTION DECLARATIONS AND PRIVATE MACRO FUNCTION DEFINITIONS       */
/******************************************************************************/

/******************************************************************************/
/* EXTERN VARIABLE DEFINTIONS                                                 */
/******************************************************************************/

/******************************************************************************/
/* PRIVATE DATA DEFINTIONS                                                    */
/******************************************************************************/
nvs_handle_t my_handle;
esp_err_t err;

/******************************************************************************/
/* PUBLIC FUNCTION DEFINITIONS                                                */
/******************************************************************************/

/**
 * @brief Flash initialization function
 *
 */
void Flash_Init(void)
{
    // Initialize NVS
    err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        // NVS partition was truncated and needs to be erased
        // Retry nvs_flash_init
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK( err );

    // Open
    printf("\n");
    printf("Opening Non-Volatile Storage (NVS) handle... ");

    err = nvs_open("storage", NVS_READWRITE, &my_handle);
    if (err != ESP_OK) 
    {
        printf("Error (%s) opening NVS handle!\n", esp_err_to_name(err));
    } 
    else 
    {
        printf("Done\n");
    }
    
}

/**
 * @brief Flash write parameters function
 *
 */
void FlashWriteParameters(FlashData* data)
{
    // Write
    err = nvs_set_i32(my_handle, "Drink_Timer_ms", data->Drink_Timer_ms);
    err = nvs_set_i32(my_handle, "PlaceTimer_ms", data->PlaceTimer_ms);
    err = nvs_set_i32(my_handle, "CleanTimer_ms", data->CleanTimer_ms);
    
    printf((err != ESP_OK) ? "Failed!\n" : "Done\n");
 
    // Commit written value.
    // After setting any values, nvs_commit() must be called to ensure changes are written
    // to flash storage. Implementations may write to storage at other times,
    // but this is not guaranteed.
    printf("Committing updates in NVS ... ");
    err = nvs_commit(my_handle);
    printf((err != ESP_OK) ? "Failed!\n" : "Done\n");
}

/**
 * @brief Flash read parameters function
 *
 */
void FlashReadParameters(FlashData* data)
{
    // Read
    err = nvs_get_i32(my_handle, "Drink_Timer_ms", &data->Drink_Timer_ms);
    switch (err) {
        case ESP_OK:
            printf("Done\n");
            printf("Drink_Timer_ms = %" PRIu32 "\n", data->Drink_Timer_ms);
            break;
        case ESP_ERR_NVS_NOT_FOUND:
            printf("The value is not initialized yet!\n");
            data->Drink_Timer_ms = DEFAULT_DRINKTIMER_VALUE;
            break;
        default :
            printf("Error (%s) reading!\n", esp_err_to_name(err));
    }
    
    err = nvs_get_i32(my_handle, "PlaceTimer_ms", &data->PlaceTimer_ms);
    switch (err) {
        case ESP_OK:
            printf("Done\n");
            printf("PlaceTimer_ms = %" PRIu32 "\n", data->PlaceTimer_ms);
            break;
        case ESP_ERR_NVS_NOT_FOUND:
            printf("The value is not initialized yet!\n");
            data->PlaceTimer_ms = DEFAULT_PLACETIMER_VALUE;
            break;
        default :
            printf("Error (%s) reading!\n", esp_err_to_name(err));
    }
    
    err = nvs_get_i32(my_handle, "CleanTimer_ms", &data->CleanTimer_ms);
    switch (err) {
        case ESP_OK:
            printf("Done\n");
            printf("CleanTimer_ms = %" PRIu32 "\n", data->CleanTimer_ms);
            break;
        case ESP_ERR_NVS_NOT_FOUND:
            printf("The value is not initialized yet!\n");
            data->CleanTimer_ms = DEFAULT_CLEANTIMER_VALUE;
            break;
        default :
            printf("Error (%s) reading!\n", esp_err_to_name(err));
    }
}

/******************************************************************************/
/* PRIVATE FUNCTION DEFINITIONS                                               */
/******************************************************************************/

