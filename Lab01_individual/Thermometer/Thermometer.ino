#include "Wire.h" // This library allows you to communicate with I2C devices.
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

const int MPU_ADDR = 0x68; // I2C address of the MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69.
int16_t accelerometer_x, accelerometer_y, accelerometer_z; // variables for accelerometer raw data
int16_t gyro_x, gyro_y, gyro_z; // variables for gyro raw data
int16_t temperature; // variables for temperature data
char tmp_str[7]; // temporary variable used in convert function

#define PIN 11
#define NUMPIXELS 12
#define START_TEMP 2400
#define END_TEMP 3800

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

char* convert_int16_to_str(int16_t i) { 
  // converts int16 to string. Moreover, resulting strings will have the same length in the debug monitor.
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
}
void setup() {
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR); // Begins a transmission to the I2C slave (GY-521 board)
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0); // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
}

int read(){
  // Wire.read()<<8 | Wire.read() means two registers are read and stored in the same variable
  return Wire.read()<<8 | Wire.read();
}

void loop() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
  Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
  Wire.requestFrom(MPU_ADDR, 7*2, true); // request a total of 7*2=14 registers
  
  read(); read(); read(); // reads for other measurements
  temperature = (Wire.read()<<8 | Wire.read()); // reading registers: 0x41 (TEMP_OUT_H) and 0x42 (TEMP_OUT_L)
  read(); read(); read(); // reads for other measurements
  
  // the following equation was taken from the documentation [MPU-6000/MPU-6050 Register Map and Description, p.30]
  Serial.print("Temperature = "); Serial.print(temperature/ 340.00+36.53); Serial.print(" °C"); Serial.println();
  int temp = (temperature / 340.00+36.53)*100;

  int howManyPixels = map(temp,START_TEMP,END_TEMP,1,NUMPIXELS);

  pixels.clear();
  for(int i=0; i<howManyPixels; i++) { // For each pixel...
    pixels.setPixelColor(i, pixels.Color(0, 0, 10));
    pixels.show();   // Send the updated pixel colors to the hardware.
  }

  delay(1000);
}
