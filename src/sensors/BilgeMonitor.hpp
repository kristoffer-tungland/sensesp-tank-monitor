#ifndef SENSORS_BILGE_MONITOR_HPP_
#define SENSORS_BILGE_MONITOR_HPP_

#include <Arduino.h>

#include "transforms/Debouncer.hpp"

class BilgeMonitor {
 public:
  explicit BilgeMonitor(uint8_t pin, unsigned long debounce_ms);

  void begin();
  void update();

  bool water_detected() const;

 private:
  uint8_t pin_;
  Debouncer debouncer_;
  bool water_detected_ = false;
};

#endif
