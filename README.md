# ESP32 HUB75 16x32 LED Matrix Test

This project provides a simple test code for HUB75 16x32 LED Matrix panels using ESP32. It's based on the ESP32-HUB75-MatrixPanel-DMA library by mrcodetastic.

## Project Structure
```
ESP32-HUB75-Test/
├── platformio.ini             # PlatformIO configuration
├── src/
│   └── main.cpp               # Main test code
└── README.md                  # This file
```

## Hardware Requirements
- ESP32 board (ESP32 DevKit, NodeMCU-ESP32, WEMOS LOLIN32, etc.)
- HUB75 16x32 LED Matrix panel
- Jumper wires
- 5V power supply (capable of providing sufficient current for your panel)

## Hardware Connection

Default pin configuration in the code:

| HUB75 Signal | ESP32 Pin |
|--------------|-----------|
| R1           | GPIO 25   |
| G1           | GPIO 26   |
| B1           | GPIO 27   |
| R2           | GPIO 14   |
| G2           | GPIO 12   |
| B2           | GPIO 13   |
| A            | GPIO 23   |
| B            | GPIO 19   |
| C            | GPIO 5    |
| D            | GPIO 17   |
| E            | -1 (not used) |
| LAT/STB      | GPIO 4    |
| OE           | GPIO 15   |
| CLK          | GPIO 16   |

**IMPORTANT**: You can customize the pins in the `main.cpp` file according to your specific wiring requirements.

## Installation and Setup

### Option 1: Using Arduino IDE
1. Install [Arduino IDE](https://www.arduino.cc/en/software)
2. Set up ESP32 support:
   - Open Arduino IDE
   - Go to File > Preferences
   - Add `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json` to Additional Boards Manager URLs
   - Go to Tools > Board > Boards Manager...
   - Search for "esp32" and install the "ESP32" package
3. Install ESP32-HUB75-MatrixPanel-DMA library:
   - Go to Sketch > Include Library > Manage Libraries...
   - Search for "ESP32 HUB75 LED MATRIX PANEL DMA Display" and install
4. Copy the code from `main.cpp` to a new sketch
5. Select your ESP32 board from Tools > Board
6. Connect your ESP32 to your computer and select the correct port
7. Compile and upload the code

### Option 2: Using PlatformIO
1. Install [Visual Studio Code](https://code.visualstudio.com/)
2. Install the PlatformIO extension
3. Create a new PlatformIO project:
   - Select "ESP32 Dev Module" as the board
   - Select "Arduino" as the framework
4. Replace the default `platformio.ini` with the one from this project
5. Create a `src/main.cpp` file and paste the code
6. Connect your ESP32 to your computer
7. Click the "Build" button and then "Upload"

## What This Test Code Does

The code runs a series of tests to verify that your panel is working correctly:

1. **Basic Color Test** - Fills the entire screen with red, green, blue, and white colors
2. **Text Display Test** - Shows "TEST" and then "OK!" in different colors
3. **Animation Test** - Displays a moving dot on the screen
4. **All Pixels Test** - Turns on and off each pixel on the panel sequentially

## Troubleshooting

### Panel Shows Nothing
- Check the connections between ESP32 and the panel
- Ensure the panel has adequate power
- Verify you've selected the correct driver in the code

### Colors Are Incorrect
- Check the R1, G1, B1, R2, G2, B2 pin connections
- The panel might use a different driver - try other options in the code

### Image Is Distorted
- Check the A, B, C, D pin connections
- Make sure you've set the correct panel dimensions (16x32)

### Image Flickers
- You may need to adjust the refresh parameters - check the library documentation

## Next Steps

After successfully testing your panel, you can:
1. Expand the code with more advanced features
2. Integrate the panel into your project
3. Create your own fork of the library with additional functionality

## Advanced Examples

If you're looking to do more with your panel, consider checking these examples:

### Scrolling Text
```cpp
void scrollText(const char *text, uint16_t color) {
    int textWidth = strlen(text) * 6; // Approximate width of text
    for (int x = PANEL_RES_X; x > -textWidth; x--) {
        dma_display->fillScreen(0);
        dma_display->setCursor(x, 4);
        dma_display->setTextColor(color);
        dma_display->print(text);
        delay(50);
    }
}
```

### Drawing Shapes
```cpp
void drawShapes() {
    dma_display->fillScreen(0);
    // Draw a circle
    dma_display->drawCircle(16, 8, 7, dma_display->color565(255, 0, 0));
    delay(1000);
    
    dma_display->fillScreen(0);
    // Draw a rectangle
    dma_display->drawRect(5, 3, 22, 10, dma_display->color565(0, 255, 0));
    delay(1000);
    
    dma_display->fillScreen(0);
    // Draw a line
    dma_display->drawLine(0, 0, 31, 15, dma_display->color565(0, 0, 255));
    delay(1000);
}
```
