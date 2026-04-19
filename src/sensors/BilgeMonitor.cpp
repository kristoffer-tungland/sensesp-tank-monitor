#include "sensors/BilgeMonitor.hpp"

BilgeMonitor::BilgeMonitor(uint8_t pin, unsigned long debounce_ms)
    : pin_(pin), debouncer_(debounce_ms) {}

void BilgeMonitor::begin() { pinMode(pin_, INPUT_PULLUP); }

void BilgeMonitor::update() {
  const bool raw_is_high = digitalRead(pin_) == HIGH;
  const bool stable_is_high = debouncer_.update(raw_is_high);
  water_detected_ = !stable_is_high;
}

bool BilgeMonitor::water_detected() const { return water_detected_; }
