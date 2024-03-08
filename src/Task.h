/*!
 * @file Task.h
 *
 * This is part of Adafruit's FXOS8700 driver for the Arduino platform.  It is
 * designed specifically to work with the Adafruit FXOS8700 breakout:
 * https://www.adafruit.com/products/3463
 *
 * These sensors use I2C to communicate, 2 pins (SCL+SDA) are required
 * to interface with the breakout.
 *
 * Adafruit invests time and resources providing this open source code,
 * please support Adafruit and open-source hardware by purchasing
 * products from Adafruit!
 *
 * Written by Kevin "KTOWN" Townsend for Adafruit Industries.
 *
 * BSD license, all text here must be included in any redistribution.
 *
 */

#ifndef Task_h
#define Task_h
#include "Arduino.h"

#if defined(ARDUINO_ARCH_RP2040)
#include <FreeRTOS.h>
#include <task.h>
#endif

class Task {
public:
  // functions
  Task(String name, int stackSize, int priority);
  void createTask(void (*TaskFunction)(void*));
  void createTask(void (*TaskFunction)(void*), byte core);
  void setPriority(int priority);
  void suspendTask();
  void resumeTask();
  
#if defined(ARDUINO_ARCH_RP2040)
  void getCoreAffinity();
#endif

private:
  // data
  TaskHandle_t _taskHandle;
  String _name;
  int _stackSize;
  int _priority;
};
#endif
