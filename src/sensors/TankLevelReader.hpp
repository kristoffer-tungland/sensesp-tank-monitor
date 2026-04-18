#ifndef SENSORS_TANK_LEVEL_READER_HPP_
#define SENSORS_TANK_LEVEL_READER_HPP_

#include <Adafruit_INA219.h>

#include "transforms/MovingAverage.hpp"

class TankLevelReader {
 public:
  TankLevelReader(uint8_t i2c_address, float empty_current_ma,
                  float full_current_ma, size_t average_samples);

  bool begin();
  void update();

  float raw_current_ma() const;
  float normalized_level() const;

 private:
  Adafruit_INA219 ina219_;
  MovingAverage moving_average_;
  float empty_current_ma_;
  float full_current_ma_;
  float raw_current_ma_ = 0.0F;
  float normalized_level_ = 0.0F;
};

#endif
