#ifndef TRANSFORMS_MOVING_AVERAGE_HPP_
#define TRANSFORMS_MOVING_AVERAGE_HPP_

#include <stddef.h>

#include <vector>

class MovingAverage {
 public:
  explicit MovingAverage(size_t sample_count);

  float update(float sample);
  void reset();

 private:
  std::vector<float> samples_;
  size_t next_index_ = 0;
  size_t valid_samples_ = 0;
  float total_ = 0.0F;
};

#endif
