#include "i2c_protocol.h"
#include <esp_log.h>

void i2c_protocol::ST25DV_i2c_params::initI2C()
{
    ESP_ERROR_CHECK(i2c_new_master_bus(&bus_config_params, &busHandle));

}

void i2c_protocol::ST25DV_i2c_params::addDeviceI2C_ST25DV(i2c_device_config_t devConfig , i2c_master_dev_handle_t devHandle , i2c_master_bus_handle_t busHandle)
{
    ESP_ERROR_CHECK(i2c_master_bus_add_device(busHandle, &devConfig, &devHandle));
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

//TODO: Función para leer direcciones de 16bit

//TODO: Terminar función para lectura
void i2c_protocol::i2c_read_ndef(i2c_protocol::stdv25_ndef_record ndef_record, i2c_master_dev_handle_t &devHandle , uint8_t *record_count)
{
    uint8_t enda1 = 0;
    *record_count = 0;
    //i2c_read_addr(i2c_slave_dev_handle_t, , enda1);

    enda1 = enda1 * 32 + 31;
    uint16_t address = CCFILE_LENGTH;

    // Read Type 5 tag tlv-format
    uint8_t *tlv = (uint8_t*) malloc(4);
    uint16_t l_value = 0;
    i2c_protocol::i2c_read_addr(devHandle,ST25DV_USER_ADDRESS, *tlv);
    
    if (!(tlv[0] == ST25DV_TYPE5_NDEF_MESSAGE)) {
        // Handle the error appropriately, e.g., log an error or return from the function
        ESP_LOGE("I2CProtocol", "NDEF message type check failed");
        free(tlv);
        return;
    }

    free(tlv);
}
