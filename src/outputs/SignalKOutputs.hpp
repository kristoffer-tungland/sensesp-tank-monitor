#ifndef OUTPUTS_SIGNAL_K_OUTPUTS_HPP_
#define OUTPUTS_SIGNAL_K_OUTPUTS_HPP_

#include "sensesp/signalk/signalk_output.h"

class SignalKOutputs {
 public:
  SignalKOutputs();

  void publish_forward_level(float level);
  void publish_port_level(float level);
  void publish_selected_tank(const char* selected_tank);
  void publish_bilge_water_detected(bool water_detected);

 private:
  sensesp::SKOutputFloat forward_tank_level_;
  sensesp::SKOutputFloat port_tank_level_;
  sensesp::SKOutputString selected_tank_;
  sensesp::SKOutputBool bilge_water_detected_;
};

#endif
