#include "sensors/TankLevelReader.hpp"

#include "transforms/LinearCalibration.hpp"

TankLevelReader::TankLevelReader(uint8_t i2c_address, float empty_current_ma,
                                 float full_current_ma, size_t average_samples)
    : ina219_(i2c_address),
      moving_average_(average_samples),
      empty_current_ma_(empty_current_ma),
      full_current_ma_(full_current_ma) {}

bool TankLevelReader::begin() { return ina219_.begin(); }

void TankLevelReader::update() {
  raw_current_ma_ = ina219_.getCurrent_mA();
  const float smoothed_current = moving_average_.update(raw_current_ma_);
  normalized_level_ = LinearCalibration::map_current_to_level(
      smoothed_current, empty_current_ma_, full_current_ma_);
}

float TankLevelReader::raw_current_ma() const { return raw_current_ma_; }

float TankLevelReader::normalized_level() const { return normalized_level_; }
