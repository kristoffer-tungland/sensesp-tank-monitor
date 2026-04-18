#include "transforms/MovingAverage.hpp"

MovingAverage::MovingAverage(size_t sample_count)
    : samples_(sample_count > 0 ? sample_count : 1, 0.0F) {}

float MovingAverage::update(float sample) {
  total_ -= samples_[next_index_];
  samples_[next_index_] = sample;
  total_ += sample;

  next_index_ = (next_index_ + 1) % samples_.size();
  if (valid_samples_ < samples_.size()) {
    ++valid_samples_;
  }

  return total_ / static_cast<float>(valid_samples_);
}

void MovingAverage::reset() {
  for (size_t i = 0; i < samples_.size(); i++) {
    samples_[i] = 0.0F;
  }
  next_index_ = 0;
  valid_samples_ = 0;
  total_ = 0.0F;
}
