#include "transforms/LinearCalibration.hpp"

#include <algorithm>

float LinearCalibration::map_current_to_level(float current_ma,
                                              float empty_current_ma,
                                              float full_current_ma) {
  const float span = full_current_ma - empty_current_ma;
  if (span == 0.0F) {
    return 0.0F;
  }
  const float normalized = (current_ma - empty_current_ma) / span;
  return std::clamp(normalized, 0.0F, 1.0F);
}
