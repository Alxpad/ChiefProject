#ifndef I2C_SETUP_H
#define I2C_SETUP_H

#include "driver/i2c.h"
#include "esp_log.h"

/**
 * @brief Configures and initializes the I2C driver.
 *
 * This function sets up the I2C configuration parameters and installs the I2C driver.
 * It configures the I2C to operate in master mode with specified GPIO pins for SDA and SCL,
 * enables pull-up resistors for these pins, and sets the clock speed to 100kHz.
 * 
 * The function performs the following steps:
 * 1. Initializes an i2c_config_t structure with the desired I2C settings.
 * 2. Configures the I2C parameters using i2c_param_config().
 * 3. Installs the I2C driver using i2c_driver_install().
 *
 * @note This function assumes the use of I2C_NUM_0 and specific GPIO pins (21 for SDA and 22 for SCL).
 *       Adjust the GPIO pins and other parameters as needed for your specific application.
 */
void i2c_setup()
{
    i2c_config_t conf;
    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = GPIO_NUM_21;
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    conf.scl_io_num = GPIO_NUM_22;
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    conf.master.clk_speed = 100000; // 100kHz

    i2c_param_config(I2C_NUM_0, &conf);
    i2c_driver_install(I2C_NUM_0, conf.mode, 0, 0, 0);
}

#endif // I2C_SETUP_H