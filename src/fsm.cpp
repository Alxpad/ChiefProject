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
        ESP_LOGI("FSM", "State on entry");
        // Create a timer with a 5-second period
        TimerHandle_t timer5s = xTimerCreate(
            "Timer5s",                // Timer name
            pdMS_TO_TICKS(5000),      // Timer period in ticks (5 seconds)
            pdFALSE,                  // Auto-reload (pdFALSE means one-shot)
            NULL,                // Timer ID
            [](TimerHandle_t xTimer) { // Timer callback function
                // Handle timer expiration
                ESP_LOGI("FSM", "Timer expired, transitioning to Running state");
                xTimerStop(xTimer, 0);
                Fsm_ChiefSight::dispatch(timer_5s());
            }
        );

        // Start the timer
        if (timer5s != NULL) {
            xTimerStart(timer5s, 0);
        } else {
            ESP_LOGE("FSM", "Failed to create timer");
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
        ESP_LOGI("FSM", "Running state");
        TimerHandle_t timer2s = xTimerCreate(
            "Timer5s",                // Timer name
            pdMS_TO_TICKS(2000),      // Timer period in ticks (5 seconds)
            pdFALSE,                  // Auto-reload (pdFALSE means one-shot)
            NULL,                // Timer ID
            [](TimerHandle_t xTimer) { // Timer callback function
                // Handle timer expiration
                ESP_LOGI("FSM", "Timer expired, transitioning to Running state");
                xTimerStop(xTimer, 0);
            }
        );

        // Start the timer
        if (timer2s != NULL) {
            xTimerStart(timer2s, 0);
        } else {
            ESP_LOGE("FSM", "Failed to create timer");
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