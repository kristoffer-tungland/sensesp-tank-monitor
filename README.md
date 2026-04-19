# sensesp-tank-monitor

SensESP project for monitoring two freshwater tanks and bilge water state on an
ESP32-C3 Super Mini, then publishing telemetry to a Signal K server.

## Hardware

- ESP32-C3 Super Mini
- INA219 @ `0x40` (forward tank)
- INA219 @ `0x41` (port tank)
- Reed switch tank selector (GPIO input pull-up)
  - `LOW` => `forward`
  - `HIGH` => `port`
- Float switch bilge monitor (GPIO input pull-up)
  - `LOW` => water detected
  - `HIGH` => dry bilge

### ESP32-C3 pin mapping

- `GPIO8`: I2C SDA (INA219 bus)
- `GPIO9`: I2C SCL (INA219 bus)
- `GPIO2`: Reed switch (tank selector, `INPUT_PULLUP`)
- `GPIO3`: Float switch (bilge, `INPUT_PULLUP`)

## Signal K paths

- `tanks.freshWater.forward.currentLevel`
- `tanks.freshWater.port.currentLevel`
- `tanks.freshWater.selectedTank`
- `environment.bilge.waterDetected`

## Calibration

Edit `/src/config/CalibrationConfig.hpp`:

- `kEmptyCurrentForward` / `kFullCurrentForward`
- `kEmptyCurrentPort` / `kFullCurrentPort`

Level values are normalized to `0.0 .. 1.0` with clamping.

## Build

This project is configured for PlatformIO:

```ini
[env:esp32-c3-supermini]
```
