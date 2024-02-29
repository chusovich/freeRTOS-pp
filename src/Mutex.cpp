#include "Arduino.h"
#include "Mutex.h"

Mutex::Mutex() {
}

bool Mutex::create() {
  _mutexHandle = xSemaphoreCreateMutex();
  if (_mutexHandle != NULL) {
    return false;
  } else {
    return true;
  }
}

bool Mutex::createStatic() {
  _mutexHandle = xSemaphoreCreateMutexStatic(&_mutexBuffer);
  if (_mutexHandle != NULL) {
    return false;
  } else {
    return true;
  }
}

void Mutex::destroy() {
  vSemaphoreDelete(_mutexHandle);
}

bool Mutex::take(int msTimeout) {
  bool status;
  if (_mutexHandle != NULL) {
    /* See if we can obtain the semaphore.  If the semaphore is not
        available wait 10 ticks to see if it becomes free. */
    if (xSemaphoreTake(_mutexHandle, (TickType_t)msTimeout) == pdTRUE) {
      status = true;
    } else {
      status = false;
    }
  }
  return status;
}

void Mutex::give() {
  xSemaphoreGive(_mutexHandle);
}