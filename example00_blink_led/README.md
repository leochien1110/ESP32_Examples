# ESP32 Variable Frequency LED Blinker

A simple ESP32 project that demonstrates GPIO control, button input handling, and non-blocking timing using PlatformIO.

## Features

- **Variable Frequency LED Blinking**: Cycle through 5 different blink frequencies
- **Button Control**: Interactive frequency switching and reset functionality
- **Non-blocking Implementation**: Uses `millis()` for timing without delays
- **Serial Monitoring**: Real-time frequency feedback via serial output

## Hardware Requirements

- ESP32 development board (Node32s or compatible)
- LED (optional - built-in LED on GPIO 2 is used)
- Current limiting resistor (if using external LED)
- USB cable for programming and power

## Pin Configuration

| Component | GPIO Pin | Notes |
|-----------|----------|-------|
| LED | GPIO 2 | Built-in LED on most ESP32 boards |
| Button | GPIO 0 | Uses internal pull-up resistor |

## Functionality

The project implements 5 different blink frequencies:

| Frequency | Half-Period (ms) | Description |
|-----------|------------------|-------------|
| 1 Hz | 500 | Default frequency |
| 2 Hz | 250 | Double speed |
| 5 Hz | 100 | Fast blink |
| 10 Hz | 50 | Very fast blink |
| 15 Hz | 33 | Rapid blink |

### Button Controls

- **Short Press** (< 1 second): Cycle to next frequency
- **Long Press** (≥ 1 second): Reset to 1 Hz (default frequency)

## Getting Started

### Prerequisites

- [PlatformIO](https://platformio.org/) installed
- USB driver for ESP32 (usually automatic)

### Installation & Upload

1. Clone or download this project
2. Open the project in PlatformIO (VS Code or CLI)
3. Connect your ESP32 board via USB
4. Build and upload:
   ```bash
   pio run --target upload
   ```

### Serial Monitor

To view frequency changes and debug output:
```bash
pio device monitor --baud 115200
```

Expected output:
```
Starting LED blink at 1.00 Hz. Short press IO0 to cycle, long press(>1s) to reset.
Switched to 2.00 Hz
Switched to 5.00 Hz
Reset Triggered!
Switched to 1.00 Hz
```

## Code Structure

- **Non-blocking LED control**: Uses `millis()` timing instead of `delay()`
- **Debounced button input**: Proper press/release detection
- **State management**: Tracks current frequency index and timing
- **Serial feedback**: Provides user interaction confirmation

## Configuration

The blink frequencies can be modified by changing the `freqDelays[]` array in `main.cpp`:

```cpp
int freqDelays[] = {500, 250, 100, 50, 33};  // Half-periods in milliseconds
```

## Troubleshooting

### LED not blinking
- Check GPIO 2 connection if using external LED
- Verify power supply to ESP32
- Check serial output for error messages

### Button not responding
- GPIO 0 is also used for boot mode - ensure proper connection
- Try different button or check wiring
- Monitor serial output for button press detection

### Upload issues
- Put ESP32 in download mode (hold BOOT button during upload)
- Check USB cable and port selection
- Verify board configuration in `platformio.ini`

## License

This project is open source and available under the MIT License.

## Contributing

Feel free to submit issues, fork the repository, and create pull requests for any improvements.
