#include "i2c_protocol.h"
#include <esp_log.h>

void i2c_protocol::ST25DV_i2c_params::initI2C()
{
    ESP_ERROR_CHECK(i2c_new_master_bus(&bus_config_params, &busHandle));

}

void i2c_protocol::ST25DV_i2c_params::addDeviceI2C_ST25DV(i2c_device_config_t &devConfig , i2c_master_dev_handle_t *devHandle , i2c_master_bus_handle_t *busHandle)
{
    ESP_ERROR_CHECK(i2c_master_bus_add_device(*busHandle, &devConfig, devHandle));
}

void i2c_protocol::i2c_read_addr(i2c_master_dev_handle_t &devHandle, uint8_t *addressToWrite, uint8_t &output)
{
    ESP_LOGI("I2CProtocol","i2c_read_addr address = %02X%02X",addressToWrite[0],addressToWrite[1]);
    ESP_ERROR_CHECK(i2c_master_transmit_receive(devHandle, addressToWrite, sizeof(addressToWrite), &output, sizeof(output), 250));
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
    uint8_t response[11];
    uint8_t read_address[2] = {0x00,0x04};
    ESP_LOGI("NDEF read","Reading block 0x%02X%02X",read_address[0],read_address[1]);
    
    ESP_ERROR_CHECK(i2c_master_transmit_receive(devHandle,read_address,sizeof(read_address),response,sizeof(response),-1));
    ESP_LOGI("I2CProtocol", "Response value returned: 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X", response[0], response[1], response[2], response[3], response[4], response[5], response[6], response[7], response[8], response[9], response[10]);
    char translated_text[10] = { '\0' };

    ESP_LOGI("TranslatedText", "Translated content: %s", translated_text);    //i2c_protocol::i2c_read_addr(devHandle, read_address, *tlv);
    /*
        devhandle -> Handle with system address loaded
        addressToWrite -> 0x20h 
        output -> output object
    */
    
    if (!(response[0] == ST25DV_TYPE5_NDEF_MESSAGE)) {
        // Handle the error appropriately, e.g., log an error or return from the function
        ESP_LOGI("I2CProtocol", "TLV value: 0x%02X", response[0]);
        ESP_LOGE("I2CProtocol", "NDEF message type check failed");
    }
    
    else
    {
        ESP_LOGI("I2CProtocol", "TLV value: 0x%02X", response[0]);
    }
}