/**
 * Example code for testing HUB75 LED Matrix 16x32 with ESP32
 * Based on ESP32-HUB75-MatrixPanel-DMA library
 * https://github.com/mrcodetastic/ESP32-HUB75-MatrixPanel-DMA
 * 
 * This code runs a series of tests to verify if your HUB75 panel is working correctly:
 * 1. Basic color test - fills the entire screen with primary colors
 * 2. Text display test - shows some text in different colors
 * 3. Animation test - displays a moving dot on the screen
 * 4. All pixels test - turns on and off each pixel sequentially
 */

 #include <Arduino.h>
 #include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>
 
 // Panel configuration
 #define PANEL_RES_X 32 // Panel width (columns)
 #define PANEL_RES_Y 16 // Panel height (rows)
 #define PANEL_CHAIN 1  // Number of panels in chain (only 1 in this case)
 
 // GPIO pin definitions for HUB75
 // You can change these according to your wiring
 #define R1_PIN 25
 #define G1_PIN 26 
 #define B1_PIN 27
 #define R2_PIN 14
 #define G2_PIN 12
 #define B2_PIN 13
 #define A_PIN 23
 #define B_PIN 19
 #define C_PIN 5
 #define D_PIN 17
 #define E_PIN -1  // Not used for 16x32 panels
 #define LAT_PIN 4
 #define OE_PIN 15
 #define CLK_PIN 16
 
 // Create MatrixPanel_I2S_DMA object
 MatrixPanel_I2S_DMA *dma_display = nullptr;
 
 void setup() {
   // Initialize serial communication
   Serial.begin(115200);
   delay(1000);
   Serial.println("Initializing HUB75 16x32 panel test...");
 
   // HUB75 configuration
   HUB75_I2S_CFG mxconfig(
     PANEL_RES_X,   // panel width
     PANEL_RES_Y,   // panel height
     PANEL_CHAIN    // number of panels in chain
   );
   
   // Set GPIO pins
   mxconfig.gpio.r1 = R1_PIN;
   mxconfig.gpio.g1 = G1_PIN;
   mxconfig.gpio.b1 = B1_PIN;
   mxconfig.gpio.r2 = R2_PIN;
   mxconfig.gpio.g2 = G2_PIN;
   mxconfig.gpio.b2 = B2_PIN;
   mxconfig.gpio.a = A_PIN;
   mxconfig.gpio.b = B_PIN;
   mxconfig.gpio.c = C_PIN;
   mxconfig.gpio.d = D_PIN;
   mxconfig.gpio.e = E_PIN;
   mxconfig.gpio.lat = LAT_PIN;
   mxconfig.gpio.oe = OE_PIN;
   mxconfig.gpio.clk = CLK_PIN;
   
   // Optional settings - adjust if needed
   mxconfig.clkphase = false;
   mxconfig.driver = HUB75_I2S_CFG::FM6126A;  // You can change to ICN2038S, FM6124, or others if needed
 
   // Initialize the panel
   dma_display = new MatrixPanel_I2S_DMA(mxconfig);
   
   if (dma_display->begin() != true) {
     Serial.println("Panel not initialized properly. Check connections.");
     return;
   }
 
   Serial.println("Panel initialized successfully!");
   
   // Clear the screen on startup
   dma_display->fillScreen(dma_display->color565(0, 0, 0));
   dma_display->setCursor(0, 0);
 }
 
 // Main loop that runs through all tests
 void loop() {
   // Test 1: Basic colors
   testBasicColors();
   delay(3000);
   
   // Test 2: Text display
   testText();
   delay(3000);
   
   // Test 3: Animation
   testAnimation();
   delay(3000);
   
   // Test 4: All pixels
   testAllPixels();
   delay(3000);
 }
 
 /**
  * Test 1: Basic Colors Test
  * Fills the entire screen with basic colors (red, green, blue, white)
  * to verify that all color channels are working
  */
 void testBasicColors() {
   // Black (clear screen)
   dma_display->fillScreen(dma_display->color565(0, 0, 0));
   delay(500);
   
   // Red
   dma_display->fillScreen(dma_display->color565(255, 0, 0));
   delay(1000);
   
   // Green
   dma_display->fillScreen(dma_display->color565(0, 255, 0));
   delay(1000);
   
   // Blue
   dma_display->fillScreen(dma_display->color565(0, 0, 255));
   delay(1000);
   
   // White
   dma_display->fillScreen(dma_display->color565(255, 255, 255));
   delay(1000);
 }
 
 /**
  * Test 2: Text Display Test
  * Displays sample text in different colors
  * to verify text rendering capabilities
  */
 void testText() {
   // Display "TEST" in yellow
   dma_display->fillScreen(dma_display->color565(0, 0, 0));
   dma_display->setTextColor(dma_display->color565(255, 255, 0)); // Yellow text
   dma_display->setCursor(1, 1);
   dma_display->print("TEST");
   delay(1000);
   
   // Display "OK!" in magenta
   dma_display->fillScreen(dma_display->color565(0, 0, 0));
   dma_display->setTextColor(dma_display->color565(255, 0, 255)); // Magenta
   dma_display->setCursor(1, 8);
   dma_display->print("OK!");
   delay(1000);
 }
 
 /**
  * Test 3: Animation Test
  * Displays a moving pixel animation
  * to verify refresh rate and pixel addressing
  */
 void testAnimation() {
   dma_display->fillScreen(dma_display->color565(0, 0, 0));
   
   for (int i = 0; i < 3; i++) { // 3 repetitions
     // Horizontal pixel movement
     for (int x = 0; x < PANEL_RES_X; x++) {
       dma_display->fillScreen(dma_display->color565(0, 0, 0));
       dma_display->drawPixel(x, PANEL_RES_Y/2, dma_display->color565(0, 255, 255)); // Cyan
       delay(50);
     }
     
     // Vertical pixel movement
     for (int y = 0; y < PANEL_RES_Y; y++) {
       dma_display->fillScreen(dma_display->color565(0, 0, 0));
       dma_display->drawPixel(PANEL_RES_X/2, y, dma_display->color565(255, 165, 0)); // Orange
       delay(50);
     }
   }
 }
 
 /**
  * Test 4: All Pixels Test
  * Turns on and off each pixel one by one
  * to verify that all pixels on the panel are functional
  */
 void testAllPixels() {
   dma_display->fillScreen(dma_display->color565(0, 0, 0));
   
   // Turn on all pixels sequentially
   for (int y = 0; y < PANEL_RES_Y; y++) {
     for (int x = 0; x < PANEL_RES_X; x++) {
       dma_display->drawPixel(x, y, dma_display->color565(255, 255, 255));
       delay(10);
     }
   }
   
   // Turn off all pixels sequentially
   for (int y = 0; y < PANEL_RES_Y; y++) {
     for (int x = 0; x < PANEL_RES_X; x++) {
       dma_display->drawPixel(x, y, dma_display->color565(0, 0, 0));
       delay(10);
     }
   }
 }