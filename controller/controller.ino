/*  IR Fan Controller
 *  By Kaden Barlow
 *
 *  Controls IR celing fan and light
 *  Reports on temperature and humidity
 */

#include <SimpleDHT.h>

const unsigned int toggleLight[] = {392, 416, 376, 412, 388, 420, 384, 416, 384, 408, 388, 416, 388, 412, 388, 408, 392, 408, 388, 416, 388, 412, 380, 5216, 780, 420, 384, 816, 788, 416, 376, 820, 780, 420, 780, 416, 384, 816, 384, 820, 376, 824, 376, 820, 380, 820, 780, 416, 384, 816, 384, 820, 376, 824, 376, 820, 780, 420, 780, 416, 780, 420, 384, 820, 784, 416, 376, 820, 380, 820, 780, 420, 380, 816, 780, 424, 776, 424, 780, 416, 780, 420, 780, 420, 380, 816, 780, 424, 380, 820, 376, 824, 376, 820, 384, 816, 384, 812, 780, 424, 380, 820, 780, 420, 780, 416, 384, 816, 384, 820, 772, 428, 772, 424, 376, 824, 376, 820, 384, 816, 384, 820, 376, 824, 376, 820, 376, 824, 376, 820, 780, 420, 780, 424, 376, 824, 376, 820, 780, 420, 780, 420, 776, 420, 780, 424, 776, 424, 780, 416, 780, 420, 780, 420, 380, 25668, 376, 416, 384, 420, 384, 416, 376, 428, 376, 424, 376, 420, 384, 416, 376, 428, 376, 424, 376, 416, 376, 432, 372, 5220, 780, 416, 380, 820, 780, 420, 380, 828, 768, 424, 776, 424, 376, 820, 380, 820, 384, 816, 380, 828, 372, 820, 776, 424, 376, 820, 380, 820, 384, 824, 372, 824, 772, 424, 784, 416, 780, 416, 380, 820, 780, 420, 380, 824, 376, 820, 784, 416, 376, 824, 776, 420, 780, 428, 772, 424, 772, 424, 784, 416, 376, 824, 780, 428, 372, 824, 376, 820, 376, 824, 376, 820, 376, 824, 780, 416, 384, 824, 772, 424, 772, 428, 376, 820, 376, 824, 780, 428, 768, 428, 376, 820, 376, 824, 376, 832, 364, 832, 372, 828, 372, 816, 384, 820, 376, 824, 776, 432, 768, 428, 372, 828, 372, 820, 776, 424, 784, 424, 772, 428, 768, 428, 772, 428, 768, 436, 764, 436, 760, 436, 368, 25676, 372, 420, 388, 412, 380, 424, 376, 420, 384, 416, 384, 420, 376, 424, 376, 416, 388, 416, 376, 428, 372, 420, 388, 5220, 768, 424, 376, 824, 784, 412, 380, 820, 780, 420, 776, 432, 372, 820, 376, 824, 376, 820, 380, 820, 376, 824, 776, 432, 372, 820, 376, 824, 376, 820, 380, 820, 780, 428, 768, 432, 768, 424, 376, 824, 780, 416, 380, 820, 384, 816, 776, 420, 384, 820, 784, 416, 780, 416, 780, 432, 768, 428, 772, 424, 376, 820, 784, 416, 376, 832, 368, 832, 372, 824, 372, 824, 376, 820, 784, 416, 376, 832, 768, 432, 768, 428, 372, 824, 376, 820, 780, 432, 768, 428, 368, 832, 372, 824, 376, 820, 376, 820, 380, 820, 376, 832, 368, 832, 372, 824, 772, 424, 772, 428, 376, 832, 364, 832, 772, 428, 768, 420, 780, 424, 772, 436, 772, 428, 768, 428, 772, 428, 768, 424, 380};
const unsigned int toggleFan[] = {380, 416, 388, 408, 392, 408, 392, 412, 384, 416, 388, 412, 388, 408, 384, 420, 380, 420, 376, 416, 388, 412, 388, 5208, 792, 408, 392, 816, 780, 420, 384, 808, 784, 416, 788, 412, 384, 824, 372, 824, 384, 812, 388, 808, 388, 812, 792, 416, 376, 824, 372, 824, 384, 812, 388, 808, 784, 428, 780, 416, 780, 420, 384, 812, 780, 416, 388, 820, 376, 824, 780, 416, 376, 824, 780, 416, 780, 428, 772, 412, 780, 432, 780, 416, 376, 824, 780, 416, 384, 824, 376, 820, 376, 824, 376, 820, 376, 824, 780, 420, 380, 824, 772, 424, 772, 428, 376, 820, 376, 824, 384, 820, 376, 824, 376, 820, 376, 824, 780, 416, 384, 816, 384, 820, 376, 824, 772, 424, 780, 420, 780, 416, 780, 420, 780, 424, 772, 428, 780, 416, 780, 420, 376, 820, 780, 420, 780, 424, 776, 424, 376, 820, 380, 820, 376, 25672, 376, 420, 384, 416, 380, 424, 376, 416, 384, 420, 372, 432, 372, 416, 380, 424, 376, 424, 376, 432, 372, 420, 380, 5220, 776, 424, 376, 820, 780, 420, 376, 824, 780, 416, 780, 424, 380, 820, 376, 824, 376, 820, 372, 828, 384, 812, 780, 424, 380, 820, 376, 824, 376, 820, 372, 828, 780, 424, 772, 428, 772, 424, 376, 824, 780, 416, 372, 828, 384, 820, 772, 428, 376, 820, 780, 420, 780, 416, 780, 428, 772, 424, 772, 428, 376, 820, 780, 420, 376, 820, 384, 824, 376, 820, 376, 824, 376, 820, 780, 420, 376, 820, 780, 432, 768, 424, 376, 824, 376, 820, 376, 824, 364, 832, 384, 828, 372, 820, 772, 428, 376, 820, 376, 824, 384, 824, 768, 428, 772, 424, 772, 428, 780, 416, 780, 428, 772, 428, 768, 428, 772, 424, 376, 824, 780, 416, 780, 432, 768, 428, 372, 824, 376, 820, 380, 25664, 372, 432, 376, 424, 376, 424, 380, 416, 372, 432, 376, 424, 376, 424, 368, 428, 376, 428, 372, 428, 368, 424, 376, 5220, 780, 428, 372, 824, 772, 424, 380, 820, 780, 420, 776, 420, 384, 824, 372, 824, 376, 820, 380, 820, 376, 832, 772, 428, 372, 824, 376, 820, 376, 824, 376, 820, 780, 420, 780, 428, 768, 428, 376, 820, 772, 428, 376, 820, 376, 832, 772, 428, 372, 820, 776, 424, 772, 428, 780, 416, 780, 428, 772, 428, 372, 824, 772, 424, 376, 824, 376, 820, 380, 832, 372, 824, 372, 824, 772, 424, 376, 824, 780, 428, 768, 432, 372, 824, 372, 824, 376, 820, 380, 832, 364, 832, 368, 832, 768, 428, 372, 824, 376, 820, 380, 820, 780, 428, 768, 432, 768, 428, 772, 424, 772, 424, 780, 432, 768, 428, 772, 428, 372, 832, 764, 424, 772, 436, 768, 432, 364, 832, 372, 828, 372};
const unsigned int increaseSpeed[] = {388, 416, 388, 416, 388, 404, 384, 420, 384, 416, 384, 408, 388, 416, 388, 416, 384, 408, 392, 412, 384, 416, 388, 5208, 792, 408, 380, 824, 784, 412, 380, 820, 780, 416, 780, 420, 384, 816, 380, 824, 376, 820, 380, 820, 376, 824, 776, 432, 372, 820, 376, 824, 376, 820, 380, 820, 780, 420, 776, 432, 768, 424, 376, 824, 784, 412, 380, 820, 376, 832, 772, 428, 372, 820, 776, 424, 772, 436, 768, 420, 780, 428, 772, 428, 372, 820, 776, 424, 376, 824, 376, 832, 364, 832, 376, 824, 372, 824, 772, 424, 376, 832, 772, 428, 768, 432, 372, 824, 372, 824, 772, 424, 376, 824, 376, 832, 372, 828, 372, 820, 376, 824, 376, 820, 376, 832, 368, 832, 768, 432, 768, 436, 760, 436, 368, 832, 768, 428, 772, 428, 768, 432, 768, 424, 772, 436, 764, 436, 768, 428, 772, 428, 372, 828, 372, 25676, 364, 428, 376, 428, 372, 420, 384, 416, 380, 424, 376, 424, 376, 420, 372, 432, 376, 424, 376, 424, 368, 428, 372, 5232, 768, 432, 364, 832, 768, 432, 372, 820, 776, 432, 772, 428, 368, 832, 364, 832, 372, 828, 372, 832, 364, 832, 772, 428, 368, 832, 372, 824, 372, 828, 372, 832, 764, 436, 768, 428, 768, 432, 372, 824, 772, 432, 368, 832, 368, 832, 768, 428, 368, 832, 768, 428, 772, 432, 764, 436, 764, 436, 768, 428, 368, 832, 768, 428, 376, 828, 368, 832, 368, 832, 364, 832, 368, 832, 768, 428, 376, 832, 760, 436, 768, 432, 364, 832, 368, 832, 768, 428, 376, 832, 364, 832, 368, 832, 376, 820, 372, 828, 372, 824, 376, 832, 364, 832, 772, 428, 768, 428, 772, 428, 372, 832, 764, 436, 772, 424, 772, 428, 768, 428, 772, 428, 768, 436, 772, 428, 772, 424, 368, 832, 364, 25680, 372, 428, 376, 416, 376, 428, 376, 424, 376, 420, 384, 416, 384, 420, 376, 424, 376, 428, 376, 420, 372, 428, 376, 5216, 784, 424, 368, 832, 768, 428, 380, 820, 768, 428, 780, 428, 364, 832, 368, 832, 364, 832, 380, 820, 372, 828, 776, 428, 364, 832, 376, 824, 364, 832, 380, 820, 780, 420, 776, 428, 772, 424, 368, 832, 768, 428, 376, 824, 372, 828, 768, 436, 364, 832, 772, 428, 768, 428, 772, 428, 780, 424, 776, 424, 376, 820, 772, 428, 376, 820, 376, 824, 372, 832, 368, 832, 376, 820, 772, 428, 376, 820, 772, 428, 768, 436, 368, 832, 364, 832, 772, 428, 376, 824, 372, 824, 372, 832, 368, 832, 376, 820, 380, 820, 376, 824, 372, 824, 780, 424, 776, 424, 768, 428, 380, 820, 768, 432, 768, 428, 780, 424, 776, 424, 768, 428, 772, 428, 768, 432, 780, 424, 364, 832, 368};
const unsigned int decreaseSpeed[] = {384, 416, 384, 408, 396, 408, 384, 416, 388, 416, 384, 408, 396, 408, 388, 412, 388, 416, 384, 412, 380, 420, 384, 5208, 784, 416, 388, 820, 780, 416, 384, 816, 780, 416, 784, 412, 388, 820, 380, 820, 376, 824, 380, 816, 384, 812, 784, 424, 376, 820, 380, 820, 376, 824, 380, 816, 780, 424, 776, 424, 768, 428, 380, 820, 780, 420, 380, 816, 384, 820, 776, 424, 376, 824, 780, 416, 780, 420, 780, 416, 780, 428, 772, 424, 376, 824, 780, 416, 372, 828, 384, 820, 376, 824, 376, 820, 376, 824, 780, 416, 376, 824, 780, 424, 772, 428, 376, 820, 376, 824, 780, 416, 376, 824, 384, 820, 376, 824, 376, 820, 376, 824, 376, 820, 376, 824, 780, 424, 376, 824, 780, 416, 780, 420, 376, 820, 780, 420, 780, 424, 776, 424, 768, 428, 780, 420, 780, 420, 776, 420, 384, 820, 776, 424, 376, 25668, 384, 416, 376, 428, 376, 424, 368, 428, 372, 428, 376, 416, 376, 428, 376, 436, 364, 428, 376, 416, 380, 424, 376, 5220, 780, 420, 372, 832, 772, 424, 380, 820, 768, 432, 776, 420, 372, 832, 376, 824, 376, 820, 380, 820, 376, 824, 780, 416, 372, 832, 380, 820, 376, 820, 380, 820, 780, 420, 780, 416, 780, 424, 380, 820, 772, 424, 380, 820, 376, 824, 780, 416, 384, 820, 776, 424, 768, 428, 772, 428, 780, 420, 780, 428, 360, 832, 776, 424, 376, 820, 380, 820, 376, 824, 372, 836, 372, 820, 776, 424, 376, 824, 780, 416, 780, 420, 372, 824, 372, 832, 776, 424, 376, 824, 376, 820, 372, 828, 372, 832, 376, 824, 376, 820, 376, 824, 780, 416, 376, 836, 768, 424, 772, 428, 376, 820, 780, 420, 780, 428, 768, 432, 768, 424, 776, 424, 768, 428, 772, 428, 376, 832, 768, 420, 384, 25664, 380, 424, 376, 420, 372, 428, 372, 432, 376, 424, 368, 424, 376, 428, 372, 432, 364, 428, 376, 424, 376, 428, 376, 5220, 768, 428, 380, 820, 780, 420, 380, 824, 772, 424, 772, 428, 376, 824, 380, 816, 372, 828, 372, 832, 376, 820, 772, 428, 376, 824, 372, 824, 372, 832, 368, 832, 772, 424, 772, 428, 768, 432, 372, 824, 780, 424, 380, 820, 376, 820, 772, 428, 376, 824, 780, 416, 780, 424, 776, 424, 772, 424, 772, 428, 376, 832, 772, 416, 372, 832, 380, 820, 376, 820, 380, 820, 376, 824, 780, 416, 384, 820, 776, 424, 768, 428, 380, 820, 376, 824, 780, 428, 372, 820, 380, 820, 376, 824, 376, 820, 372, 828, 384, 812, 384, 820, 776, 424, 376, 824, 780, 428, 768, 428, 376, 820, 772, 424, 776, 424, 768, 440, 772, 428, 768, 428, 772, 424, 772, 424, 380, 820, 780, 420, 376};

