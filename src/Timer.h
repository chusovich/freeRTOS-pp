#ifndef Timer_h
#define Timer_h
#include "Arduino.h"

#if defined(ARDUINO_ARCH_RP2040)
#include <FreeRTOS.h>
#include <timers.h>
#endif

class Timer {
public:
  bool create(const char *timerName, int msDuration, bool autoRestart, int timerID, void callbackFunction(TimerHandle_t handle));
  bool createStatic(const char *timerName, int msDuration, bool autoRestart, int timerID, void callbackFunction(TimerHandle_t handle));
  bool start(int msToBlock);
  bool destroy(int msToBlock);
  bool reset(int msToBlock);
  bool changeDuration(int msDuration, int msToBlock);
  bool startFromISR();
private:
  static StaticTimer_t _staticHandle;
  TimerHandle_t _timerHandle;
};
#endif
