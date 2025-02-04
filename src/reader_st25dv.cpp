#include "reader_st25dv.h"

// Singleton definition
ST25dv_device& ST25dv_device::getInstance() {
    static ST25dv_device instance;
    return instance;
}