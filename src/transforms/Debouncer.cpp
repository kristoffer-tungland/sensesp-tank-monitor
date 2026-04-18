#include "transforms/Debouncer.hpp"

Debouncer::Debouncer(unsigned long debounce_ms) : debounce_ms_(debounce_ms) {}

bool Debouncer::update(bool raw_value) {
  const unsigned long now = millis();

  if (raw_value != last_raw_value_) {
    last_raw_value_ = raw_value;
    changed_at_ms_ = now;
  }

  if ((now - changed_at_ms_) >= debounce_ms_) {
    stable_value_ = last_raw_value_;
  }

  return stable_value_;
}

bool Debouncer::value() const { return stable_value_; }
