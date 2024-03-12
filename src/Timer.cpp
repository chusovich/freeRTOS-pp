#include "Timer.h"

bool Timer::create(const char *timerName, int msDuration, bool autoRestart, int timerID, void callbackFunction(TimerHandle_t timerHandle)) {
  if (autoRestart) {
    _timerHandle = xTimerCreate(timerName, msDuration / portTICK_PERIOD_MS, pdTRUE, (void *)timerID, callbackFunction);
  } else {
    _timerHandle = xTimerCreate(timerName, msDuration / portTICK_PERIOD_MS, pdFALSE, (void *)timerID, callbackFunction);
  }
  if (_timerHandle == NULL) {
    return false;
  }
  return true;
}

bool Timer::createStatic(const char *timerName, int durationMs, bool autoRestart, int timerID, void callbackFunction(TimerHandle_t timerHandle)) {
  if (autoRestart) {
    _timerHandle = xTimerCreateStatic(timerName, durationMs / portTICK_PERIOD_MS, pdTRUE, (void *)timerID, callbackFunction, &_staticHandle);
  } else {
    _timerHandle = xTimerCreateStatic(timerName, durationMs / portTICK_PERIOD_MS, pdFALSE, (void *)timerID, callbackFunction, &_staticHandle);
  }
  if (_timerHandle == NULL) {
    return false;
  }
  return true;
}

bool Timer::start(int msToBlock) {
  if (_timerHandle != NULL) {
    if (xTimerStart(_timerHandle, msToBlock / portTICK_PERIOD_MS) == pdPASS) {
      return true;
    }
  }
  return false;
}

// Note, when deleting a statically allocated timer, its static memory cannot be reused until that timer is indicated inactive by xTimerIsTimerActive().
bool Timer::destroy(int msToBlock) {
  if (_timerHandle != NULL) {
    if (xTimerDelete(_timerHandle, msToBlock / portTICK_PERIOD_MS) == pdPASS) {
      return true;
    }
  }
  return false;
}

bool Timer::reset(int msToBlock) {
  if (_timerHandle != NULL) {
    if (xTimerReset(_timerHandle, msToBlock / portTICK_PERIOD_MS) == pdPASS) {
      return true;
    }
  }
  return false;
}

bool Timer::changeDuration(int msDuration, int msToBlock) {
  if (_timerHandle != NULL) {
    if (xTimerChangePeriod(_timerHandle, msDuration / portTICK_PERIOD_MS, msToBlock / portTICK_PERIOD_MS) == pdPASS) {
      return true;
    }
  }
  return false;
}

bool Timer::startFromISR() {
  BaseType_t HigherPriorityTaskWoken = pdFALSE;
  if (xTimerStartFromISR(_timerHandle, &HigherPriorityTaskWoken) != pdPASS) {
    return false;
  }
  /* If xHigherPriorityTaskWoken equals pdTRUE, then a context switch
    should be performed.  The syntax required to perform a context switch
    from inside an ISR varies from port to port, and from compiler to
    compiler.  Inspect the demos for the port you are using to find the
    actual syntax required. */
  if (HigherPriorityTaskWoken != pdFALSE) {
    /* Call the interrupt safe yield function here (actual function
        depends on the FreeRTOS port being used). */
  }
  return true;
}
