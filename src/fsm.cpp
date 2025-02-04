#include "fsm.h"
#include <freertos/FreeRTOS.h>
#include "st25dv.h" // Include the header file that defines st25dv_ndef_record
#include "st25dv_ndef.h"
#include <cstring> // Include the header file for memset
#include <driver/i2c_master.h>

// ----------------------------------------------------------------------------
// Estados de la fsm

//-- Forward declaration

class Update_data;

//-------

class StateOn : public Fsm_ChiefSight
{
    void entry() override{
        
        i2c_master_bus_config_t I2C_busConfig;
            I2C_busConfig.i2c_port = I2C_NUM_0;
            I2C_busConfig.sda_io_num = GPIO_NUM_21;
            I2C_busConfig.scl_io_num = GPIO_NUM_22;
            I2C_busConfig.clk_source = I2C_CLK_SRC_DEFAULT;
            I2C_busConfig.glitch_ignore_cnt = 0;
            I2C_busConfig.intr_priority = 1;
            I2C_busConfig.flags.enable_internal_pullup = 0;
            I2C_busConfig.flags.allow_pd = 0;

        const i2c_device_config_t ST25DV_config
        {
            .dev_addr_length = I2C_ADDR_BIT_LEN_7,
            .device_address = ST25DV_USER_ADDRESS,
            .scl_speed_hz = ST25DV_MAX_CLK_SPEED,
            .scl_wait_us = 200
        };
        
        i2c_master_bus_handle_t bus_handle;
        ESP_ERROR_CHECK(i2c_new_master_bus(&I2C_busConfig,&bus_handle));

        // Create bus and device connection
        i2c_master_dev_handle_t dev_handle;
        ESP_ERROR_CHECK(i2c_master_bus_add_device(bus_handle, &ST25DV_config, &dev_handle));



        ESP_LOGI("FSMStateOn", "State on entry");
        // Create a timer with a 5-second period
        TimerHandle_t timer5 = xTimerCreate(
            "Timer5s",                // Timer name
            pdMS_TO_TICKS(5000),      // Timer period in ticks (5 seconds)
            pdFALSE,                  // Auto-reload (pdFALSE means one-shot)
            NULL,                // Timer ID
            [](TimerHandle_t xTimer) { // Timer callback function
                // Handle timer expiration
                ESP_LOGI("FSMStateOn", "Timer expired, transitioning to Running state");
                xTimerStop(xTimer, 0);
                Fsm_ChiefSight::dispatch(timer_5s());
            }
        );

        // Start the timer
        if (timer5 != NULL) {
            xTimerStart(timer5, 0);
        } else {
            ESP_LOGE("FSMStateOn", "Failed to create timer");
        }
    }
};

class setupMode : public Fsm_ChiefSight
{
    void entry() override{
        ESP_LOGI("FSM", "Setup mode entry");
    }
};

class Running : public Fsm_ChiefSight
{
    void entry() override{
        ESP_LOGI("FSMRunning", "Running state");
        TimerHandle_t timer2 = xTimerCreate(
            "Timer5s",                // Timer name
            pdMS_TO_TICKS(2000),      // Timer period in ticks (5 seconds)
            pdTRUE,                  // Auto-reload (pdFALSE means one-shot)
            NULL,                // Timer ID
            [](TimerHandle_t xTimer) { // Timer callback function
                // Handle timer expiration
                ESP_LOGI("FSMRunning", "Launching ST TestFunction");
                
                //TEST ------ {Create ST25DV instance here}

                ESP_LOGI("ST25DV", "I2C configured and initialized");
                std25dv_ndef_record *read = (std25dv_ndef_record*)malloc(sizeof(std25dv_ndef_record));
                memset(read, 0 , sizeof(std25dv_ndef_record));
                uint8_t record_num = 2;
                uint8_t record_count = 0;

                // -------
            }
        );

        // Start the timer
        if (timer2 != NULL) {
            xTimerStart(timer2, 0);
        } else {
            ESP_LOGE("FSMRunning", "Failed to create timer");
        }
        
    }

    void react(shot const &){
        transit<Update_data>();
        
    }

    //TODO: Scanner function ST25DV
};

class Update_data : public Fsm_ChiefSight
{
    void entry() override
    {
        ESP_LOGI("FSM", "Updating data");
    }

    void react(checkUpdateData_true const &)
    {
        transit<Running>();
    }

    //TODO: Implementar check falso (Comprobar que se cumplen las condiciones)
};

//-------------------------------------------------------------
// Base state: default implementations
//

void Fsm_ChiefSight::react(setup_done const &){
    transit<Running>();
}

void Fsm_ChiefSight::react(enterSetup const &){
    transit<setupMode>();
}

void Fsm_ChiefSight::react(timer_5s const &){
    transit<Running>();
}

//-------------------------------------------------------------
// Initial state definition
//

FSM_INITIAL_STATE(Fsm_ChiefSight, StateOn);