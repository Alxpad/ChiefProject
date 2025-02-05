#ifndef ST25DV_H
#define ST25DV_H


#include <driver/i2c_master.h>
#include <iostream>
#include "ST25DV_registers.h"

extern "C"{
namespace i2c_protocol
    {
        struct ST25DV_i2c_params
        {
             i2c_master_bus_config_t bus_config_params =
            {
                .i2c_port = I2C_NUM_0,
                .sda_io_num = GPIO_NUM_21,
                .scl_io_num = GPIO_NUM_22,
                .clk_source = I2C_CLK_SRC_DEFAULT,
                .glitch_ignore_cnt = 7,
                .flags = {
                    .enable_internal_pullup = 0
                }
            };

             i2c_device_config_t dev_config_params =
            {
                .dev_addr_length = I2C_ADDR_BIT_LEN_7,
                .device_address = ST25DV_USER_ADDRESS,
                .scl_speed_hz = ST25DV_MAX_CLK_SPEED,
                .flags = {
                    .disable_ack_check = 1
                }
            };

            i2c_master_bus_handle_t busHandle;
            i2c_master_dev_handle_t deviceHandle;
            void initI2C()
                {
                    ESP_ERROR_CHECK(i2c_new_master_bus(&bus_config_params, &busHandle));
                }

            void addDeviceI2C()
                {
                    ESP_ERROR_CHECK(i2c_master_bus_add_device(busHandle, &dev_config_params, &deviceHandle));
                }
        } ;
    };
}
#endif