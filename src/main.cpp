// UP: z   8.01  enabled 1  raw 1945 -> duty 121
// SIDEWAYS: z  -0.63  enabled 0  raw 4095 -> duty   0
// DOWN: z -11.29  enabled 0  raw 4095 -> duty   0

#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include <Wire.h>

#define POT_PIN 4
#define LED_PIN 40
#define TILT_THRESHOLD 5.0f   // m/s^2 on Z; above this counts as "up" -> enabled

Adafruit_MPU6050 mpu;

void setup() {
  Serial.begin(115200);
  delay(300);
  pinMode(LED_PIN, OUTPUT);

  Wire.begin(8, 9);
  if (!mpu.begin()) {
    Serial.println("MPU-6050 not found.  Run the I2C scanner first.");
    while (true) delay(1000);
  }
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);

  Serial.println();
  Serial.println("Tilt up to enable, knob to dim");
}

void loop() {
  sensors_event_t a, g, t;
  mpu.getEvent(&a, &g, &t);            // acceleration in m/s^2

  bool enabled = a.acceleration.z > TILT_THRESHOLD;

  int raw  = analogRead(POT_PIN);      // 0 .. 4095
  int duty = raw / 16;                 // 0 .. 255
  if (duty > 255) duty = 255;          // guard the top end of the range

  int output = enabled ? duty : 0;     // knob has zero effect while disabled
  analogWrite(LED_PIN, output);

  Serial.printf("z %6.2f  enabled %d  raw %4d -> duty %3d\n",
                a.acceleration.z, enabled, raw, output);

  delay(50);
}