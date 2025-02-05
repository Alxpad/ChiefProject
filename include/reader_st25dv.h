#ifndef ST25DV_H
#define ST25DV_H

#include <string>

#ifndef READER_ST25DV_H
#define READER_ST25DV_H

#include "esp_log.h"
#include "esp_err.h"
#include <driver/i2c_master.h>

// Singleton structure

/*
void init_i2c_connection();

class ST25dv_device {
public:
    static ST25dv_device& getInstance(); // Retorna la única instancia
        
private:
    ST25dv_device() {} // Constructor privado
    ST25dv_device(const ST25dv_device&) = delete;
    ST25dv_device& operator=(const ST25dv_device&) = delete;
};
*/
struct init_i2c_config
{
    i2c_master_bus_config_t I2C_busConfig = {
            .i2c_port = I2C_NUM_0,
            .sda_io_num = GPIO_NUM_21,
            .scl_io_num = GPIO_NUM_22,
            .clk_source = I2C_CLK_SRC_DEFAULT,
            .glitch_ignore_cnt = 0,
            .intr_priority = 1,
            .flags = {
                .enable_internal_pullup = 0,
                .allow_pd = 0
            }
            
    };
    
    const i2c_device_config_t ST25DV_config
    {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = ST25DV_USER_ADDRESS,
        .scl_speed_hz = ST25DV_MAX_CLK_SPEED,
        .scl_wait_us = 200,
        .flags = {0} // Initialize the flags member
    };
        
    i2c_master_bus_handle_t bus_handle;
    i2c_master_dev_handle_t dev_handle;

    void init_i2c_connection() {
        ESP_ERROR_CHECK(i2c_new_master_bus(&I2C_busConfig, &bus_handle));

    // Create bus and device connection
    // Note: Accessing user address from this device_handler
    // TODO: Implement a customizable device constructor to allow access as system or user based on choice
        ESP_ERROR_CHECK(i2c_master_bus_add_device(bus_handle, &ST25DV_config, &dev_handle));
    }
};

#endif // READER_ST25DV_H


#endif