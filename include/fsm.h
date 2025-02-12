#ifndef FSM_STATES_H
#define FSM_STATES_H

#include <tinyfsm.hpp>
#include <string>
#include <esp_log.h>
#include "i2c_protocol.h"

using ST25DV_t = i2c_protocol::ST25DV_i2c_params;

//----------------------------------------
// event declarations

struct setup_done               : tinyfsm::Event { };
struct enterSetup               : tinyfsm::Event { };
struct timer_5s                 : tinyfsm::Event { };
struct setting_up               : tinyfsm::Event { };
struct error_logged             : tinyfsm::Event { };
struct shot                     : tinyfsm::Event { };
struct checkUpdateData_false    : tinyfsm::Event { };
struct checkUpdateData_true     : tinyfsm::Event { };
struct checkUpdateTag_true      : tinyfsm::Event { };
struct checkUpdateTag_false     : tinyfsm::Event { };

//--------------------------------------------
// FSM declaration

class Fsm_ChiefSight : public tinyfsm::Fsm<Fsm_ChiefSight>
{
    public: 
        void react(tinyfsm::Event const &){ }; // Reacción por defecto para estados sin manejador

        void react(setup_done const &);
        void react(enterSetup const &);
        void react(timer_5s const &);
        void react(setting_up const &);
        void react(error_logged const &);
        void react(shot const &);
        void react(checkUpdateData_false const &);
        void react(checkUpdateData_true const &);
        void react(checkUpdateTag_true const &);
        void react(checkUpdateTag_false const &);


        /* Declaración no-virtual: Será la misma en todos los estados */
        //void react()

        /* Declaración virtual: Habrá que definirla en cada estado */

        virtual void entry(void) = 0; // Pura virtual: Obliga a implementarla en todos los estados
        void exit(void) { };
};


#endif