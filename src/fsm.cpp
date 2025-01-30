#include "fsm.h"
#include <freertos/FreeRTOS.h>

// ----------------------------------------------------------------------------
// Estados de la fsm

//-- Forward declaration

class Update_data;

//-------

class StateOn : public Fsm_ChiefSight
{
    void entry() override{
        ST25dv_device::getInstance().I2C_Config();

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
                uint8_t value = 0; 
                st25dv_read_byte(ST25DV_USER_ADDRESS, 0x00, &value);
                ESP_LOGI("FSMRunning", "Reading 0x00 value : 0x%02X\n", value);
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