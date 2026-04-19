#ifndef CONFIG_CALIBRATION_CONFIG_HPP_
#define CONFIG_CALIBRATION_CONFIG_HPP_

#include <stddef.h>
#include <stdint.h>

namespace config {

constexpr uint8_t kTankSelectorPin = 2;
constexpr uint8_t kBilgeFloatPin = 3;

constexpr uint8_t kI2cSdaPin = 8;
constexpr uint8_t kI2cSclPin = 9;

constexpr uint32_t kTankReadIntervalMs = 1000;
constexpr uint32_t kSwitchReadIntervalMs = 100;
constexpr uint32_t kDebounceMs = 75;
constexpr size_t kLevelAverageSamples = 5;

constexpr float kEmptyCurrentForward = 4.0F;
constexpr float kFullCurrentForward = 20.0F;
constexpr float kEmptyCurrentPort = 4.0F;
constexpr float kFullCurrentPort = 20.0F;

// SignalK paths
constexpr const char* kForwardLevelPath = "tanks.freshWater.forward.currentLevel";
constexpr const char* kPortLevelPath = "tanks.freshWater.port.currentLevel";
constexpr const char* kSelectedTankPath = "tanks.freshWater.selectedTank";
constexpr const char* kBilgeWaterPath = "environment.bilge.waterDetected";

}  // namespace config

#endif
