#include <Arduino.h>
// This example code is in the Public Domain (or CC0 licensed, at your option.)
// By Evandro Copercini - 2018
//
// This example creates a bridge between Serial and Classical Bluetooth (SPP)
// and also demonstrate that SerialBT have the same functionalities of a normal Serial

#include "BluetoothSerial.h"
#include "DCMDriverL298.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif

BluetoothSerial SerialBT;

char cmd;
int speed = 255;

int dirA = 1;
int dirB = 1;

// LEFT MOTOR CONTROL PINS
#define ENA 27
#define IN1 14
#define IN2 12

// RIGHT MOTOR CONTROL PINS
#define ENB 33
#define IN3 26
#define IN4 25

DCMDriverL298 Motors(ENA, IN1, IN2, ENB, IN3, IN4);

void Left()
{
  speed = 200;
  dirA = 0;
  dirB = 1;
}

void Right()
{
  speed = 200;
  dirA = 1;
  dirB = 0;
}
void Forward()
{
  speed = 255;
  dirA = 1;
  dirB = 1;
}

void Backward()
{
  speed = 255;
  dirA = 0;
  dirB = 0;
}

void Start()
{
  speed = 255;
  for (int i = 0; i < 255; i++)
  {
    speed = i;
    delay(2);
  }
}

void Stop()
{
  speed = 0;
}

void setup()
{
  Serial.begin(115255);
  SerialBT.begin("ESP32test"); // Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop()
{
  if (SerialBT.available())
  {
    cmd = SerialBT.read();
  }

  switch (cmd)
  {
  case 'f':
    Serial.println("Forward");
    Forward();
    break;

  case 'b':
    Serial.println("Backward");
    Backward();
    break;

  case 'l':
    Serial.println("Left");
    Left();
    break;

  case 'r':
    Serial.println("Right");
    Right();
    break;

  case 's':
    Serial.println("Start");
    Start();
    break;

  case 't':
    Serial.println("Stop");
    Stop();
    break;

  default:
    break;
  }

  Motors.setMotorA(speed, dirA);
  Motors.setMotorB(speed, dirB);
}