#include "reader_st25dv.h"

// Singleton definition
ST25dv_device& ST25dv_device::getInstance() {
    static ST25dv_device instance;
    return instance;
}

void ST25dv_device::test_function() {
    ESP_LOGI("ST25DV", "Singleton test function");
}

void ST25dv_device::I2C_Config()
{   
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
    this->i2c_config_dev = i2c_config_params;
    this->st25dv_config_dev = st25dv_config_params;
    
    ESP_LOGI("ST25DV", "I2C parameters stored");
}