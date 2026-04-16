#include <Arduino.h>

// Variables for coordinates
float userX = 0.0;
float userZ = 0.0;
float speed = 0.5; // Walking speed simulation

void setup() {
  // Initialize Serial at the same baud rate as the web app (115200)
  Serial.begin(115200);
  
  // Wait for serial port to connect
  while (!Serial) {
    delay(10);
  }
}

void loop() {
  // --- SECTION 1: YOUR SENSOR LOGIC ---
  // This is where you would normally get data from your ESP32 beacons.
  // For now, we will simulate walking in a circle to test the distance meter.
  
  static float angle = 0;
  userX = 80 * cos(angle); // Moves between -80 and 80
  userZ = 80 * sin(angle); // Moves between -80 and 80
  angle += 0.02;           // Adjust this to walk faster or slower

  // --- SECTION 2: THE "CLEAN" OUTPUT ---
  // IMPORTANT: The web app expects ONLY "X,Z"
  // Do not add "X=" or labels, or the JavaScript parseFloat will fail.
  
  Serial.print(userX);
  Serial.print(",");
  Serial.println(userZ);

  // --- SECTION 3: STABILITY ---
  // Sending data too fast (e.g., every 1ms) can crash the browser's serial buffer.
  // 50ms (20 times per second) is perfect for smooth 3D movement.
  delay(50); 
}