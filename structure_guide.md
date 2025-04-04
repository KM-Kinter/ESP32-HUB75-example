# ESP32 HUB75 Project Structure Guide

This guide explains the complete project structure for testing and using HUB75 LED Matrix panels with ESP32.

## Complete Project Structure

```
ESP32-HUB75-Test/
├── platformio.ini                 # PlatformIO configuration
├── src/
│   ├── main.cpp                   # Main program (basic test code)
│   └── advanced_examples.cpp      # Advanced examples (optional)
├── include/                       # Header files directory
│   └── config.h                   # Configuration header (optional)
└── README.md                      # Project documentation
```

## Files Explanation

### 1. `platformio.ini`
This file contains the configuration for PlatformIO, including:
- Board specification (ESP32)
- Framework (Arduino)
- Library dependencies (ESP32-HUB75-MatrixPanel-DMA)
- Build and upload settings

### 2. `src/main.cpp`
The main program file with the basic test code for HUB75 panels. This file includes:
- Library imports
- Pin configuration
- Panel initialization
- Test functions (colors, text, animation, pixel test)

### 3. `src/advanced_examples.cpp` (Optional)
Contains more advanced examples for using HUB75 panels:
- Scrolling text
- Drawing shapes
- Color gradients
- Clock display
- Animations

### 4. `include/config.h` (Optional)
A header file for centralized configuration:
```cpp
// Example config.h content
#ifndef CONFIG_H
#define CONFIG_H

// Panel configuration
#define PANEL_RES_X 32
#define PANEL_RES_Y 16
#define PANEL_CHAIN 1

// Pin definitions
#define R1_PIN