#include <Arduino.h>
#include <Wire.h>

#include "config/CalibrationConfig.hpp"
#include "outputs/SignalKOutputs.hpp"
#include "sensesp/sensesp.h"
#include "sensesp/sensesp_app_builder.h"
#include "sensors/BilgeMonitor.hpp"
#include "sensors/TankLevelReader.hpp"
#include "sensors/TankSelector.hpp"

using namespace sensesp;

ReactESP app;

TankLevelReader forward_tank_reader(0x40, config::empty_current_forward,
                                    config::full_current_forward,
                                    config::kLevelAverageSamples);
TankLevelReader port_tank_reader(0x41, config::empty_current_port,
                                 config::full_current_port,
                                 config::kLevelAverageSamples);
TankSelector tank_selector(config::kTankSelectorPin, config::kDebounceMs);
BilgeMonitor bilge_monitor(config::kBilgeFloatPin, config::kDebounceMs);
SignalKOutputs* signalk_outputs = nullptr;

void setup() {
  SetupSerialDebug(115200);

  sensesp_app = SensESPAppBuilder().set_hostname("sensesp-tank-monitor").get_app();
  signalk_outputs = new SignalKOutputs();

  Wire.begin(config::kI2cSdaPin, config::kI2cSclPin);

  const bool forward_ok = forward_tank_reader.begin();
  const bool port_ok = port_tank_reader.begin();
  tank_selector.begin();
  bilge_monitor.begin();

  debugI("INA219 forward init: %s", forward_ok ? "OK" : "FAIL");
  debugI("INA219 port init: %s", port_ok ? "OK" : "FAIL");

  app.onRepeat(config::kTankReadIntervalMs, []() {
    forward_tank_reader.update();
    port_tank_reader.update();

    signalk_outputs->publish_forward_level(forward_tank_reader.normalized_level());
    signalk_outputs->publish_port_level(port_tank_reader.normalized_level());

    debugD("Forward raw current: %.2f mA, level: %.3f",
           forward_tank_reader.raw_current_ma(),
           forward_tank_reader.normalized_level());
    debugD("Port raw current: %.2f mA, level: %.3f",
           port_tank_reader.raw_current_ma(), port_tank_reader.normalized_level());
  });

  app.onRepeat(config::kSwitchReadIntervalMs, []() {
    tank_selector.update();
    bilge_monitor.update();

    signalk_outputs->publish_selected_tank(tank_selector.selected_tank());
    signalk_outputs->publish_bilge_water_detected(bilge_monitor.water_detected());

    debugD("Selected tank: %s", tank_selector.selected_tank());
    debugD("Bilge water detected: %s",
           bilge_monitor.water_detected() ? "true" : "false");
  });

  sensesp_app->start();
}

void loop() { app.tick(); }
