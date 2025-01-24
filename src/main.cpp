#include <iostream>
#include <esp_log.h>
#include <fsm_states.h>


extern "C" int app_main() {

    ESP_LOGI("main", "Iniciando programa");
    fsm::ChiefSight chiefSight;
    fsm::stateOn stateOn;

    // Instantiate events
    fsm::turnOn turnOn;
    fsm::enter_setup enter_setup;
    fsm::setup_done setup_done;
    fsm::timer_5s timer_5s;

    // Start the state machine
    using fsm_handle = fsm::ChiefSight;

    ESP_LOGI("main", "Iniciando máquina de estados");
    fsm_handle::start();
    return 0;
    
}