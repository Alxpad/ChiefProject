#include <iostream>
#include <esp_log.h>
#include "fsm.h"

extern "C" int app_main() {

    ESP_LOGI("main", "Iniciando programa");
    ST25DV_t::getInstance().initI2C();

    // Add user access address in ST25DV
    ST25DV_t::getInstance().addDeviceI2C_ST25DV(ST25DV_t::getInstance().dev_config_params_USER,&(ST25DV_t::getInstance().deviceHandle_user),&ST25DV_t::getInstance().busHandle);

    // Add system access address in ST25DV
    ST25DV_t::getInstance().addDeviceI2C_ST25DV(ST25DV_t::getInstance().dev_config_params_SYSTEM,&(ST25DV_t::getInstance().deviceHandle_system),&ST25DV_t::getInstance().busHandle);

    // Add device USER address to i2C bus
    if (ST25DV_t::getInstance().deviceHandle_user != nullptr) {
        ESP_LOGI("main", "Device USER handle initialized");
    } else {
        ESP_LOGE("main", "Device USER handle not initialized");
    }

    if (ST25DV_t::getInstance().deviceHandle_system != nullptr) {
        ESP_LOGI("main", "Device SYSTEM handle initialized");
    } else {
        ESP_LOGE("main", "Device SYSTEM handle not initialized");
    }
    // Add device SYSTEM address to i2C bus
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