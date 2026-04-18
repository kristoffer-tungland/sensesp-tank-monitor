#ifndef TRANSFORMS_DEBOUNCER_HPP_
#define TRANSFORMS_DEBOUNCER_HPP_

#include <Arduino.h>

class Debouncer {
 public:
  explicit Debouncer(unsigned long debounce_ms);

  bool update(bool raw_value);
  bool value() const;

 private:
  unsigned long debounce_ms_;
  bool stable_value_ = true;
  bool last_raw_value_ = true;
  unsigned long changed_at_ms_ = 0;
};

#endif
