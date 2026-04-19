#include "sensors/TankSelector.hpp"

TankSelector::TankSelector(uint8_t pin, unsigned long debounce_ms)
    : pin_(pin), debouncer_(debounce_ms) {}

void TankSelector::begin() { pinMode(pin_, INPUT_PULLUP); }

void TankSelector::update() {
  const bool raw_is_high = digitalRead(pin_) == HIGH;
  const bool stable_is_high = debouncer_.update(raw_is_high);
  forward_selected_ = !stable_is_high;
}

const char* TankSelector::selected_tank() const {
  return forward_selected_ ? "forward" : "port";
}

bool TankSelector::is_forward_selected() const { return forward_selected_; }
