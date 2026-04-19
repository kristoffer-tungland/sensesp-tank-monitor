#include "transforms/Debouncer.hpp"

#include <limits>

Debouncer::Debouncer(unsigned long debounce_ms) : debounce_ms_(debounce_ms) {}

bool Debouncer::update(bool raw_value) {
  const unsigned long now = millis();

  if (raw_value != last_raw_value_) {
    last_raw_value_ = raw_value;
    changed_at_ms_ = now;
  }

  const unsigned long elapsed =
      now >= changed_at_ms_
          ? (now - changed_at_ms_)
          : (std::numeric_limits<unsigned long>::max() - changed_at_ms_) + now +
                1UL;
  if (elapsed >= debounce_ms_) {
    stable_value_ = last_raw_value_;
  }

  return stable_value_;
}

bool Debouncer::value() const { return stable_value_; }
