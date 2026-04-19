#ifndef SENSORS_TANK_SELECTOR_HPP_
#define SENSORS_TANK_SELECTOR_HPP_

#include <Arduino.h>

#include "transforms/Debouncer.hpp"

class TankSelector {
 public:
  explicit TankSelector(uint8_t pin, unsigned long debounce_ms);

  void begin();
  void update();

  const char* selected_tank() const;
  bool is_forward_selected() const;

 private:
  uint8_t pin_;
  Debouncer debouncer_;
  bool forward_selected_ = true;
};

#endif
