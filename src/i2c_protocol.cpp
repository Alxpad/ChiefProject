#include "i2c_protocol.h"
#include <esp_log.h>

void i2c_protocol::ST25DV_i2c_params::initI2C()
{
    ESP_ERROR_CHECK(i2c_new_master_bus(&bus_config_params, &busHandle));

}

void i2c_protocol::ST25DV_i2c_params::addDeviceI2C_ST25DV()
{
    ESP_ERROR_CHECK(i2c_master_bus_add_device(busHandle, &dev_config_params, &deviceHandle));

}

void i2c_protocol::i2c_read_addr(i2c_master_dev_handle_t &devHandle, uint8_t addressToWrite, uint8_t &output)
{
    ESP_ERROR_CHECK(i2c_master_transmit_receive(devHandle, &addressToWrite, sizeof(addressToWrite), &output, sizeof(output), 250));
}

void i2c_protocol::i2c_probing(i2c_master_bus_handle_t &busHandle, uint16_t addressToWrite)
{
    ESP_LOGI("I2CProtocol", "Probing I2C in address 0x%04X...", addressToWrite);
    ESP_ERROR_CHECK(i2c_master_probe(busHandle,addressToWrite, 250));
}
 