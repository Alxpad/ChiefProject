#include <iostream>
#include <esp_log.h>
#include "fsm.h"

extern "C" int app_main() {

    ESP_LOGI("main", "Iniciando programa");
    ST25DV_t::getInstance().initI2C();

    // Add user access address in ST25DV
    ST25DV_t::getInstance().addDeviceI2C_ST25DV(ST25DV_t::getInstance().dev_config_params_USER,ST25DV_t::getInstance().deviceHandle_user,ST25DV_t::getInstance().busHandle);

    // Add system access address in ST25DV
    ST25DV_t::getInstance().addDeviceI2C_ST25DV(ST25DV_t::getInstance().dev_config_params_SYSTEM,ST25DV_t::getInstance().deviceHandle_system,ST25DV_t::getInstance().busHandle);

    // Add device USER address to i2C bus
    //ST25DV_t::getInstance().addDeviceI2C_ST25DV(&ST25DV_t::getInstance().dev_config_params_USER,&ST25DV_t::getInstance().deviceHandle_user);
    
    // Add device SYSTEM address to i2C bus
    //ST25DV_t::getInstance().addDeviceI2C_ST25DV(&ST25DV_t::getInstance().dev_config_params_SYSTEM,&ST25DV_t::getInstance().deviceHandle_system);
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