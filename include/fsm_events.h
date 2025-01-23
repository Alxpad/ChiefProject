#ifndef FSM_EVENTS_H
#define FSM_EVENTS_H

#include <tinyfsm.hpp>

//FSM states for the main program
//Declare events that state machine will listen to

struct BaseEvent : tinyfsm::Event {};

struct turnOn : BaseEvent {};
struct turnOff : BaseEvent {};
struct enter_setup : BaseEvent {};
struct setup_done : BaseEvent {};
struct timer_5s : BaseEvent {};
struct timer_10s : BaseEvent {};
struct error : BaseEvent {};
struct error_logged : BaseEvent {};
struct shot : BaseEvent {};
struct new_tag_detected : BaseEvent {};
struct check_update_data : BaseEvent {};
struct check_update_tag : BaseEvent {};

#endif // FSM_EVENTS_H