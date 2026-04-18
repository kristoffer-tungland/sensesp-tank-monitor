#include "outputs/SignalKOutputs.hpp"

SignalKOutputs::SignalKOutputs()
    : forward_tank_level_("tanks.freshWater.forward.currentLevel"),
      port_tank_level_("tanks.freshWater.port.currentLevel"),
      selected_tank_("tanks.freshWater.selectedTank"),
      bilge_water_detected_("environment.bilge.waterDetected") {}

void SignalKOutputs::publish_forward_level(float level) {
  forward_tank_level_.set_input(level);
}

void SignalKOutputs::publish_port_level(float level) {
  port_tank_level_.set_input(level);
}

void SignalKOutputs::publish_selected_tank(const char* selected_tank) {
  selected_tank_.set_input(selected_tank);
}

void SignalKOutputs::publish_bilge_water_detected(bool water_detected) {
  bilge_water_detected_.set_input(water_detected);
}
