#ifndef FSM_STATEMACHINE_H
#define FSM_STATEMACHINE_H

#include <tinyfsm.hpp>
#include "fsm_events.h"
#include "fsm_states.h"
#include "esp_log.h"


class ChiefSight : public tinyfsm::Fsm<ChiefSight>
{
    public:
        virtual void react(turnOn const &);
        virtual void react(turnOff const &);
        virtual void react(enter_setup const &);
        virtual void react(setup_done const &);
        virtual void react(timer_5s const &);
        virtual void react(timer_10s const &);
        virtual void react(error const &);
        virtual void react(error_logged const &);
        virtual void react(shot const &);
        virtual void react(new_tag_detected const &);
        virtual void react(check_update_data const &);
        virtual void react(check_update_tag const &);
        virtual void entry(void);
        virtual void exit(void);
        virtual void reset();

};

#endif
