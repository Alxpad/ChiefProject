#ifndef FSM_STATES_H
#define FSM_STATES_H

#include "esp_log.h"
#include "fsm_events.h"
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"

// states declaration
// Functions will be defined implicitly in the file


void timerCallback(TimerHandle_t xTimer){
  ESP_LOGI("FSMstates", "Timer 5s expired");
}

namespace fsm{

  struct setup;
  struct ChiefSight : public tinyfsm::Fsm<ChiefSight> // Clase base para los estados
  {
      public:
          virtual void react(){}; // Cuando se produce el evento indicado, se activa la función react dentro del estado actual.

          virtual void entry(){}; // Función que se ejecuta al entrar en el estado.
          virtual void exit(){};  // Función que se ejecuta al salir del estado.
          virtual void react(fsm::enter_setup const &){}; // Acción cuando se produce el evento indicado
  };

struct stateOn : public fsm::ChiefSight
{
  void entry() override {
    ESP_LOGI("stateOn", "entry");
    TimerHandle_t timer = xTimerCreate("Timer", pdMS_TO_TICKS(5000), pdFALSE, NULL, timerCallback);
    xTimerStart(timer, 0);
  };
  void react(fsm::enter_setup const &) { transit<setup>();}; // Acción cuando se produce el evento indicado

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