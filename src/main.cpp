#include <Arduino.h>
#include <Wire.h>

#include "config/CalibrationConfig.hpp"
#include "sensesp/sensors/sensor.h"
#include "sensesp/signalk/signalk_output.h"
#include "sensesp_app_builder.h"
#include "sensors/BilgeMonitor.hpp"
#include "sensors/TankLevelReader.hpp"
#include "sensors/TankSelector.hpp"

using namespace sensesp;

TankLevelReader forward_tank_reader(0x40, config::kEmptyCurrentForward,
                                    config::kFullCurrentForward,
                                    config::kLevelAverageSamples);
TankLevelReader port_tank_reader(0x41, config::kEmptyCurrentPort,
                                 config::kFullCurrentPort,
                                 config::kLevelAverageSamples);
TankSelector tank_selector(config::kTankSelectorPin, config::kDebounceMs);
BilgeMonitor bilge_monitor(config::kBilgeFloatPin, config::kDebounceMs);

void setup() {
  SetupLogging();

  sensesp_app = SensESPAppBuilder().set_hostname("sensesp-tank-monitor")->get_app();

  Wire.begin(config::kI2cSdaPin, config::kI2cSclPin);

  const bool forward_ok = forward_tank_reader.begin();
  const bool port_ok = port_tank_reader.begin();
  tank_selector.begin();
  bilge_monitor.begin();

  debugI("INA219 forward init: %s", forward_ok ? "OK" : "FAIL");
  debugI("INA219 port init: %s", port_ok ? "OK" : "FAIL");

  auto* forward_level = new RepeatSensor<float>(config::kTankReadIntervalMs, []() {
    forward_tank_reader.update();
    const float level = forward_tank_reader.normalized_level();
    debugD("Forward raw current: %.2f mA, level: %.3f",
           forward_tank_reader.raw_current_ma(), level);
    return level;
  });
  forward_level->connect_to(new SKOutputFloat(config::kForwardLevelPath));

  auto* port_level = new RepeatSensor<float>(config::kTankReadIntervalMs, []() {
    port_tank_reader.update();
    const float level = port_tank_reader.normalized_level();
    debugD("Port raw current: %.2f mA, level: %.3f",
           port_tank_reader.raw_current_ma(), level);
    return level;
  });
  port_level->connect_to(new SKOutputFloat(config::kPortLevelPath));

  auto* selected_tank = new RepeatSensor<String>(config::kSwitchReadIntervalMs, []() {
    tank_selector.update();
    const char* tank = tank_selector.selected_tank();
    debugD("Selected tank: %s", tank);
    return String(tank);
  });
  selected_tank->connect_to(new SKOutputString(config::kSelectedTankPath));

  auto* bilge_water = new RepeatSensor<bool>(config::kSwitchReadIntervalMs, []() {
    bilge_monitor.update();
    const bool detected = bilge_monitor.water_detected();
    debugD("Bilge water detected: %s", detected ? "true" : "false");
    return detected;
  });
  bilge_water->connect_to(new SKOutputBool(config::kBilgeWaterPath));
}

void loop() { event_loop()->tick(); }
