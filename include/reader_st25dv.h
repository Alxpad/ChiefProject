#ifndef ST25DV_H
#define ST25DV_H

#include <string>
#include "st25dv.h"
#include "st25dv_registers.h"
#include "st25dv_ndef.h"

class ST25dv_device
{
    public:
        ST25dv_device();
        virtual ~ST25dv_device();
        void scan_tag();
};

#endif