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
    init_i2c_config i2c_conf;

    
    void entry() override{
        ESP_LOGI("FSMStateOn", "State on entry");
        // Create a timer with a 5-second period
        TimerHandle_t timer5 = xTimerCreate(
            "Timer5s",                // Timer name
            pdMS_TO_TICKS(5000),      // Timer period in ticks (5 seconds)
            pdFALSE,                  // Auto-reload (pdFALSE means one-shot)
            NULL,                // Timer ID
            [](TimerHandle_t xTimer){
                ESP_LOGI("FSMStateOn", "Timer expired");
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
    


    static void timedFunction(TimerHandle_t xTimer, init_i2c_config &conf)
    {
        ESP_LOGI("FSMRunning","Probing i2c");
        ESP_ERROR_CHECK(i2c_master_probe(conf.bus_handle, ST25DV_USER_ADDRESS,-1));
    }

    void entry() override{
        static init_i2c_config i2c_conf;
        i2c_conf.init_i2c_connection();
        ESP_LOGI("FSMRunning", "Running state");
        TimerHandle_t timer2 = xTimerCreate(
            "Timer5s",                // Timer name
            pdMS_TO_TICKS(2000),      // Timer period in ticks (5 seconds)
            pdTRUE,                  // Auto-reload (pdFALSE means one-shot)
            NULL,                // Timer ID
            [](TimerHandle_t xTimer) { timedFunction(xTimer, i2c_conf); }
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