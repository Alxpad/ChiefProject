#ifndef ST25DV_H
#define ST25DV_H

#include <string>

extern "C" {
    #include "st25dv.h"
    #include "st25dv_ndef.h"
    #include "st25dv_registers.h"
};

#ifndef READER_ST25DV_H
#define READER_ST25DV_H

#include "esp_log.h"
#include "esp_err.h"

// Singleton structure

class ST25dv_device {
public:
    static ST25dv_device& getInstance(); // Retorna la única instancia
    void I2C_Config(); // Configura el I2C
    void test_function(); // Método de prueba
    
    i2c_config_t i2c_config_dev;    
    st25dv_config st25dv_config_dev;

private:
    ST25dv_device() {} // Constructor privado
    ST25dv_device(const ST25dv_device&) = delete;
    ST25dv_device& operator=(const ST25dv_device&) = delete;
};

#endif // READER_ST25DV_H


#endif