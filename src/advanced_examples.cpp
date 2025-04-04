/**
 * Advanced Examples for HUB75 16x32 LED Matrix with ESP32
 * Based on ESP32-HUB75-MatrixPanel-DMA library
 * https://github.com/mrcodetastic/ESP32-HUB75-MatrixPanel-DMA
 * 
 * This file contains more advanced examples that you can use
 * after confirming your panel works with the basic test.
 */

 #include <Arduino.h>
 #include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>
 
 // Panel configuration
 #define PANEL_RES_X 32 // Panel width (columns)
 #define PANEL_RES_Y 16 // Panel height (rows)
 #define PANEL_CHAIN 1  // Number of panels in chain
 
 // GPIO pin definitions for HUB75 - same as in the basic test
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
 
 MatrixPanel_I2S_DMA *dma_display = nullptr;
 
 void setup() {
   Serial.begin(115200);
   delay(1000);
   Serial.println("Initializing HUB75 16x32 panel advanced examples...");
 
   // HUB75 configuration (same as basic test)
   HUB75_I2S_CFG mxconfig(
     PANEL_RES_X,
     PANEL_RES_Y,
     PANEL_CHAIN
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
   
   mxconfig.clkphase = false;
   mxconfig.driver = HUB75_I2S_CFG::FM6126A;
 
   // Initialize the panel
   dma_display = new MatrixPanel_I2S_DMA(mxconfig);
   
   if (dma_display->begin() != true) {
     Serial.println("Panel not initialized properly. Check connections.");
     return;
   }
 
   Serial.println("Panel initialized successfully!");
   dma_display->fillScreen(dma_display->color565(0, 0, 0));
 }
 
 void loop() {
   // Example 1: Scrolling text
   scrollText("HELLO WORLD!", dma_display->color565(255, 255, 0));
   delay(1000);
   
   // Example 2: Drawing shapes
   drawShapes();
   delay(1000);
   
   // Example 3: Color gradient
   drawGradient();
   delay(2000);
   
   // Example 4: Simple clock (for demo, not accurate timekeeping)
   displayClock();
   delay(2000);
   
   // Example 5: Bouncing ball animation
   bouncingBall(3000); // Run for 3 seconds
   delay(1000);
 }
 
 /**
  * Example 1: Scrolling Text
  * Displays text that scrolls from right to left
  */
 void scrollText(const char *text, uint16_t color) {
   int textWidth = strlen(text) * 6; // Approximate width of text
   
   // Scroll from right to left
   for (int x = PANEL_RES_X; x > -textWidth; x--) {
     dma_display->fillScreen(0);
     dma_display->setCursor(x, 4);
     dma_display->setTextColor(color);
     dma_display->print(text);
     delay(50);
   }
 }
 
 /**
  * Example 2: Drawing Shapes
  * Demonstrates drawing various shapes on the panel
  */
 void drawShapes() {
   // Draw a circle
   dma_display->fillScreen(0);
   dma_display->drawCircle(16, 8, 7, dma_display->color565(255, 0, 0));
   delay(1000);
   
   // Draw a filled circle
   dma_display->fillScreen(0);
   dma_display->fillCircle(16, 8, 5, dma_display->color565(0, 255, 0));
   delay(1000);
   
   // Draw a rectangle
   dma_display->fillScreen(0);
   dma_display->drawRect(5, 3, 22, 10, dma_display->color565(0, 0, 255));
   delay(1000);
   
   // Draw a filled rectangle
   dma_display->fillScreen(0);
   dma_display->fillRect(8, 4, 16, 8, dma_display->color565(255, 0, 255));
   delay(1000);
   
   // Draw a line
   dma_display->fillScreen(0);
   dma_display->drawLine(0, 0, 31, 15, dma_display->color565(255, 255, 0));
   delay(1000);
   
   // Draw a triangle
   dma_display->fillScreen(0);
   dma_display->drawTriangle(16, 1, 30, 15, 2, 15, dma_display->color565(0, 255, 255));
   delay(1000);
 }
 
 /**
  * Example 3: Color Gradient
  * Creates a beautiful color gradient across the panel
  */
 void drawGradient() {
   dma_display->fillScreen(0);
   
   // Draw horizontal gradient
   for (int x = 0; x < PANEL_RES_X; x++) {
     uint8_t red = map(x, 0, PANEL_RES_X-1, 0, 255);
     uint8_t green = map(x, 0, PANEL_RES_X-1, 255, 0);
     uint8_t blue = 128;
     
     for (int y = 0; y < PANEL_RES_Y; y++) {
       dma_display->drawPixel(x, y, dma_display->color565(red, green, blue));
     }
   }
   delay(1500);
   
   // Draw vertical gradient
   for (int y = 0; y < PANEL_RES_Y; y++) {
     uint8_t red = 128;
     uint8_t green = map(y, 0, PANEL_RES_Y-1, 0, 255);
     uint8_t blue = map(y, 0, PANEL_RES_Y-1, 255, 0);
     
     for (int x = 0; x < PANEL_RES_X; x++) {
       dma_display->drawPixel(x, y, dma_display->color565(red, green, blue));
     }
   }
   delay(1500);
   
   // Draw radial gradient
   int centerX = PANEL_RES_X / 2;
   int centerY = PANEL_RES_Y / 2;
   int maxRadius = sqrt(centerX*centerX + centerY*centerY);
   
   for (int y = 0; y < PANEL_RES_Y; y++) {
     for (int x = 0; x < PANEL_RES_X; x++) {
       int dx = x - centerX;
       int dy = y - centerY;
       int distance = sqrt(dx*dx + dy*dy);
       
       uint8_t red = map(distance, 0, maxRadius, 255, 0);
       uint8_t green = map(distance, 0, maxRadius, 0, 255);
       uint8_t blue = map(distance, 0, maxRadius, 0, 255);
       
       dma_display->drawPixel(x, y, dma_display->color565(red, green, blue));
     }
   }
 }
 
 /**
  * Example 4: Simple Clock Display
  * Shows a simple digital clock (for demo purposes only)
  */
 void displayClock() {
   // This is just a demo - in a real app, you'd use actual time functions
   static int hour = 12;
   static int minute = 34;
   
   dma_display->fillScreen(0);
   dma_display->setTextColor(dma_display->color565(255, 255, 255));
   
   // Format time as HH:MM
   char timeStr[6];
   sprintf(timeStr, "%02d:%02d", hour, minute);
   
   // Center text on display
   int16_t x1, y1;
   uint16_t w, h;
   dma_display->getTextBounds(timeStr, 0, 0, &x1, &y1, &w, &h);
   int x = (PANEL_RES_X - w) / 2;
   int y = (PANEL_RES_Y - h) / 2;
   
   dma_display->setCursor(x, y);
   dma_display->print(timeStr);
   
   // Increment minute for next display
   minute = (minute + 1) % 60;
   if (minute == 0) {
     hour = (hour + 1) % 24;
   }
 }
 
 /**
  * Example 5: Bouncing Ball Animation
  * Animates a ball bouncing around the screen
  * 
  * @param duration Duration to run the animation in milliseconds
  */
 void bouncingBall(unsigned long duration) {
   int x = 5;             // Initial X position
   int y = 5;             // Initial Y position
   int radius = 2;        // Ball radius
   int xSpeed = 1;        // X direction speed
   int ySpeed = 1;        // Y direction speed
   int ballColor = dma_display->color565(0, 255, 0); // Green ball
   
   unsigned long startTime = millis();
   unsigned long currentTime = startTime;
   
   while (currentTime - startTime < duration) {
     // Clear screen
     dma_display->fillScreen(0);
     
     // Draw the ball
     dma_display->fillCircle(x, y, radius, ballColor);
     
     // Update position
     x += xSpeed;
     y += ySpeed;
     
     // Check for collisions with walls
     if (x <= radius || x >= PANEL_RES_X - radius - 1) {
       xSpeed = -xSpeed;
       // Change color on horizontal bounce
       ballColor = dma_display->color565(random(128, 255), random(128, 255), random(128, 255));
     }
     if (y <= radius || y >= PANEL_RES_Y - radius - 1) {
       ySpeed = -ySpeed;
       // Change color on vertical bounce
       ballColor = dma_display->color565(random(128, 255), random(128, 255), random(128, 255));
     }
     
     // Short delay for animation speed
     delay(50);
     
     // Update current time
     currentTime = millis();
   }
 }