// dht11 is the temperature / humidity sensor
const int pinDHT11 = 2;
SimpleDHT11 dht11(pinDHT11);

// Incoming serial data
int incomingByte = 0;

// RF modules
int pinRFTransmitter = 12;

void setup() {
  Serial.begin(9600);
  pinMode(pinRFTransmitter, OUTPUT);
  digitalWrite(pinRFTransmitter, LOW);
}

void checkSensors() {
  byte temperatureC = 0;
  byte humidity = 0;

  float temperatureF = 0.0;

  int err = SimpleDHTErrSuccess;
  if (err = dht11.read(&temperatureC, &humidity, NULL) != SimpleDHTErrSuccess) {
    // Serial.print("Read DHT11 failed\n");
    // For now just don't report the new values on this iteration
    return;
  }

  temperatureF = (float)temperatureC * 9.0/5.0 + 32.0; // °F = °C x 9/5 + 32.
  Serial.print("{ \"type\": \"update\"");
  Serial.print(", \"temperature\": "); Serial.print(temperatureF);
  Serial.print(", \"humidity\": "); Serial.print((float)humidity);
  Serial.print(" }\n");
}

void transmit(unsigned int* command) {
  int state = 0;
  for (int x = 0; x < sizeof(command)/sizeof(command[0]); ++x) {
    state = !state;
    digitalWrite(12, state);
    delayMicroseconds(command[x]);
  }
  digitalWrite(12, LOW);
}

void serverCommands() {
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    switch (incomingByte) {
    case 'l': // toggle light
      transmit(toggleLight);
      break;
    case 'f': // toggle fan
      transmit(toggleFan);
      break;
    case 'S': // increase fan speed
      transmit(increaseSpeed);
      break;
    case 's': // decrease fan speed
      transmit(decreaseSpeed);
      break;
    }
  }
}

void loop() {
  serverCommands();
  checkSensors();
  delay(1000);
}
