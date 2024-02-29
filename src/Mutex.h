#ifndef Mutex_h
#define Mutex_h
#include "Arduino.h"

#if defined(ARDUINO_ARCH_RP2040)
#include <FreeRTOS.h>
#include <semphr.h>
#endif

class Mutex {
public:
  // functions
  Mutex();
  bool create();
  bool createStatic();
  void destroy();
  bool take(int msTimeout);
  void give();
  // data

private:
  // data
  SemaphoreHandle_t _mutexHandle;
  static StaticSemaphore_t _mutexBuffer;
};
#endif