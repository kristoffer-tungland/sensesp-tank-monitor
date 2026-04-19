#ifndef TRANSFORMS_LINEAR_CALIBRATION_HPP_
#define TRANSFORMS_LINEAR_CALIBRATION_HPP_

class LinearCalibration {
 public:
  static float map_current_to_level(float current_ma, float empty_current_ma,
                                    float full_current_ma);
};

#endif
