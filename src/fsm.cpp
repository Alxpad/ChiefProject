#include "fsm.h"
#include <freertos/FreeRTOS.h>
#include "st25dv.h" // Include the header file that defines st25dv_ndef_record
#include "st25dv_ndef.h"
#include <cstring> // Include the header file for memset

// ----------------------------------------------------------------------------
// Estados de la fsm

//-- Forward declaration

class Update_data;

//-------

class StateOn : public Fsm_ChiefSight
{
    void entry() override{
        

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
                ST25dv_device::getInstance().test_function();
                
                //TEST ------ {Create ST25DV instance here}

                i2c_config_t i2c_config_params;
    
                i2c_config_params.mode = I2C_MODE_MASTER;
                i2c_config_params.sda_io_num = GPIO_NUM_21;
                i2c_config_params.scl_io_num = GPIO_NUM_22;
                i2c_config_params.sda_pullup_en = GPIO_PULLUP_DISABLE;
                i2c_config_params.scl_pullup_en = GPIO_PULLUP_DISABLE;
                i2c_config_params.master.clk_speed = ST25DV_MAX_CLK_SPEED;
                i2c_config_params.clk_flags = 0;
                
                st25dv_config st25dv_config_params;
                st25dv_config_params.user_address = ST25DV_USER_ADDRESS;
                st25dv_config_params.system_address = ST25DV_SYSTEM_ADDRESS;

                ESP_ERROR_CHECK(st25dv_init_i2c(I2C_NUM_1, i2c_config_params));
                
                ESP_LOGI("ST25DV", "I2C configured and initialized");
                std25dv_ndef_record *read = (std25dv_ndef_record*)malloc(sizeof(std25dv_ndef_record));
                memset(read, 0 , sizeof(std25dv_ndef_record));
                uint8_t record_num = 2;
                uint8_t record_count = 0;

                st25dv_ndef_read(st25dv_config_params,record_num,read,&record_count);
                printf("Record %d type : %s\n", record_num, read->type);

                
                

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