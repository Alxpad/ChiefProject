#include <iostream>
#include <esp_log.h>
#include "fsm.h"

extern "C" int app_main() {

    ESP_LOGI("main", "Iniciando programa");
    i2c_protocol::ST25DV_i2c_params::getInstance().initI2C();
    i2c_protocol::ST25DV_i2c_params::getInstance().addDeviceI2C_ST25DV();

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