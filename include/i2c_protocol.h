#ifndef ST25DV_H
#define ST25DV_H


#include <driver/i2c_master.h>
#include <iostream>
#include "ST25DV_registers.h"

extern "C"{
namespace i2c_protocol
    {
        typedef struct stdv25_ndef_record
        {
            uint8_t tnf;
            char *type;
            char *payload;
        };

        class ST25DV_i2c_params
        {
        public:
            static ST25DV_i2c_params& getInstance()
            {
            static ST25DV_i2c_params instance;
            return instance;
            }

            ST25DV_i2c_params(const ST25DV_i2c_params&) = delete;
            void operator=(const ST25DV_i2c_params&) = delete;

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

            i2c_device_config_t dev_config_params_USER =
            {
            .dev_addr_length = I2C_ADDR_BIT_LEN_7,
            .device_address = ST25DV_USER_ADDRESS,
            .scl_speed_hz = ST25DV_MAX_CLK_SPEED,
            .flags = {
                .disable_ack_check = 1
                }
            };

            i2c_device_config_t dev_config_params_SYSTEM =
            {
            .dev_addr_length = I2C_ADDR_BIT_LEN_7,
            .device_address = ST25DV_SYSTEM_ADDRESS,
            .scl_speed_hz = ST25DV_MAX_CLK_SPEED,
            .flags = {
                .disable_ack_check = 1
                }
            };

            i2c_master_bus_handle_t busHandle;
            i2c_master_dev_handle_t deviceHandle_user;
            i2c_master_dev_handle_t deviceHandle_system;

            void initI2C();
            void addDeviceI2C_ST25DV(i2c_device_config_t &devConfig , i2c_master_dev_handle_t *devHandle , i2c_master_bus_handle_t *busHandle );

        private:
            ST25DV_i2c_params() = default;
        };

        //-------- Functions
        void i2c_read_addr(i2c_master_dev_handle_t &devHandle,uint8_t *addressToWrite,uint8_t &output);
        void i2c_probing(i2c_master_bus_handle_t &busHandle, uint16_t addressToWrite);

        void i2c_read_ndef(i2c_protocol::stdv25_ndef_record ndef_record, i2c_master_dev_handle_t &devHandle , uint8_t *record_count); // Read NFC tag
    };
}
#endif