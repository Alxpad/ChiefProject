#include <iostream>
#include <esp_log.h>
#include "fsm.h"

//#include "I2C_setup.h"

extern "C" int app_main() {

    ESP_LOGI("main", "Iniciando programa");
    
    Fsm_ChiefSight::start();

    setup_done setup;
    enterSetup enter;
    timer_5s timer;
    setting_up setting;
    error_logged error;
    shot shot;
    checkUpdateData_false checkDataFalse;
    checkUpdateData_true checkDataTrue;
    checkUpdateTag_true checkTagTrue;
    checkUpdateTag_false checkTagFalse;
    

    
    return 0;
    
}