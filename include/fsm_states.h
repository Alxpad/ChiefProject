#ifndef FSM_STATES_H
#define FSM_STATES_H

#include "fsm_stateMachine.h"

// states declaration
class stateOn : public ChiefSight
{
  
    void entry() override;

};

class setup : public ChiefSight
{
  //void react({Baseevent} const &) override;
};

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


#endif // FSM_STATES_H