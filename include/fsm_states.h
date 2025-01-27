#ifndef FSM_STATES_H
#define FSM_STATES_H

#include <tinyfsm.hpp>
#include <string>
#include "esp_log.h"
#include "fsm_events.h"
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
#include "fsmlist.h"

// states declaration
// Functions will be defined implicitly in the file

struct notFsm{
  notFsm(){};
};

namespace fsm{

  struct setup;
  struct Running;
  struct stateOn;

  struct testStruct : public tinyfsm::Fsm<testStruct>
  {
    void entry() {
      ESP_LOGI("testStruct", "entry");
    };
    void exit() {
      ESP_LOGI("testStruct", "exit");
    };
    void react(fsm::turnOn const &) {transit<stateOn>();};
  };

  struct ChiefSight : public tinyfsm::Fsm<ChiefSight> // Clase base para los estados
  {
      public:
          //virtual void react(){}; // Cuando se produce el evento indicado, se activa la función react dentro del estado actual.

          virtual void entry(){}; // Función que se ejecuta al entrar en el estado.
          virtual void exit(){};  // Función que se ejecuta al salir del estado.
          virtual void react(fsm::enter_setup const &){}; // Acción cuando se produce el evento indicado
  };

struct stateOn : public fsm::ChiefSight
{
  static void timerCallback(TimerHandle_t xTimer){
    ESP_LOGI("FSMstates", "Timer 5s expired");
    send_event(fsm::timer_5s());
  }

  void entry() override {
    ESP_LOGI("stateOn", "entry");
    TimerHandle_t xTimer = xTimerCreate("Timer 5s", pdMS_TO_TICKS(5000), pdFALSE, NULL, timerCallback);
    xTimerStart(xTimer, 0);
  };
  void react(fsm::enter_setup const &) { transit<setup>();}; // Acción cuando se produce el evento indicado
  void react(fsm::timer_5s const &) { transit<Running>();}; // Acción cuando se produce el evento indicado

  //void react(fsm::setup_done) override;
};

struct setup : public fsm::ChiefSight
{
  //void react({Baseevent} const &) override;
};
/*
class Running : public ChiefSight
{
  //void react({Baseevent} const &) override;
};

class error : public ChiefSight
{
  //void react({Baseevent} const &) override;
};

class update_data : public ChiefSight
{
  //void react({Baseevent} const &) override;
};

class update_tag : public ChiefSight
{
  //void react({Baseevent} const &) override;
};
*/

} // namespace fsm

FSM_INITIAL_STATE(fsm::ChiefSight, fsm::stateOn);

#endif // FSM_STATES_H